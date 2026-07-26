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
