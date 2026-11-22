#include <cmath>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float Z[DOC_BUF];  // re0 im0 re1 im1 ...
DOC_ALIGNED static float W[DOC_BUF];
DOC_ALIGNED static float P[DOC_BUF];
DOC_ALIGNED static float Q[DOC_BUF];
DOC_ALIGNED static float S[DOC_BUF];
DOC_ALIGNED static float M[DOC_BUF];
DOC_ALIGNED static float AR[DOC_BUF]; // split layout: the real parts...
DOC_ALIGNED static float AI[DOC_BUF]; // ... and the imaginary parts
DOC_ALIGNED static float BR[DOC_BUF];
DOC_ALIGNED static float BI[DOC_BUF];
DOC_ALIGNED static float PR[DOC_BUF];
DOC_ALIGNED static float PI[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        Z[i] = (float)(i % 7) - 3.f;
        W[i] = 1.f + (float)(i % 5); // no zero divisor
        AR[i] = Z[i];
        AI[i] = 0.5f * (float)(i % 3);
        BR[i] = W[i];
        BI[i] = (float)(i % 4) - 2.f;
    }
}

static bool close_to(float x, float ref)
{
    return std::fabs(x - ref) <= 1e-4f * (1.f + std::fabs(ref));
}

// §2: interleaved layout
static void interleaved()
{
    // --8<-- [start:interleaved]
    mipp::Rvd<float> a(Z);                      // re0 im0 re1 im1 ...
    mipp::Rvd<float> b(W);
    mipp::Rvd<float> p = mipp::cmul(a, b);      // a * b
    mipp::Rvd<float> q = mipp::cdiv(a, b);      // a / b
    mipp::Rvd<float> s = mipp::cfmadd(a, b, p); // a * b + p
    mipp::Rvd<float> m = mipp::cabs(a);         // |a|, in both lanes of each pair
    // --8<-- [end:interleaved]
    mipp::store(P, p);
    mipp::store(Q, q);
    mipp::store(S, s);
    mipp::store(M, m);
    for (int i = 0; i + 1 < (int)mipp::N<float>(); i += 2) {
        const float ar = Z[i], ai = Z[i + 1], br = W[i], bi = W[i + 1], d = br * br + bi * bi;
        DOC_CHECK(close_to(P[i], ar * br - ai * bi) && close_to(P[i + 1], ar * bi + ai * br));
        DOC_CHECK(close_to(Q[i], (ar * br + ai * bi) / d) && close_to(Q[i + 1], (ai * br - ar * bi) / d));
        DOC_CHECK(close_to(S[i], 2.f * P[i]) && close_to(S[i + 1], 2.f * P[i + 1]));
        DOC_CHECK(close_to(M[i], std::sqrt(ar * ar + ai * ai)) && M[i + 1] == M[i]);
    }
}

// §3: split layout
static void split()
{
    // --8<-- [start:split]
    mipp::Rvd<float> ar(AR), ai(AI);
    mipp::Rvd<float> br(BR), bi(BI);
    mipp::Rvd<float> pr = mipp::fmsub(ar, br, mipp::mul(ai, bi)); // ar br - ai bi
    mipp::Rvd<float> pi = mipp::fmadd(ar, bi, mipp::mul(ai, br)); // ar bi + ai br
    // --8<-- [end:split]
    mipp::store(PR, pr);
    mipp::store(PI, pi);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(close_to(PR[i], AR[i] * BR[i] - AI[i] * BI[i]) && close_to(PI[i], AR[i] * BI[i] + AI[i] * BR[i]));
}

int main()
{
    fill();
    interleaved();
    split();
    return doc_status();
}
