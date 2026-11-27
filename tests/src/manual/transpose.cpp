// Tests of the transpositions transpose and transpose_b128 (mipp/c/transpose.h, mipp/cpp/transpose.hpp,
// mipp/obj/transpose.hpp), in the three APIs, compared with the transposition of the matrices in memory.
// Not generated: tests/src/manual/ is kept by gen_mipp_tests.py.
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

#include <mipp.h>
#include <mipp.hpp>
#include <mipp_obj.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

// a named namespace: the unity builds put several test files in one translation unit
namespace mipp_test_transpose
{
// the element (i, j) of the matrix, distinct for all the elements of a type (modulo 256 for the 8-bit integers,
// whose matrices have at most 16 rows of 16 lanes in a block)
template <typename T> T elem(std::size_t i, std::size_t j, std::size_t n) { return static_cast<T>(i * n + j + 1); }

// rows = n registers of n lanes: t[i] lane j = elem(j, i)
template <typename T, int LMUL>
void check_transpose()
{
	constexpr std::size_t n = mipp::N<T, LMUL>();
	std::vector<T> in(n * n), out(n * n);
	for (std::size_t i = 0; i < n; i++)
		for (std::size_t j = 0; j < n; j++)
			in[i * n + j] = elem<T>(i, j, n);

	// Functional API
	mipp::vd<T, LMUL> t[n];
	for (std::size_t i = 0; i < n; i++)
		t[i] = mipp::loadu<T, LMUL>(&in[i * n]);
	mipp::transpose<T, LMUL>(t);
	for (std::size_t i = 0; i < n; i++)
		mipp::storeu(&out[i * n], t[i]);
	for (std::size_t i = 0; i < n; i++)
		for (std::size_t j = 0; j < n; j++)
			REQUIRE(out[i * n + j] == in[j * n + i]);

	// Object API: T and LMUL deduced
	mipp::Vd<T, LMUL> v[n];
	for (std::size_t i = 0; i < n; i++)
		v[i] = mipp::Vd<T, LMUL>(&in[i * n]);
	mipp::transpose(v);
	for (std::size_t i = 0; i < n; i++)
		mipp::storeu(&out[i * n], v[i]);
	for (std::size_t i = 0; i < n; i++)
		for (std::size_t j = 0; j < n; j++)
			REQUIRE(out[i * n + j] == in[j * n + i]);
}

// k = 16 / sizeof(T) registers of n lanes: n / k matrices k x k side by side, one per block of 128 bits
template <typename T, int LMUL>
void check_transpose_b128()
{
	constexpr std::size_t n = mipp::N<T, LMUL>();
	constexpr std::size_t k = 16 / sizeof(T);
	std::vector<T> in(k * n), out(k * n);
	for (std::size_t i = 0; i < k; i++)
		for (std::size_t j = 0; j < n; j++)
			in[i * n + j] = elem<T>(i, j, n);

	mipp::vd<T, LMUL> t[k];
	for (std::size_t i = 0; i < k; i++)
		t[i] = mipp::loadu<T, LMUL>(&in[i * n]);
	mipp::transpose_b128<T, LMUL>(t);
	for (std::size_t i = 0; i < k; i++)
		mipp::storeu(&out[i * n], t[i]);
	// lane b k + j of the row i = lane b k + i of the row j
	for (std::size_t i = 0; i < k; i++)
		for (std::size_t b = 0; b < n / k; b++)
			for (std::size_t j = 0; j < k; j++)
				REQUIRE(out[i * n + b * k + j] == in[j * n + b * k + i]);

	mipp::Vd<T, LMUL> v[k];
	for (std::size_t i = 0; i < k; i++)
		v[i] = mipp::Vd<T, LMUL>(&in[i * n]);
	mipp::transpose_b128(v);
	for (std::size_t i = 0; i < k; i++)
		mipp::storeu(&out[i * n], v[i]);
	for (std::size_t i = 0; i < k; i++)
		for (std::size_t b = 0; b < n / k; b++)
			for (std::size_t j = 0; j < k; j++)
				REQUIRE(out[i * n + b * k + j] == in[j * n + b * k + i]);
}

// the float64 half-vectors do not exist on NEON ARMv7 (implementation_levels.md, known limitations)
#if defined(MIPP_NEON) && !defined(__aarch64__)
constexpr bool d2_64 = false;
#else
constexpr bool d2_64 = true;
#endif
template <typename T> void check_d2(std::true_type) { check_transpose<T, -2>(); }
template <typename T> void check_d2(std::false_type) {}

TEMPLATE_TEST_CASE("transpose - transpose and transpose_b128", "[transpose]", double, float, int64_t, int32_t,
                   int16_t, int8_t, uint64_t, uint32_t, uint16_t, uint8_t)
{
	check_transpose<TestType, 1>();
	check_transpose<TestType, 2>();
	check_transpose_b128<TestType, 1>();
	check_transpose_b128<TestType, 2>();
#if defined(MIPP_LDIV_2)
	check_d2<TestType>(std::integral_constant<bool, d2_64 || !std::is_same<TestType, double>::value>());
#endif
}

// C API: mipp_transpose_<type><sfx> on N registers, mipp_transpose_b128_<type><sfx> on K = 16 / sizeof(T)
#define MIPP_TEST_C_TRANSPOSE(T, NAME, SFX, N)                                                    \
	do {                                                                                          \
		const std::size_t n = (N);                                                                \
		std::vector<T> in(n * n), out(n * n);                                                     \
		for (std::size_t i = 0; i < n * n; i++) in[i] = elem<T>(i / n, i % n, n);                 \
		vd_##NAME##SFX##_t t[N];                                                                  \
		for (std::size_t i = 0; i < n; i++) t[i] = mipp_loadu_##NAME##SFX(&in[i * n]);            \
		mipp_transpose_##NAME##SFX(t);                                                            \
		for (std::size_t i = 0; i < n; i++) mipp_storeu_##NAME##SFX(&out[i * n], t[i]);           \
		for (std::size_t i = 0; i < n; i++)                                                       \
			for (std::size_t j = 0; j < n; j++) REQUIRE(out[i * n + j] == in[j * n + i]);         \
	} while (0)
#define MIPP_TEST_C_TRANSPOSE_B128(T, NAME, SFX, N)                                               \
	do {                                                                                          \
		const std::size_t n = (N), k = 16 / sizeof(T);                                            \
		std::vector<T> in(k * n), out(k * n);                                                     \
		for (std::size_t i = 0; i < k * n; i++) in[i] = elem<T>(i / n, i % n, n);                 \
		vd_##NAME##SFX##_t t[16 / sizeof(T)];                                                     \
		for (std::size_t i = 0; i < k; i++) t[i] = mipp_loadu_##NAME##SFX(&in[i * n]);            \
		mipp_transpose_b128_##NAME##SFX(t);                                                       \
		for (std::size_t i = 0; i < k; i++) mipp_storeu_##NAME##SFX(&out[i * n], t[i]);           \
		for (std::size_t i = 0; i < k; i++)                                                       \
			for (std::size_t b = 0; b < n / k; b++)                                               \
				for (std::size_t j = 0; j < k; j++)                                               \
					REQUIRE(out[i * n + b * k + j] == in[j * n + b * k + i]);                     \
	} while (0)
#define MIPP_TEST_C_TYPE(T, NAME, UNAME)                                                          \
	do {                                                                                          \
		MIPP_TEST_C_TRANSPOSE(T, NAME, , MIPP_N_##UNAME);                                         \
		MIPP_TEST_C_TRANSPOSE(T, NAME, _m2, MIPP_N_##UNAME##_M2);                                 \
		MIPP_TEST_C_TRANSPOSE_B128(T, NAME, , MIPP_N_##UNAME);                                    \
		MIPP_TEST_C_TRANSPOSE_B128(T, NAME, _m2, MIPP_N_##UNAME##_M2);                            \
	} while (0)

TEST_CASE("transpose - C API", "[transpose]")
{
	MIPP_TEST_C_TYPE(double, float64, FLOAT64);
	MIPP_TEST_C_TYPE(float, float32, FLOAT32);
	MIPP_TEST_C_TYPE(int64_t, int64, INT64);
	MIPP_TEST_C_TYPE(int32_t, int32, INT32);
	MIPP_TEST_C_TYPE(int16_t, int16, INT16);
	MIPP_TEST_C_TYPE(int8_t, int8, INT8);
	MIPP_TEST_C_TYPE(uint64_t, uint64, UINT64);
	MIPP_TEST_C_TYPE(uint32_t, uint32, UINT32);
	MIPP_TEST_C_TYPE(uint16_t, uint16, UINT16);
	MIPP_TEST_C_TYPE(uint8_t, uint8, UINT8);
#if defined(MIPP_LDIV_2)
	MIPP_TEST_C_TRANSPOSE(float, float32, _d2, MIPP_N_FLOAT32_D2);
	MIPP_TEST_C_TRANSPOSE(int16_t, int16, _d2, MIPP_N_INT16_D2);
#if MIPP_RVD_SIZE_BYTE >= 32
	MIPP_TEST_C_TRANSPOSE_B128(int8_t, int8, _d2, MIPP_N_INT8_D2);
#endif
#endif
}
} // namespace mipp_test_transpose
