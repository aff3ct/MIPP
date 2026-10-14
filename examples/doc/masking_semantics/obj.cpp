#include <cstdint>
#include <cstring>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float C[DOC_BUF];
DOC_ALIGNED static float SRC[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        C[i] = (float)(i % 3) - 1.f;
        SRC[i] = 100.f + (float)i;
    }
}

// §2: the four variants
static void variants()
{
    mipp::Rvd<float> va(A), vb(B), vsrc(SRC);
    // --8<-- [start:variants]
    // Mask generation via comparison:
    mipp::Rvm<float> m = (va < vb);

    // 1. Unmasked:
    mipp::Rvd<float> res_u = va + vb;

    // 2. Merge-Masked: inactive lanes keep va
    mipp::Rvd<float> res_m = mipp::add<mipp::M>(m, va, vb);

    // 3. Zero-Masked: inactive lanes set to 0
    mipp::Rvd<float> res_z = mipp::add<mipp::Z>(m, va, vb);

    // 4. Source-Masked: inactive lanes taken from vsrc
    mipp::Rvd<float> res_s = mipp::add<mipp::S>(m, vsrc, va, vb);
    // --8<-- [end:variants]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        const bool act = A[i] < B[i];
        DOC_CHECK(res_u[i] == A[i] + B[i]);
        DOC_CHECK(res_m[i] == (act ? A[i] + B[i] : A[i]));
        DOC_CHECK(res_z[i] == (act ? A[i] + B[i] : 0.f));
        DOC_CHECK(res_s[i] == (act ? A[i] + B[i] : SRC[i]));
    }
}

// §2: tip, concise mask syntax
static void using_m()
{
    mipp::Rvd<float> va(A), vb(B);
    mipp::Rvm<float> m = (va < vb);
    // --8<-- [start:using_m]
    using mipp::M;
    mipp::Rvd<float> res = mipp::add<M>(m, va, vb);
    // --8<-- [end:using_m]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(res[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

// §5: mask boolean algebra
static void mask_algebra()
{
    mipp::Rvd<float> va(A), vb(B), vc(C);
    // --8<-- [start:mask_algebra]
    mipp::Rvm<float> m1 = (va < vb);
    mipp::Rvm<float> m2 = (va > vc);

    // Logical AND (m1 AND m2):
    mipp::Rvm<float> m_and = m1 & m2;

    // Logical OR (m1 OR m2):
    mipp::Rvm<float> m_or  = m1 | m2;

    // Logical XOR (m1 XOR m2):
    mipp::Rvm<float> m_xor = m1 ^ m2;

    // Logical NOT (~m1):
    mipp::Rvm<float> m_not = ~m1;

    // Logical AND-NOT ((NOT m1) AND m2):
    mipp::Rvm<float> m_andn = mipp::andnb(m1, m2);
    // --8<-- [end:mask_algebra]
    for (int i = 0; i < mipp::Rvm<float>::N(); i++) {
        const bool a = A[i] < B[i], b = A[i] > C[i];
        DOC_CHECK(m_and[i] == (a && b));
        DOC_CHECK(m_or[i] == (a || b));
        DOC_CHECK(m_xor[i] == (a != b));
        DOC_CHECK(m_not[i] == !a);
        DOC_CHECK(m_andn[i] == (!a && b));
    }
}

// §6.1: cast between mask types
static void cast_k()
{
    mipp::Rvd<float> va(A), vb(B);
    // --8<-- [start:cast_k]
    mipp::Rvm<float>   m_float = (va < vb);
    mipp::Rvm<int32_t> m_int   = mipp::cast<int32_t>(m_float);
    // --8<-- [end:cast_k]
    for (int i = 0; i < mipp::Rvm<int32_t>::N(); i++)
        DOC_CHECK(m_int[i] == (A[i] < B[i]));
}

// §6.2: tomsk
static void tomsk()
{
    const float* ptr = A;
    // --8<-- [start:tomsk]
    mipp::Rvd<float> raw_vector = mipp::load_obj<float>(ptr);
    mipp::Rvm<float> m = mipp::tomsk(raw_vector);
    // --8<-- [end:tomsk]
    for (int i = 0; i < mipp::Rvm<float>::N(); i++)
        DOC_CHECK(m[i] == (A[i] != 0.f)); // +0.0f is the only inactive value of A
}

// §6.3: toreg
static void toreg()
{
    mipp::Rvd<float> va(A), vb(B);
    // --8<-- [start:toreg]
    mipp::Rvm<float> m = (va == vb);
    mipp::Rvd<float> mask_vector = mipp::toreg(m);
    // --8<-- [end:toreg]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        uint32_t bits;
        const float f = mask_vector[i];
        std::memcpy(&bits, &f, sizeof(bits));
        DOC_CHECK(bits == (A[i] == B[i] ? 0xFFFFFFFFu : 0u));
    }
}

// §6.4: blend
static void blend()
{
    mipp::Rvd<float> if_true(A), if_false(B);
    mipp::Rvm<float> m = (if_true < if_false);
    // --8<-- [start:blend]
    // Arguments: mask, if_true, if_false
    mipp::Rvd<float> chosen = mipp::blend(m, if_true, if_false);
    // --8<-- [end:blend]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(chosen[i] == (A[i] < B[i] ? A[i] : B[i]));
}

// §7.2: set_k
static void set_k()
{
    // --8<-- [start:set_k]
    // Array of int32_t, one value per lane
    int32_t mask_values[mipp::N<float>()];
    for (uint32_t i = 0; i < mipp::N<float>(); i++)
        mask_values[i] = (i % 3 == 0) ? 1 : 0; // lanes 0, 3, 6, ... active
    mipp::Rvm<float> m = mipp::set_k_obj<float>(mask_values);
    // --8<-- [end:set_k]
    for (int i = 0; i < mipp::Rvm<float>::N(); i++)
        DOC_CHECK(m[i] == (i % 3 == 0));
}

// §8.1: masks with LMUL = 2
static void lmul2()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    // --8<-- [start:lmul2]
    mipp::Rvd<float, 2> va  = mipp::load_obj<float, 2>(ptr_a);
    mipp::Rvd<float, 2> vb  = mipp::load_obj<float, 2>(ptr_b);
    mipp::Rvm<float, 2> m   = (va < vb);
    mipp::Rvd<float, 2> res = mipp::add<mipp::M>(m, va, vb);
    // --8<-- [end:lmul2]
    for (int i = 0; i < mipp::Rvd<float, 2>::N(); i++)
        DOC_CHECK(res[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

int main()
{
    fill();
    variants();
    using_m();
    mask_algebra();
    cast_k();
    tomsk();
    toreg();
    blend();
    set_k();
    lmul2();
    return doc_status();
}
