#include <cstdlib>
#include <iostream>
#include <vector>

#include <mipp_obj.hpp>

// Computes y[i] = x[i] > 0 ? x[i] : alpha * x[i] (Leaky ReLU) over an arbitrary size
void leaky_relu(float alpha, const float* x, float* y, size_t size)
{
    constexpr size_t N = mipp::Rvd<float>::N(); // elements per register (e.g. 8 with AVX2)
    const size_t vec_end = (size / N) * N;

    // 1. Vector main loop
    for (size_t i = 0; i < vec_end; i += N) {
        mipp::Rvd<float> vx(&x[i]);                               // load
        mipp::Rvm<float> pos = vx > 0.f;                          // comparison -> mask
        mipp::Rvd<float> vy  = mipp::select(pos, vx, vx * alpha); // branch-free
        mipp::storeu(&y[i], vy);
    }
    // 2. Scalar tail loop for the remaining elements
    for (size_t i = vec_end; i < size; i++)
        y[i] = x[i] > 0.f ? x[i] : alpha * x[i];
}

int main()
{
    std::vector<float> x(1007), y(1007);
    for (size_t i = 0; i < x.size(); i++)
        x[i] = (i % 2) ? 2.0f : -2.0f;

    leaky_relu(0.1f, x.data(), y.data(), x.size());

    size_t errors = 0;
    for (size_t i = 0; i < y.size(); i++)
        if (y[i] != ((i % 2) ? 2.0f : -0.2f)) errors++;
    std::cout << "y[0] = " << y[0] << ", y[1] = " << y[1] << " (expected -0.2, 2), "
              << errors << " error(s)" << std::endl;
    return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
