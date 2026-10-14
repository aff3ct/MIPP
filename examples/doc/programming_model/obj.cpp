#include <cmath>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float C[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        C[i] = (float)(i % 3);
    }
}

// §4.3: free functions
static void free_functions()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    const float* ptr_c = C;
    float* ptr_out = OUT;
    // --8<-- [start:free_functions]
    auto a = mipp::Rvd<float>(ptr_a);
    auto b = mipp::Rvd<float>(ptr_b);
    auto c = mipp::Rvd<float>(ptr_c);

    // Free functions on Rvd:
    auto res_fma = mipp::fmadd(a, b, c); // Fused multiply-add
    auto res_abs = mipp::abs(a);         // Absolute value
    auto res_min = mipp::min(a, b);      // Element-wise minimum
    auto res_red = mipp::hadd(a);        // Horizontal sum (returns scalar float)

    // Store directly using free function:
    mipp::store(ptr_out, res_fma);
    // --8<-- [end:free_functions]
    const int N = mipp::Rvd<float>::N();
    float sum = 0.f;
    for (int i = 0; i < N; i++) {
        DOC_CHECK(OUT[i] == A[i] * B[i] + C[i]);
        DOC_CHECK(res_abs[i] == std::fabs(A[i]));
        DOC_CHECK(res_min[i] == (A[i] < B[i] ? A[i] : B[i]));
        sum += A[i];
    }
    DOC_CHECK(res_red == sum);
}

// §4.4: masked operation
static void masked()
{
    mipp::Rvd<float> a(A), b(B);
    // --8<-- [start:masked]
    mipp::Rvm<float> m = (a > b);
    auto c = mipp::add<mipp::M>(m, a, b); // res[i] = m[i] ? a[i] + b[i] : a[i]
    // --8<-- [end:masked]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(c[i] == (A[i] > B[i] ? A[i] + B[i] : A[i]));
}

int main()
{
    fill();
    free_functions();
    masked();
    return doc_status();
}
