// Special values of the complex functions that the generated tests (random parts in [-10, 10]) do not draw: the
// modulus of a complex number with a zero or an infinite part. Not generated: tests/src/manual/ is kept by
// gen_mipp_tests.py.
#include <cmath>
#include <limits>

#include <mipp.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

TEMPLATE_TEST_CASE("complex - cabs of special values", "[complex]", float, double)
{
	using T = TestType;
	constexpr int n = static_cast<int>(mipp::N<T>());
	const T inf = std::numeric_limits<T>::infinity(), big = std::numeric_limits<T>::max() / 2;
	// pairs (re, im): zero, an infinite part, both infinite, parts whose squares overflow, a regular number
	const T pairs[][2] = {{0, 0}, {inf, 1}, {-2, -inf}, {inf, inf}, {big, big}, {3, -4}};
	const int n_pairs = static_cast<int>(sizeof(pairs) / sizeof(pairs[0]));
	T a[n], r[n];
	for (int p0 = 0; p0 < n_pairs; p0 += n / 2 > 0 ? n / 2 : 1)
	{
		for (int i = 0; i < n; i++)
			a[i] = pairs[(p0 + i / 2) % n_pairs][i % 2];
		mipp::storeu(r, mipp::cabs(mipp::loadu<T>(a)));
		for (int i = 0; i + 1 < n; i += 2)
		{
			const T re = std::abs(a[i]), im = std::abs(a[i + 1]);
			const T ref = std::isinf(re) || std::isinf(im) ? inf : re == 0 && im == 0 ? T(0) : std::hypot(re, im);
			if (std::isinf(ref))
				REQUIRE(std::isinf(r[i]));
			else
				REQUIRE(std::abs(r[i] - ref) <= ref * T(1e-6));
			REQUIRE((r[i + 1] == r[i] || (std::isinf(r[i]) && std::isinf(r[i + 1]))));
		}
	}
}
