#include <cstddef>
// --8<-- [start:includes]
#include <mipp.hpp>
// --8<-- [end:includes]

#include "doc_check.h"

DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static float Y[DOC_BUF];

// §2: the raw registers of MIPPv1 (mipp::reg, mipp::msk) become typed registers
// --8<-- [start:loop]
// y[i] = x[i] < 0 ? alpha * x[i] : x[i], n being a multiple of N
void leaky_relu(std::size_t n, float alpha, const float* x, float* y)
{
    constexpr std::size_t N = mipp::N<float>();
    const mipp::vd<float> vzero  = mipp::set0<float>();
    const mipp::vd<float> valpha = mipp::set1<float>(alpha);
    for (std::size_t i = 0; i < n; i += N) {
        mipp::vd<float> vx = mipp::loadu<float>(&x[i]);
        mipp::vm<float> m  = mipp::cmplt(vx, vzero);                    // T is deduced from the registers
        mipp::vd<float> vy = mipp::select(m, mipp::mul(vx, valpha), vx); // m ? vx * alpha : vx
        mipp::storeu(&y[i], vy);
    }
}
// --8<-- [end:loop]

int main()
{
    for (int i = 0; i < DOC_BUF; i++) {
        X[i] = (float)(i % 7) - 3.f;
        Y[i] = -1.f;
    }
    const std::size_t n = 4 * mipp::N<float>();
    leaky_relu(n, 0.5f, X, Y);
    for (std::size_t i = 0; i < n; i++) DOC_CHECK(Y[i] == (X[i] < 0.f ? 0.5f * X[i] : X[i]));
    return doc_status();
}
