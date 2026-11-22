// --8<-- [start:includes]
#include <cstddef>
#include <cstdint>
#include <mipp_obj.hpp>
// --8<-- [end:includes]
#include <cmath>
#include <sstream>

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

// §4.5: printing, packing, generic reductions
static void utilities()
{
    std::ostringstream out;
    // --8<-- [start:utilities]
    const mipp::Rvd<float> v(A);
    out << v << "\n";                                     // [-3, -2, -1, 0 | 1, 2, 3, -3 | ...]
    out << (v > mipp::Rvd<float>(0.f)) << "\n";           // [0, 0, 0, 0 | 1, 1, 1, 0 | ...]

    float vmax = mipp::reduce(v, mipp::op::max());        // largest lane of v
    float total = mipp::reduce(B, 100, mipp::op::add());  // sum of the 100 elements of B

    const mipp::Rvd<int16_t> a(int16_t(300)), b(int16_t(-5));
    mipp::Rvd<int8_t> p = mipp::pack<int8_t>(a, b);       // [127, 127, ... (lanes of a), -5, -5, ... (lanes of b)]
    // --8<-- [end:utilities]
    float ref_max = A[0], ref_total = 0.f;
    for (int i = 1; i < mipp::Rvd<float>::N(); i++)
        ref_max = A[i] > ref_max ? A[i] : ref_max;
    for (int i = 0; i < 100; i++)
        ref_total += B[i];
    DOC_CHECK(vmax == ref_max);
    DOC_CHECK(total == ref_total);
    DOC_CHECK(p[0] == 127 && p[mipp::Rvd<int16_t>::N()] == -5);
    DOC_CHECK(out.str().compare(0, 4, "[-3,") == 0);
}

// §5: remainder handled with masked memory accesses
// --8<-- [start:masked_tail]
// y[i] = x[i] > 0 ? x[i] : alpha * x[i]
void leaky_relu(std::size_t n, float alpha, const float* x, float* y)
{
    constexpr std::size_t N = mipp::Rvd<float>::N();
    const mipp::Rvd<float> vzero(0.f);
    const mipp::Rvd<float> valpha(alpha);

    std::size_t i = 0;
    for (; i + N <= n; i += N) {
        mipp::Rvd<float> vx(x + i);
        mipp::Rvm<float> pos = vx > vzero;
        mipp::storeu(y + i, mipp::select(pos, vx, vx * valpha));
    }

    if (i < n) { // fewer than N elements left
        int32_t active[N];
        for (std::size_t j = 0; j < N; j++)
            active[j] = (i + j < n);
        mipp::Rvm<float> m   = mipp::set_k_obj<float>(active);     // lane j active iff i + j < n
        mipp::Rvd<float> vx  = mipp::loadu_obj<mipp::Z>(m, x + i); // inactive lanes are not read (set to 0)
        mipp::Rvm<float> pos = vx > vzero;
        mipp::storeu<mipp::M>(m, y + i, mipp::select(pos, vx, vx * valpha)); // inactive lanes are not written
    }
}
// --8<-- [end:masked_tail]

static void masked_tail()
{
    const int N = mipp::Rvd<float>::N();
    for (int n = 0; n <= 3 * N + 1 && n + 1 < DOC_BUF; n++) {
        float x[DOC_BUF], y[DOC_BUF];
        for (int i = 0; i < DOC_BUF; i++) { x[i] = (i % 2) ? 2.f : -2.f; y[i] = 99.f; }
        leaky_relu((std::size_t)n, 0.1f, x, y);
        for (int i = 0; i < n; i++)
            DOC_CHECK(y[i] == ((i % 2) ? 2.f : -0.2f));
        DOC_CHECK(y[n] == 99.f); // the element after the end is not written
    }
}

int main()
{
    fill();
    free_functions();
    masked();
    utilities();
    masked_tail();
    return doc_status();
}
