// Fine-grained headers check. Requires headers generated with `--granularity fine`.
//
// g++ mipp_fine_grained.cpp -I../include -Wall -mavx2 -o mipp_fine_grained.bin
//
// This file must include ONLY atomic headers (mipp/{cpp,obj}/fun/<variant>/<lmul>/<func>.hpp) and never
// an umbrella (mipp.hpp, mipp_obj.hpp, mipp/{cpp,obj}/fun/<func>.hpp, mipp/{cpp,obj}/cat/...).
// Each atom must be self-sufficient: if one of them silently relies on another granule (for instance a `_k`
// partner or another variant) being included, this file stops compiling or computing the right result.
// The CI greps the includes of this file to enforce that rule.

#include <cstdint>
#include <cstdio>

// --- C++ object API, unmasked (u), LMUL = 1 ---------------------------------------------------------------------
#include <mipp/obj/fun/u/m1/loadu.hpp>
#include <mipp/obj/fun/u/m1/storeu.hpp>
#include <mipp/obj/fun/u/m1/add.hpp>
#include <mipp/obj/fun/u/m1/cmpeq.hpp>
#include <mipp/obj/fun/u/m1/hadd.hpp>
#include <mipp/obj/fun/u/m1/cast.hpp>   // also exercises the `cast_k` partner pulled at the same granule
#include <mipp/obj/fun/u/m1/cvt.hpp>

// --- C++ object API, masked variants (m, z, s), LMUL = 1 --------------------------------------------------------
#include <mipp/obj/fun/m/m1/add.hpp>
#include <mipp/obj/fun/z/m1/add.hpp>
#include <mipp/obj/fun/s/m1/add.hpp>

// --- C++ object API, LMUL = 2 -----------------------------------------------------------------------------------
#include <mipp/obj/fun/u/m2/loadu.hpp>
#include <mipp/obj/fun/u/m2/storeu.hpp>
#include <mipp/obj/fun/u/m2/add.hpp>

// --- C++ functional API (does not depend on the obj layer) ------------------------------------------------------
#include <mipp/cpp/fun/u/m1/loadu.hpp>
#include <mipp/cpp/fun/u/m1/storeu.hpp>
#include <mipp/cpp/fun/u/m1/mul.hpp>

static int errors = 0;

#define CHECK(cond)                                                                                              \
	do {                                                                                                         \
		if (!(cond)) {                                                                                           \
			std::printf("CHECK FAILED (line %d): %s\n", __LINE__, #cond);                                        \
			errors++;                                                                                            \
		}                                                                                                        \
	} while (0)

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	// ---- LMUL = 1 -------------------------------------------------------------------------------------------
	constexpr int N = mipp::N<float, 1>();

	float a[N], b[N], c[N], src[N];
	for (int i = 0; i < N; i++) {
		a[i] = (float)i;
		b[i] = 1.f;
		src[i] = 100.f;
	}

	const mipp::Rvd<float, 1> ra = mipp::loadu_obj<float, 1>(a);
	const mipp::Rvd<float, 1> rb = mipp::loadu_obj<float, 1>(b);
	const mipp::Rvd<float, 1> rs = mipp::loadu_obj<float, 1>(src);

	// unmasked add + operator
	mipp::storeu(c, mipp::add(ra, rb));
	for (int i = 0; i < N; i++) CHECK(c[i] == a[i] + b[i]);

	mipp::storeu(c, ra + rb);
	for (int i = 0; i < N; i++) CHECK(c[i] == a[i] + b[i]);

	// compare -> mask (lane 1 is the only one where a[i] == b[i])
	const mipp::Rvm<float, 1> m = mipp::cmpeq(ra, rb);

	// masked variants: only the active lane (1) has a well defined result for M, zero for Z, `src` for S
	if (N > 1) {
		mipp::storeu(c, mipp::add(m, ra, rb)); // VARIANT M (default)
		CHECK(c[1] == a[1] + b[1]);

		mipp::storeu(c, mipp::add<mipp::Z>(m, ra, rb)); // VARIANT Z
		CHECK(c[1] == a[1] + b[1]);
		for (int i = 0; i < N; i++)
			if (i != 1) CHECK(c[i] == 0.f);

		mipp::storeu(c, mipp::add(m, rs, ra, rb)); // VARIANT S (default for 4 arguments)
		CHECK(c[1] == a[1] + b[1]);
		for (int i = 0; i < N; i++)
			if (i != 1) CHECK(c[i] == src[i]);
	}

	// reduction
	float sum = 0.f;
	for (int i = 0; i < N; i++) sum += a[i];
	CHECK(mipp::hadd(ra) == sum);

	// cast (float <-> int32 bit reinterpretation) round trip, goes through the `cast_k` partner overloads
	const mipp::Rvd<int32_t, 1> ri = mipp::cast<int32_t>(ra);
	const mipp::Rvd<float, 1> rf = mipp::cast<float>(ri);
	mipp::storeu(c, rf);
	for (int i = 0; i < N; i++) CHECK(c[i] == a[i]);

	// value conversion float -> int32
	int32_t ci[N];
	mipp::storeu(ci, mipp::cvt<int32_t>(ra));
	for (int i = 0; i < N; i++) CHECK(ci[i] == (int32_t)a[i]);

	// ---- LMUL = 2 -------------------------------------------------------------------------------------------
	constexpr int N2 = mipp::N<float, 2>();

	float a2[N2], b2[N2], c2[N2];
	for (int i = 0; i < N2; i++) {
		a2[i] = (float)i;
		b2[i] = 2.f;
	}
	const mipp::Rvd<float, 2> ra2 = mipp::loadu_obj<float, 2>(a2);
	const mipp::Rvd<float, 2> rb2 = mipp::loadu_obj<float, 2>(b2);
	mipp::storeu(c2, ra2 + rb2);
	for (int i = 0; i < N2; i++) CHECK(c2[i] == a2[i] + b2[i]);

	// ---- C++ functional API ---------------------------------------------------------------------------------
	mipp::rvd<float, 1> fa = mipp::loadu<float, 1>(a);
	mipp::rvd<float, 1> fb = mipp::loadu<float, 1>(b);
	mipp::storeu(c, mipp::mul(fa, fb));
	for (int i = 0; i < N; i++) CHECK(c[i] == a[i] * b[i]);

	if (errors == 0)
		std::printf("mipp_fine_grained: OK\n");
	return errors == 0 ? 0 : 1;
}
