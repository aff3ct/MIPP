#define MIPP

#include <stdint.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
#include <stdexcept>
#include <string>
namespace mipp {
    class stub_exception : public std::runtime_error {
    public:
        explicit stub_exception(const std::string& msg) : std::runtime_error(msg) {}
        explicit stub_exception(const char* msg) : std::runtime_error(msg) {}
    };
}
#define MIPP_PANIC_STUB(msg) throw mipp::stub_exception(msg)
#else
#define MIPP_PANIC_STUB(msg) do { printf("%s\n", msg); exit(-1); } while(0)
#endif

// Number of bytes copied between a register of an ISA and the arrays of the scalar fallback (Level 3): the smaller
// of the two sizes. A half-vector can be a full register (RVV with MIPP_RVV_LDIV_VL or MIPP_RVV_LDIV_HYBRID, index
// of a gather on SSE / NEON / SVE): only its lanes are copied.
#define MIPP_MIN_SIZEOF(a, b) (sizeof(a) < sizeof(b) ? sizeof(a) : sizeof(b))
