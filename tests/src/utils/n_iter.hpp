// n_iter.hpp — Number of test iterations helper.
// Returns the iteration count from the N_ITER environment variable,
// the N_ITER compile-time macro, or the default value of 10.
#pragma once

#include <cstdlib>

inline unsigned get_n_iter() {
    if (const char* env_p = std::getenv("N_ITER")) {
        int val = std::atoi(env_p);
        if (val > 0) return static_cast<unsigned>(val);
    }
#ifdef N_ITER
    return N_ITER;
#else
    return 10;
#endif
}
