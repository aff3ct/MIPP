// Tests of the scalar forms that the generated tests do not cover (generator/helpers_headers/forms.py): the C aliases
// of the base form `vv`, and the C++ overloads of the base function in the three APIs.
// Not generated: tests/src/manual/ is kept by gen_mipp_tests.py.
#include <cstdint>

#include <mipp.h>
#include <mipp.hpp>
#include <mipp_obj.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("forms - vv aliases and overloads", "[forms]")
{
	constexpr int n = MIPP_N_FLOAT32;
	float a[n], b[n], r[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = static_cast<float>(i) - 2.f;
		b[i] = static_cast<float>(3 * i % 7);
	}
	const rvd_float32_t va = mipp_loadu_float32(a);
	const rvd_float32_t vb = mipp_loadu_float32(b);

	// C: mipp_<f>_vv_<...> is the base function
	mipp_storeu_float32(r, mipp_sub_vv_float32(va, vb));
	for (int i = 0; i < n; i++)
		REQUIRE(r[i] == a[i] - b[i]);
	mipp_storeu_float32_m1(r, mipp_fmadd_vv_float32_m1(va, vb, va));
	for (int i = 0; i < n; i++)
		REQUIRE(r[i] == a[i] * b[i] + a[i]);

	// C++ Functional: the forms are overloads of the base name
	mipp::storeu(r, mipp::sub(2.f, va));
	for (int i = 0; i < n; i++)
		REQUIRE(r[i] == 2.f - a[i]);
	mipp::storeu(r, mipp::clamp(va, 0.f, 3.f));
	for (int i = 0; i < n; i++)
		REQUIRE(r[i] == (a[i] < 0.f ? 0.f : (a[i] > 3.f ? 3.f : a[i])));

	// C++ Object: same overloads, T deduced from the register and the scalar
	const mipp::Rvd<float> oa(a);
	const mipp::Rvd<float> oc = mipp::fmadd(oa, oa, 1.f);
	const mipp::Rvm<float> om = mipp::cmpge(1.f, oa);
	for (int i = 0; i < n; i++)
	{
		REQUIRE(oc[i] == a[i] * a[i] + 1.f);
		REQUIRE(om[i] == (1.f >= a[i]));
	}

	// shifts: a count per lane (lshift) or the same count (lshift_vs, mipp::lshift(r, n))
	int32_t x[MIPP_N_INT32], c[MIPP_N_INT32];
	for (int i = 0; i < MIPP_N_INT32; i++)
	{
		x[i] = i - 3;
		c[i] = i % 4;
	}
	const mipp::Rvd<int32_t> ox(x), occ(c);
	const mipp::Rvd<int32_t> l1 = ox << occ;
	const mipp::Rvd<int32_t> l2 = mipp::lshift(ox, 2);
	for (int i = 0; i < MIPP_N_INT32; i++)
	{
		REQUIRE(l1[i] == static_cast<int32_t>(static_cast<uint32_t>(x[i]) << c[i]));
		REQUIRE(l2[i] == static_cast<int32_t>(static_cast<uint32_t>(x[i]) << 2));
	}
}
