// Tests of the immediate versions (generator/helpers_headers/codegen/imm.py): for every value S of the integer
// argument, the call with the constant S (C dispatch on the immediate bodies), the C++ templates f<S>(...) of the
// Functional and Object APIs, and the call with a variable (dynamic body, itself tested against the scalar reference
// by the generated tests) give the same lanes. Built with optimizations, as the other tests: the constant reaches the
// dispatch through the inlining. Not generated: tests/src/manual/ is kept by gen_mipp_tests.py.
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>

#include <mipp.hpp>
#include <mipp_obj.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

// a named namespace: the unity builds put several test files in one translation unit
namespace mipp_test_immediates
{
template <typename T, int LMUL>
struct data
{
	static constexpr int n = static_cast<int>(mipp::N<T, LMUL>());
	T a[n], b[n];
	data()
	{
		for (int i = 0; i < n; i++)
		{
			a[i] = static_cast<T>((i * 7 + 3) % 61 + 1);
			b[i] = static_cast<T>(100 - (i * 5 + 1) % 47);
		}
	}
};

// lanes of two registers, compared bit by bit (the shifts of the floating-point numbers give any pattern)
template <typename T, int LMUL, typename R>
void require_same(const R& x, const R& y)
{
	constexpr int n = static_cast<int>(mipp::N<T, LMUL>());
	T bx[n], by[n];
	mipp::storeu(bx, x);
	mipp::storeu(by, y);
	std::string lanes; // the lanes, printed on a failure
	for (int i = 0; i < n; i++)
		lanes += std::to_string(static_cast<double>(bx[i])) + "/" + std::to_string(static_cast<double>(by[i])) + " ";
	INFO("lanes (x/y): " << lanes);
	REQUIRE(std::memcmp(bx, by, sizeof(bx)) == 0);
}

template <typename T, int LMUL, int S>
void check_value()
{
	data<T, LMUL> d;
	volatile int32_t vs = S; // a variable: the dynamic body
	const int32_t v = vs;
	const mipp::vd<T, LMUL> a = mipp::loadu<T, LMUL>(d.a), b = mipp::loadu<T, LMUL>(d.b);
	const mipp::Vd<T, LMUL> oa(d.a), ob(d.b);
	constexpr int n = data<T, LMUL>::n;
	constexpr int nb = static_cast<int>(16 / sizeof(T)) < n ? static_cast<int>(16 / sizeof(T)) : n;
	constexpr int bits = static_cast<int>(8 * sizeof(T));

#define MIPP_CHECK_IMM(F, ...)                                                                                         \
	do {                                                                                                               \
		INFO(#F << ": S = " << S << ", LMUL = " << LMUL);                                                              \
		const mipp::vd<T, LMUL> dyn = mipp::F(__VA_ARGS__, v);                                                        \
		require_same<T, LMUL>(mipp::F(__VA_ARGS__, S), dyn);                                                           \
		require_same<T, LMUL>(mipp::F<S>(__VA_ARGS__), dyn);                                                           \
	} while (0)

	if constexpr (S <= n)
	{
		MIPP_CHECK_IMM(slide, a, b);
		MIPP_CHECK_IMM(slideup, a);
		MIPP_CHECK_IMM(slidedown, a);
		INFO("obj slide: S = " << S << ", LMUL = " << LMUL);
		require_same<T, LMUL>(mipp::slide<S>(oa, ob).vd, mipp::slide(a, b, v));
	}
	if constexpr (S < n)
	{
		MIPP_CHECK_IMM(rotate, a);
		MIPP_CHECK_IMM(bcast, a);
		INFO("get: S = " << S << ", LMUL = " << LMUL);
		REQUIRE(mipp::get(a, S) == mipp::get(a, (uint32_t)v));
		REQUIRE(mipp::get<S>(a) == mipp::get(a, (uint32_t)v));
		REQUIRE(mipp::get<S>(oa) == mipp::get(a, (uint32_t)v));
	}
	if constexpr (S <= nb)
	{
		MIPP_CHECK_IMM(slide_b128, a, b);
		MIPP_CHECK_IMM(slideup_b128, a);
		MIPP_CHECK_IMM(slidedown_b128, a);
	}
	if constexpr (S < nb)
	{
		MIPP_CHECK_IMM(rotate_b128, a);
		MIPP_CHECK_IMM(bcast_b128, a);
	}
	if constexpr (S < bits)
	{
		MIPP_CHECK_IMM(lshift, a);
		MIPP_CHECK_IMM(rshift, a);
	}
#undef MIPP_CHECK_IMM
}

template <typename T, int LMUL, int B, int... S>
void check_values(std::integer_sequence<int, S...>)
{
	(check_value<T, LMUL, B + S>(), ...);
}

// the values B to TOTAL - 1, by blocks of 128: one fold expression of more than 256 terms exceeds the nesting limit
// of Clang (int8 of LMUL 2 with registers of 1024 bits: 257 values)
template <typename T, int LMUL, int B, int TOTAL>
void check_from()
{
	constexpr int count = TOTAL - B < 128 ? TOTAL - B : 128;
	check_values<T, LMUL, B>(std::make_integer_sequence<int, count>());
	if constexpr (B + count < TOTAL)
		check_from<T, LMUL, B + count, TOTAL>();
}

template <typename T, int LMUL>
void check_all()
{
	constexpr int n = static_cast<int>(mipp::N<T, LMUL>());
	constexpr int bits = static_cast<int>(8 * sizeof(T));
	check_from<T, LMUL, 0, (n > bits ? n : bits) + 1>();
}

TEMPLATE_TEST_CASE("immediates - constant, template and dynamic calls", "[immediates]", float, double, int8_t,
                   uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t)
{
	check_all<TestType, 1>();
	check_all<TestType, 2>();
}
} // namespace mipp_test_immediates
