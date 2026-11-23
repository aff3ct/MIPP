// Tests of the compile-time permutations permute<P> and permute2<P> (C++17, mipp/cpp/patterns.hpp): every pattern
// recognized among the named rearrangements, and the fallbacks (table of indices, zeros, memory), compared with the
// lanes given by the pattern itself. Not generated: tests/src/manual/ is kept by gen_mipp_tests.py.
#include <cstdint>

#include <mipp.hpp>
#include <mipp_obj.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#if __cplusplus >= 201703L

// a named namespace: the unity builds put several test files in one translation unit
namespace mipp_test_patterns
{
// one register
struct p_zero      { static constexpr int get(int, int) { return -1; } };
struct p_identity  { static constexpr int get(int i, int) { return i; } };
struct p_reverse   { static constexpr int get(int i, int n) { return n - 1 - i; } };
struct p_rotate    { static constexpr int get(int i, int n) { return (i + 1) % n; } };
struct p_broadcast { static constexpr int get(int, int n) { return n - 1; } };
struct p_down      { static constexpr int get(int i, int n) { return i + 1 < n ? i + 1 : -1; } };
struct p_up        { static constexpr int get(int i, int) { return i >= 1 ? i - 1 : -1; } };
struct p_swap      { static constexpr int get(int i, int n) { return (i ^ 1) < n ? i ^ 1 : i; } }; // n = 1: d2 of float64 on NEON
struct p_even      { static constexpr int get(int i, int) { return i & ~1; } };
struct p_odd       { static constexpr int get(int i, int n) { return (i | 1) < n ? i | 1 : i; } };
struct p_table     { static constexpr int get(int i, int n) { return (3 * i + 1) % n; } };
struct p_table0    { static constexpr int get(int i, int n) { return i % 3 == 0 ? -1 : (5 * i + 2) % n; } };
// two registers
struct q_slide     { static constexpr int get(int i, int) { return i + 1; } };
struct q_zip_lo    { static constexpr int get(int i, int n) { return (i & 1) ? n + i / 2 : i / 2; } };
struct q_zip_hi    { static constexpr int get(int i, int n) { return (i & 1) ? n + n / 2 + i / 2 : n / 2 + i / 2; } };
struct q_unzip_e   { static constexpr int get(int i, int) { return 2 * i; } };
struct q_unzip_o   { static constexpr int get(int i, int) { return 2 * i + 1; } };
struct q_hi        { static constexpr int get(int i, int n) { return n + n - 1 - i; } };
struct q_table     { static constexpr int get(int i, int n) { return (7 * i + 3) % (2 * n); } };
struct q_table0    { static constexpr int get(int i, int n) { return i % 4 == 1 ? -1 : (3 * i + n / 2) % (2 * n); } };

template <typename T, int LMUL, typename P>
void check1()
{
	constexpr int n = static_cast<int>(mipp::N<T, LMUL>());
	T a[n], r[n];
	for (int i = 0; i < n; i++) a[i] = static_cast<T>(i + 1);
	mipp::storeu(r, mipp::permute<P>(mipp::loadu<T, LMUL>(a)));
	for (int i = 0; i < n; i++)
	{
		const int k = P::get(i, n);
		REQUIRE(r[i] == (k < 0 ? T(0) : a[k]));
	}
	mipp::Rvd<T, LMUL> o(a); // Object API
	mipp::storeu(r, mipp::permute<P>(o).r);
	for (int i = 0; i < n; i++)
		REQUIRE(r[i] == (P::get(i, n) < 0 ? T(0) : a[P::get(i, n)]));
}

template <typename T, int LMUL, typename P>
void check2()
{
	constexpr int n = static_cast<int>(mipp::N<T, LMUL>());
	T a[2 * n], r[n];
	for (int i = 0; i < 2 * n; i++) a[i] = static_cast<T>((i + 1) % 100);
	mipp::storeu(r, mipp::permute2<P>(mipp::loadu<T, LMUL>(a), mipp::loadu<T, LMUL>(a + n)));
	for (int i = 0; i < n; i++)
	{
		const int k = P::get(i, n);
		REQUIRE(r[i] == (k < 0 ? T(0) : a[k]));
	}
}

template <typename T, int LMUL>
void check_all()
{
	check1<T, LMUL, p_zero>();
	check1<T, LMUL, p_identity>();
	check1<T, LMUL, p_reverse>();
	check1<T, LMUL, p_rotate>();
	check1<T, LMUL, p_broadcast>();
	check1<T, LMUL, p_down>();
	check1<T, LMUL, p_up>();
	check1<T, LMUL, p_swap>();
	check1<T, LMUL, p_even>();
	check1<T, LMUL, p_odd>();
	check1<T, LMUL, p_table>();
	check1<T, LMUL, p_table0>();
	check2<T, LMUL, q_slide>();
	check2<T, LMUL, q_zip_lo>();
	check2<T, LMUL, q_zip_hi>();
	check2<T, LMUL, q_unzip_e>();
	check2<T, LMUL, q_unzip_o>();
	check2<T, LMUL, q_hi>();
	check2<T, LMUL, q_table>();
	check2<T, LMUL, q_table0>();
}

TEMPLATE_TEST_CASE("patterns - permute<P> and permute2<P>", "[patterns]", float, double, int8_t, uint8_t, int16_t,
                   int32_t, uint64_t)
{
	check_all<TestType, 1>();
	check_all<TestType, 2>();
	check_all<TestType, 8>();
#if defined(MIPP_LDIV_2)
	check_all<TestType, -2>();
#endif
}

// the recognized patterns are the named functions themselves
TEST_CASE("patterns - recognized patterns", "[patterns]")
{
	using T = int32_t;
	constexpr int n = static_cast<int>(mipp::N<T, 1>());
	static_assert(mipp::details::is_reverse(mipp::details::pattern_checked<p_reverse, n, n>()), "reverse");
	static_assert(mipp::details::rotate_of(mipp::details::pattern_checked<p_rotate, n, n>()) == (n > 1 ? 1 : 0), "rotate");
	static_assert(mipp::details::slide_of(mipp::details::pattern_checked<q_slide, n, 2 * n>()) == 1, "slide");
	static_assert(!mipp::details::is_zip_lo(mipp::details::pattern_checked<q_table, n, 2 * n>()) || n <= 2, "zip_lo");
	SUCCEED();
}
} // namespace mipp_test_patterns

#endif // __cplusplus >= 201703L
