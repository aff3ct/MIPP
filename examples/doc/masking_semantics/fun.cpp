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
    mipp::storeu(r, mipp::blend(m, mipp::set1<T, LMUL>(1), mipp::set0<T, LMUL>()));
    for (int i = 0; i < (int)mipp::N<T, LMUL>(); i++)
        out[i] = r[i] != 0;
}

// §2.2: the four variants
static void variants()
{
    auto va = mipp::load<float>(A);
    auto vb = mipp::load<float>(B);
    auto vsrc = mipp::load<float>(SRC);
    // --8<-- [start:variants]
    auto m = mipp::cmplt(va, vb);

    // 1. Unmasked (deduced automatically from operand types):
    auto res_u = mipp::add(va, vb);

    // 2. Merge-Masked: preserves va on false
    auto res_m = mipp::add<mipp::M, float, 1>(m, va, vb); // or mipp::add<mipp::M, float>(m, va, vb)

    // 3. Zero-Masked: zeroes inactive elements on false
    auto res_z = mipp::add<mipp::Z, float, 1>(m, va, vb);

    // 4. Source-Masked: preserves values from vsrc on false
    auto res_s = mipp::add<mipp::S, float, 1>(m, vsrc, va, vb);
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
    auto va = mipp::load<float>(A);
    auto vb = mipp::load<float>(B);
    auto vc = mipp::load<float>(C);
    // --8<-- [start:mask_algebra]
    // C++ Functional API
    auto m1 = mipp::cmplt(va, vb);
    auto m2 = mipp::cmpgt(va, vc);

    // Logical AND (m1 AND m2):
    auto m_and = mipp::andb(m1, m2);

    // Logical OR (m1 OR m2):
    auto m_or  = mipp::orb(m1, m2);

    // Logical XOR (m1 XOR m2):
    auto m_xor = mipp::xorb(m1, m2);

    // Logical NOT (~m1):
    auto m_not = mipp::notb(m1);

    // Logical AND-NOT ((NOT m1) AND m2):
    auto m_andn = mipp::andnb(m1, m2);
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
    auto va = mipp::load<float>(A);
    auto vb = mipp::load<float>(B);
    // --8<-- [start:cast_k]
    // C++ Functional API: target type suffix (overloaded on rvm and rvd)
    mipp::rvm<float> m_float = mipp::cmplt(va, vb);
    mipp::rvm<int32_t> m_int = mipp::cast_int32(m_float);
    // --8<-- [end:cast_k]
    int32_t act[DOC_BUF];
    lanes<int32_t>(m_int, act);
    for (int i = 0; i < (int)mipp::N<int32_t>(); i++)
        DOC_CHECK(act[i] == (A[i] < B[i]));
}

// §6.2: tomsk
static void tomsk()
{
    const float* ptr = A;
    // --8<-- [start:tomsk]
    // C++ API:
    mipp::rvd<float> raw_vector = mipp::load<float>(ptr);
    mipp::rvm<float> m = mipp::tomsk(raw_vector);
    // --8<-- [end:tomsk]
    int32_t act[DOC_BUF];
    lanes<float>(m, act);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(act[i] == (A[i] != 0.f)); // +0.0f is the only inactive value of A
}

// §6.3: toreg
static void toreg()
{
    auto va = mipp::load<float>(A);
    auto vb = mipp::load<float>(B);
    // --8<-- [start:toreg]
    // C++ API:
    mipp::rvm<float> m = mipp::cmpeq(va, vb);
    mipp::rvd<float> mask_vector = mipp::toreg(m);
    // --8<-- [end:toreg]
    uint32_t bits[DOC_BUF];
    mipp::storeu(OUT, mask_vector);
    std::memcpy(bits, OUT, sizeof(bits));
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(bits[i] == (A[i] == B[i] ? 0xFFFFFFFFu : 0u));
}

// §6.4: blend
static void blend()
{
    auto if_true = mipp::load<float>(A);
    auto if_false = mipp::load<float>(B);
    auto m = mipp::cmplt(if_true, if_false);
    // --8<-- [start:blend]
    // C++ Functional API: (mask, if_true, if_false)
    auto chosen_fun = mipp::blend(m, if_true, if_false);
    // --8<-- [end:blend]
    mipp::storeu(OUT, chosen_fun);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] : B[i]));
}

// §8.1: masks with LMUL = 2
static void lmul2()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    // --8<-- [start:lmul2]
    // C++ Functional API: explicit LMUL parameter required
    auto va = mipp::load<float, 2>(ptr_a);              // mipp::rvd<float, 2>
    auto vb = mipp::load<float, 2>(ptr_b);              // mipp::rvd<float, 2>
    auto m  = mipp::cmplt(va, vb);                      // mipp::rvm<float, 2>
    auto res = mipp::add<mipp::M, float, 2>(m, va, vb); // mipp::rvd<float, 2>
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
    tomsk();
    toreg();
    blend();
    lmul2();
    return doc_status();
}
