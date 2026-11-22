#include <cstddef>
#include <mipp.hpp>

#include "doc_check.h"

int main()
{
    const std::size_t n_elements = 1000;
    // --8<-- [start:alloc]
    // Aligned on mipp::required_alignment() bytes (the register size, e.g. 32 bytes on AVX2):
    float* data = mipp::malloc<float>(n_elements);
    mipp::free(data);

    // std::vector whose storage is aligned (mipp::allocator):
    mipp::vector<float> v(n_elements);
    const bool aligned = mipp::is_aligned(v.data()); // true
    // --8<-- [end:alloc]
    DOC_CHECK(data != NULL);
    DOC_CHECK(aligned);
    DOC_CHECK(mipp::required_alignment() == mipp::req_alignment());
    return doc_status();
}
