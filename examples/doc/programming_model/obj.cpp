// --8<-- [start:includes]
#include <cstddef>
#include <cstdint>
#include <mipp_obj.hpp>
// --8<-- [end:includes]
#include <cmath>

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
    mipp::Rvd<float> a = mipp::loadu_obj<float>(ptr_a);
    mipp::Rvd<float> b = mipp::loadu_obj<float>(ptr_b);
    mipp::Rvd<float> c = mipp::loadu_obj<float>(ptr_c);

    // Free functions on Rvd:
    mipp::Rvd<float> res_fma = mipp::fmadd(a, b, c); // Fused multiply-add
    mipp::Rvd<float> res_abs = mipp::abs(a);         // Absolute value
    mipp::Rvd<float> res_min = mipp::min(a, b);      // Element-wise minimum
    float            res_red = mipp::hadd(a);        // Horizontal sum (returns a scalar)

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
    mipp::Rvd<float> c = mipp::add<mipp::M>(m, a, b); // res[i] = m[i] ? a[i] + b[i] : a[i]
    // --8<-- [end:masked]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(c[i] == (A[i] > B[i] ? A[i] + B[i] : A[i]));
}

// §5: remainder handled with masked memory accesses
// --8<-- [start:masked_tail]
// y[i] = a * x[i] + y[i]
void saxpy(std::size_t n, float a, const float* x, float* y)
{
    constexpr std::size_t N = mipp::N<float>();
    const mipp::Rvd<float> va = mipp::set1_obj<float>(a);

    std::size_t i = 0;
    for (; i + N <= n; i += N) {
        mipp::Rvd<float> vx = mipp::loadu_obj<float>(x + i);
        mipp::Rvd<float> vy = mipp::loadu_obj<float>(y + i);
        mipp::storeu(y + i, mipp::fmadd(va, vx, vy));
    }

    if (i < n) { // fewer than N elements left
        int32_t active[N];
        for (std::size_t j = 0; j < N; j++)
            active[j] = (i + j < n);
        mipp::Rvm<float> m  = mipp::set_k_obj<float>(active);     // lane j active iff i + j < n
        mipp::Rvd<float> vx = mipp::loadu_obj<mipp::Z>(m, x + i); // inactive lanes are not read (set to 0)
        mipp::Rvd<float> vy = mipp::loadu_obj<mipp::Z>(m, y + i);
        mipp::storeu<mipp::M>(m, y + i, mipp::fmadd(va, vx, vy)); // inactive lanes are not written
    }
}
// --8<-- [end:masked_tail]

static void masked_tail()
{
    const int N = mipp::Rvd<float>::N();
    for (int n = 0; n <= 3 * N + 1 && n + 1 < DOC_BUF; n++) {
        float x[DOC_BUF], y[DOC_BUF];
        for (int i = 0; i < DOC_BUF; i++) { x[i] = 2.f; y[i] = 1.f; }
        saxpy((std::size_t)n, 3.f, x, y);
        for (int i = 0; i < n; i++)
            DOC_CHECK(y[i] == 7.f);
        DOC_CHECK(y[n] == 1.f); // the element after the end is not written
    }
}

int main()
{
    fill();
    free_functions();
    masked();
    masked_tail();
    return doc_status();
}
