#include <cstdint>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static int32_t I[DOC_BUF];
DOC_ALIGNED static int32_t CNT[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        I[i] = (i % 9) - 4;
        CNT[i] = i % 5;
    }
}

// §2: registers and scalars
static void forms()
{
    // --8<-- [start:forms]
    mipp::Vd<float> va(A);
    mipp::Vd<float> vb(B);
    mipp::Vd<float> vd1 = va - 1.f;                  // a - 1
    mipp::Vd<float> vd2 = 10.f - va;                 // 10 - a
    mipp::Vd<float> vd3 = mipp::fmadd(va, 2.f, vb);  // a * 2 + b
    mipp::Vm<float> m = va < 0.f;                    // a < 0
    // --8<-- [end:forms]
    const int n = (int)mipp::N<float>();
    for (int i = 0; i < n; i++) DOC_CHECK(vd1[i] == A[i] - 1.f);
    for (int i = 0; i < n; i++) DOC_CHECK(vd2[i] == 10.f - A[i]);
    for (int i = 0; i < n; i++) DOC_CHECK(vd3[i] == A[i] * 2.f + B[i]);
    for (int i = 0; i < n; i++) DOC_CHECK(m[i] == (A[i] < 0.f));

    // --8<-- [start:masked]
    // merge masking keeps the register operand: m ? 10 - a : a
    mipp::Vd<float> vd4 = mipp::sub<mipp::M>(m, 10.f, va);
    // --8<-- [end:masked]
    for (int i = 0; i < n; i++) DOC_CHECK(vd4[i] == (A[i] < 0.f ? 10.f - A[i] : A[i]));
}

// §4: shifts
static void shifts()
{
    // --8<-- [start:shifts]
    mipp::Vd<int32_t> vi(I);
    mipp::Vd<int32_t> vn(CNT);                        // a count per lane, in [0, 31]
    mipp::Vd<int32_t> s1 = vi << vn;                  // i << n, lane by lane
    mipp::Vd<int32_t> s2 = vi >> 1;                   // i >> 1, every lane
    // --8<-- [end:shifts]
    const int n = (int)mipp::N<int32_t>();
    for (int i = 0; i < n; i++) DOC_CHECK(s1[i] == (int32_t)((uint32_t)I[i] << CNT[i]));
    for (int i = 0; i < n; i++) DOC_CHECK(s2[i] == (I[i] >> 1));
}

int main()
{
    fill();
    forms();
    shifts();
    return doc_status();
}
