#include <stdio.h>
#include <stdlib.h>

#include <mipp.h>

// Computes y[i] = a * x[i] + y[i] (SAXPY) over arbitrary size S
void saxpy_mipp(float a, const float* x, float* y, size_t size)
{
    const size_t N = MIPP_N_FLOAT32; // Elements per SIMD register (e.g. 8 on AVX2)
    const size_t vec_limit = (size / N) * N;
    rvd_float32_m1_t va = mipp_set1_float32_m1(a);

    // 1. Vector main loop
    for (size_t i = 0; i < vec_limit; i += N)
    {
        rvd_float32_m1_t vx = mipp_loadu_float32_m1(&x[i]);
        rvd_float32_m1_t vy = mipp_loadu_float32_m1(&y[i]);

        rvd_float32_m1_t vres = mipp_fmadd_float32_m1(va, vx, vy);

        mipp_storeu_float32_m1(&y[i], vres);
    }

    // 2. Scalar tail loop for remaining elements
    for (size_t i = vec_limit; i < size; ++i)
    {
        y[i] += a * x[i];
    }
}

int main(void)
{
    const size_t size = 1007;
    float *x = (float*)malloc(size * sizeof(float));
    float *y = (float*)malloc(size * sizeof(float));

    for (size_t i = 0; i < size; i++) { x[i] = 2.0f; y[i] = 1.0f; }

    saxpy_mipp(3.0f, x, y, size);

    size_t errors = 0;
    for (size_t i = 0; i < size; i++)
        if (y[i] != 7.0f) errors++;
    printf("y[0] = %f, y[1006] = %f (expected: 7.0), %zu error(s)\n", y[0], y[1006], errors);

    free(x);
    free(y);
    return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

// Compile and run:
// gcc -std=c99 -O3 -mavx2 -mfma -I/path/to/mipp/include saxpy_c.c -o saxpy_c
// ./saxpy_c
