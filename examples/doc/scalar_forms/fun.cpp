#include <cstdint>
#include <mipp.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];
DOC_ALIGNED static int32_t I[DOC_BUF];
DOC_ALIGNED static int32_t CNT[DOC_BUF];
DOC_ALIGNED static int32_t IOUT[DOC_BUF];

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
    mipp::vd<float> va = mipp::load<float>(A);
    mipp::vd<float> vb = mipp::load<float>(B);
    mipp::vd<float> r1 = mipp::sub(va, 1.f);         // a - 1
    mipp::vd<float> r2 = mipp::sub(10.f, va);        // 10 - a
    mipp::vd<float> r3 = mipp::fmadd(va, 2.f, vb);   // a * 2 + b
    mipp::vm<float> m = mipp::cmplt(va, 0.f);        // a < 0
    // --8<-- [end:forms]
    const int n = (int)mipp::N<float>();
    mipp::store(OUT, r1);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == A[i] - 1.f);
    mipp::store(OUT, r2);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == 10.f - A[i]);
    mipp::store(OUT, r3);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == A[i] * 2.f + B[i]);
    mipp::store(OUT, mipp::select(m, mipp::set1<float>(1.f), mipp::set0<float>()));
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == (A[i] < 0.f ? 1.f : 0.f));

    // --8<-- [start:masked]
    // merge masking keeps the register operand: m ? 10 - a : a
    mipp::vd<float> r4 = mipp::sub<mipp::M>(m, 10.f, va);
    // --8<-- [end:masked]
    mipp::store(OUT, r4);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == (A[i] < 0.f ? 10.f - A[i] : A[i]));
}

// §4: shifts
static void shifts()
{
    // --8<-- [start:shifts]
    mipp::vd<int32_t> vi = mipp::load<int32_t>(I);
    mipp::vd<int32_t> vn = mipp::load<int32_t>(CNT); // a count per lane, in [0, 31]
    mipp::vd<int32_t> s1 = mipp::lshift(vi, vn);      // i << n, lane by lane
    mipp::vd<int32_t> s2 = mipp::rshift(vi, 1);       // i >> 1, every lane
    // --8<-- [end:shifts]
    const int n = (int)mipp::N<int32_t>();
    mipp::store(IOUT, s1);
    for (int i = 0; i < n; i++) DOC_CHECK(IOUT[i] == (int32_t)((uint32_t)I[i] << CNT[i]));
    mipp::store(IOUT, s2);
    for (int i = 0; i < n; i++) DOC_CHECK(IOUT[i] == (I[i] >> 1));
}

int main()
{
    fill();
    forms();
    shifts();
    return doc_status();
}
