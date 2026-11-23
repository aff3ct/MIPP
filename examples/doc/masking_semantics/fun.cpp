#include <cstdint>
#include <cstring>
#include <mipp.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float C[DOC_BUF];
DOC_ALIGNED static float SRC[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        C[i] = (float)(i % 3) - 1.f;
        SRC[i] = 100.f + (float)i;
    }
}

// Lane i of a mask, as 0 or 1.
template <typename T, int LMUL = 1, typename MASK>
static void lanes(MASK m, int32_t* out)
{
    T r[DOC_BUF];
    mipp::storeu(r, mipp::select(m, mipp::set1<T, LMUL>(1), mipp::set0<T, LMUL>()));
    for (int i = 0; i < (int)mipp::N<T, LMUL>(); i++)
        out[i] = r[i] != 0;
}

// §2.2: the four variants
static void variants()
{
    mipp::vd<float> va = mipp::load<float>(A);
    mipp::vd<float> vb = mipp::load<float>(B);
    mipp::vd<float> vsrc = mipp::load<float>(SRC);
    // --8<-- [start:variants]
    // Mask generation via comparison:
    mipp::vm<float> m = mipp::cmplt(va, vb);

    // 1. Unmasked:
    mipp::vd<float> res_u = mipp::add(va, vb);

    // 2. Merge-Masked: inactive lanes keep va
    mipp::vd<float> res_m = mipp::add<mipp::M, float>(m, va, vb);

    // 3. Zero-Masked: inactive lanes set to 0
    mipp::vd<float> res_z = mipp::add<mipp::Z, float>(m, va, vb);

    // 4. Source-Masked: inactive lanes taken from vsrc
    mipp::vd<float> res_s = mipp::add<mipp::S, float>(m, vsrc, va, vb);
    // --8<-- [end:variants]
    float u[DOC_BUF], mm[DOC_BUF], z[DOC_BUF], s[DOC_BUF];
    mipp::storeu(u, res_u);
    mipp::storeu(mm, res_m);
    mipp::storeu(z, res_z);
    mipp::storeu(s, res_s);
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
        const bool act = A[i] < B[i];
        DOC_CHECK(u[i] == A[i] + B[i]);
        DOC_CHECK(mm[i] == (act ? A[i] + B[i] : A[i]));
        DOC_CHECK(z[i] == (act ? A[i] + B[i] : 0.f));
        DOC_CHECK(s[i] == (act ? A[i] + B[i] : SRC[i]));
    }
}

// §5: mask boolean algebra
static void mask_algebra()
{
    mipp::vd<float> va = mipp::load<float>(A);
    mipp::vd<float> vb = mipp::load<float>(B);
    mipp::vd<float> vc = mipp::load<float>(C);
    // --8<-- [start:mask_algebra]
    mipp::vm<float> m1 = mipp::cmplt(va, vb);
    mipp::vm<float> m2 = mipp::cmpgt(va, vc);

    // Logical AND (m1 AND m2):
    mipp::vm<float> m_and = mipp::andb(m1, m2);

    // Logical OR (m1 OR m2):
    mipp::vm<float> m_or  = mipp::orb(m1, m2);

    // Logical XOR (m1 XOR m2):
    mipp::vm<float> m_xor = mipp::xorb(m1, m2);

    // Logical NOT (~m1):
    mipp::vm<float> m_not = mipp::notb(m1);

    // Logical AND-NOT ((NOT m1) AND m2):
    mipp::vm<float> m_andn = mipp::andnb(m1, m2);
    // --8<-- [end:mask_algebra]
    int32_t l_and[DOC_BUF], l_or[DOC_BUF], l_xor[DOC_BUF], l_not[DOC_BUF], l_andn[DOC_BUF];
    lanes<float>(m_and, l_and);
    lanes<float>(m_or, l_or);
    lanes<float>(m_xor, l_xor);
    lanes<float>(m_not, l_not);
    lanes<float>(m_andn, l_andn);
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
        const int a = A[i] < B[i], b = A[i] > C[i];
        DOC_CHECK(l_and[i] == (a && b));
        DOC_CHECK(l_or[i] == (a || b));
        DOC_CHECK(l_xor[i] == (a != b));
        DOC_CHECK(l_not[i] == !a);
        DOC_CHECK(l_andn[i] == (!a && b));
    }
}

// §6.1: cast between mask types
static void cast_k()
{
    mipp::vd<float> va = mipp::load<float>(A);
    mipp::vd<float> vb = mipp::load<float>(B);
    // --8<-- [start:cast_k]
    mipp::vm<float>   m_float = mipp::cmplt(va, vb);
    mipp::vm<int32_t> m_int   = mipp::cast_int32(m_float);
    // --8<-- [end:cast_k]
    int32_t act[DOC_BUF];
    lanes<int32_t>(m_int, act);
    for (int i = 0; i < (int)mipp::N<int32_t>(); i++)
        DOC_CHECK(act[i] == (A[i] < B[i]));
}

// §6.2: tovm
static void tovm()
{
    const float* ptr = A;
    // --8<-- [start:tovm]
    mipp::vd<float> raw_vector = mipp::load<float>(ptr);
    mipp::vm<float> m = mipp::tovm(raw_vector);
    // --8<-- [end:tovm]
    int32_t act[DOC_BUF];
    lanes<float>(m, act);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(act[i] == (A[i] != 0.f)); // +0.0f is the only inactive value of A
}

// §6.3: tovd
static void tovd()
{
    mipp::vd<float> va = mipp::load<float>(A);
    mipp::vd<float> vb = mipp::load<float>(B);
    // --8<-- [start:tovd]
    mipp::vm<float> m = mipp::cmpeq(va, vb);
    mipp::vd<float> mask_vector = mipp::tovd(m);
    // --8<-- [end:tovd]
    uint32_t bits[DOC_BUF];
    mipp::storeu(OUT, mask_vector);
    std::memcpy(bits, OUT, sizeof(bits));
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(bits[i] == (A[i] == B[i] ? 0xFFFFFFFFu : 0u));
}

// §6.4: select
static void select_example()
{
    mipp::vd<float> if_true = mipp::load<float>(A);
    mipp::vd<float> if_false = mipp::load<float>(B);
    mipp::vm<float> m = mipp::cmplt(if_true, if_false);
    // --8<-- [start:select]
    // Arguments: mask, if_true, if_false
    mipp::vd<float> chosen = mipp::select(m, if_true, if_false);
    // --8<-- [end:select]
    mipp::storeu(OUT, chosen);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] : B[i]));
}

// §7.2: set_k
static void set_k()
{
    // --8<-- [start:set_k]
    // Array of int32_t, one value per lane
    int32_t mask_values[mipp::N<float>()];
    for (uint32_t i = 0; i < mipp::N<float>(); i++)
        mask_values[i] = (i % 3 == 0) ? 1 : 0; // lanes 0, 3, 6, ... active
    mipp::vm<float> m = mipp::set_k<float>(mask_values);
    // --8<-- [end:set_k]
    int32_t act[DOC_BUF];
    lanes<float>(m, act);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(act[i] == (i % 3 == 0));
}

// §8.1: masks with LMUL = 2
static void lmul2()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    // --8<-- [start:lmul2]
    mipp::vd<float, 2> va  = mipp::load<float, 2>(ptr_a);
    mipp::vd<float, 2> vb  = mipp::load<float, 2>(ptr_b);
    mipp::vm<float, 2> m   = mipp::cmplt(va, vb);
    mipp::vd<float, 2> res = mipp::add<mipp::M, float, 2>(m, va, vb);
    // --8<-- [end:lmul2]
    mipp::storeu(OUT, res);
    for (int i = 0; i < (int)mipp::N<float, 2>(); i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

int main()
{
    fill();
    variants();
    mask_algebra();
    cast_k();
    tovm();
    tovd();
    select_example();
    set_k();
    lmul2();
    return doc_status();
}
