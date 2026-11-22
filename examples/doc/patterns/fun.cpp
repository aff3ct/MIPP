// doc-std: c++17
#include <mipp.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float O[DOC_BUF];

// --8<-- [start:patterns]
// lane i of the result: lane get(i, n) of the source (n lanes), -1 for a zero
struct reversed { static constexpr int get(int i, int n) { return n - 1 - i; } };
struct shifted  { static constexpr int get(int i, int n) { return i + 1 < n ? i + 1 : -1; } };
struct mixed    { static constexpr int get(int i, int n) { return i % 2 ? n + i : i; } }; // two registers
// --8<-- [end:patterns]

int main()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)i;
        B[i] = 100.f + (float)i;
    }
    const int n = (int)mipp::N<float>();
    // --8<-- [start:calls]
    mipp::rvd<float> a = mipp::load<float>(A);
    mipp::rvd<float> b = mipp::load<float>(B);
    mipp::rvd<float> r = mipp::permute<reversed>(a);  // mipp::reverse(a)
    mipp::rvd<float> s = mipp::permute<shifted>(a);   // mipp::slide_down(a, 1)
    mipp::rvd<float> m = mipp::permute2<mixed>(a, b); // a0 b1 a2 b3 ...: permute2 and a table
    // --8<-- [end:calls]
    mipp::store(O, r);
    for (int i = 0; i < n; i++) DOC_CHECK(O[i] == A[n - 1 - i]);
    mipp::store(O, s);
    for (int i = 0; i < n; i++) DOC_CHECK(O[i] == (i + 1 < n ? A[i + 1] : 0.f));
    mipp::store(O, m);
    for (int i = 0; i < n; i++) DOC_CHECK(O[i] == (i % 2 ? B[i] : A[i]));
    return doc_status();
}
