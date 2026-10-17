#include <cstdlib>
#include <iostream>
#include <vector>

#include <mipp_obj.hpp>

// Computes y[i] = a * x[i] + y[i] (SAXPY) over arbitrary size S
void saxpy_mipp(float a, const float *x, float *y, size_t size)
{
    constexpr size_t N = mipp::N<float>(); // Elements per SIMD register (e.g. 8 on AVX2)
    const size_t vec_limit = (size / N) * N;
    mipp::Rvd<float> va = mipp::set1_obj<float>(a);

    // 1. Vector main loop
    for (size_t i = 0; i < vec_limit; i += N) 
    {
        mipp::Rvd<float> vx = mipp::loadu_obj<float>(&x[i]);
        mipp::Rvd<float> vy = mipp::loadu_obj<float>(&y[i]);

        mipp::Rvd<float> vres = mipp::fmadd(va, vx, vy);

        mipp::storeu(&y[i], vres);
    }

    // 2. Scalar tail loop for remaining elements
    for (size_t i = vec_limit; i < size; ++i) 
    {
        y[i] += a * x[i];
    }
}

int main() 
{
    const size_t size = 1007;
    std::vector<float> x(size, 2.0f);
    std::vector<float> y(size, 1.0f);

    saxpy_mipp(3.0f, x.data(), y.data(), size);

    size_t errors = 0;
    for (size_t i = 0; i < size; i++)
        if (y[i] != 7.0f) errors++;
    std::cout << "y[0] = " << y[0] << ", y[1006] = " << y[1006] << " (expected: 7.0), "
              << errors << " error(s)" << std::endl;
    return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
