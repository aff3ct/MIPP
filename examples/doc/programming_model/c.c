/* --8<-- [start:includes] */
#include <stddef.h>
#include <stdint.h>
#include <mipp.h>
/* --8<-- [end:includes] */

#include "doc_check.h"

/* §5: remainder handled with masked memory accesses */
/* --8<-- [start:masked_tail] */
// y[i] = a * x[i] + y[i]
void saxpy(size_t n, float a, const float* x, float* y)
{
    const size_t N = MIPP_N_FLOAT32;
    const rvd_float32_t va = mipp_set1_float32(a);

    size_t i = 0;
    for (; i + N <= n; i += N) {
        rvd_float32_t vx = mipp_loadu_float32(x + i);
        rvd_float32_t vy = mipp_loadu_float32(y + i);
        mipp_storeu_float32(y + i, mipp_fmadd_float32(va, vx, vy));
    }

    if (i < n) { // fewer than N elements left
        int32_t active[MIPP_N_FLOAT32];
        for (size_t j = 0; j < N; j++)
            active[j] = (i + j < n);
        rvm_float32_t m  = mipp_set_k_float32(active);          // lane j active iff i + j < n
        rvd_float32_t vx = mipp_loadu_float32_maskz(m, x + i);  // inactive lanes are not read (set to 0)
        rvd_float32_t vy = mipp_loadu_float32_maskz(m, y + i);
        mipp_storeu_float32_mask(m, y + i, mipp_fmadd_float32(va, vx, vy)); // inactive lanes are not written
    }
}
/* --8<-- [end:masked_tail] */

static void masked_tail(void)
{
    const int N = MIPP_N_FLOAT32;
    for (int n = 0; n <= 3 * N + 1 && n + 1 < DOC_BUF; n++) {
        float x[DOC_BUF], y[DOC_BUF];
        for (int i = 0; i < DOC_BUF; i++) { x[i] = 2.f; y[i] = 1.f; }
        saxpy((size_t)n, 3.f, x, y);
        for (int i = 0; i < n; i++)
            DOC_CHECK(y[i] == 7.f);
        DOC_CHECK(y[n] == 1.f); /* the element after the end is not written */
    }
}

int main(void)
{
    masked_tail();
    return doc_status();
}
