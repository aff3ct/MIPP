#include <stdio.h>
#include <stdlib.h>

#include <mipp.h>

// Computes y[i] = x[i] > 0 ? x[i] : alpha * x[i] (Leaky ReLU) over an arbitrary size
void leaky_relu(float alpha, const float* x, float* y, size_t size)
{
    const size_t N = MIPP_N_FLOAT32; // elements per register (e.g. 8 with AVX2)
    const size_t vec_end = (size / N) * N;
    rvd_float32_m1_t vzero  = mipp_set1_float32_m1(0.f);
    rvd_float32_m1_t valpha = mipp_set1_float32_m1(alpha);

    // 1. Vector main loop
    for (size_t i = 0; i < vec_end; i += N) {
        rvd_float32_m1_t vx  = mipp_loadu_float32_m1(&x[i]);
        rvm_float32_m1_t pos = mipp_cmpgt_float32_m1(vx, vzero);                                 // comparison -> mask
        rvd_float32_m1_t vy  = mipp_select_float32_m1(pos, vx, mipp_mul_float32_m1(vx, valpha)); // branch-free
        mipp_storeu_float32_m1(&y[i], vy);
    }
    // 2. Scalar tail loop for the remaining elements
    for (size_t i = vec_end; i < size; i++)
        y[i] = x[i] > 0.f ? x[i] : alpha * x[i];
}

int main(void)
{
    const size_t size = 1007;
    float* x = (float*)malloc(size * sizeof(float));
    float* y = (float*)malloc(size * sizeof(float));
    for (size_t i = 0; i < size; i++)
        x[i] = (i % 2) ? 2.0f : -2.0f;

    leaky_relu(0.1f, x, y, size);

    size_t errors = 0;
    for (size_t i = 0; i < size; i++)
        if (y[i] != ((i % 2) ? 2.0f : -0.2f)) errors++;
    printf("y[0] = %g, y[1] = %g (expected -0.2, 2), %zu error(s)\n", y[0], y[1], errors);

    free(x);
    free(y);
    return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
