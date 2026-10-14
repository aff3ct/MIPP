// doc-std: c++17 (std::aligned_alloc)
#include <cstdlib>
#include <mipp.hpp>

#include "doc_check.h"

int main()
{
    const size_t n_elements = 1000;
    // --8<-- [start:alloc]
    // Alignment required by the active target ISA (e.g. 32 bytes on AVX2):
    constexpr size_t alignment = mipp::req_alignment();

    // POSIX aligned allocation (C99 / C++):
    float* data_c = NULL;
    if (posix_memalign((void**)&data_c, alignment, n_elements * sizeof(float)) != 0)
        return 1; // allocation failed
    free(data_c);

    // C++17 aligned allocation (the size must be a multiple of the alignment):
    const size_t bytes = ((n_elements * sizeof(float) + alignment - 1) / alignment) * alignment;
    float* data = static_cast<float*>(std::aligned_alloc(alignment, bytes));
    std::free(data);
    // --8<-- [end:alloc]
    DOC_CHECK(data != NULL);
    DOC_CHECK(bytes % alignment == 0 && bytes >= n_elements * sizeof(float));
    return doc_status();
}
