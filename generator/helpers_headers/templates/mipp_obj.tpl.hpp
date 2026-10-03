#pragma once

#include <cstring>
#include <type_traits>
#include "mipp/internal/interfaces/cpp/common.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/loadu.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set1_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/load/set_k.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get.hpp"
#include "mipp/internal/interfaces/cpp/functions/store/get_k.hpp"

namespace mipp
{

namespace details
{
template <typename T>
inline bool mask_get_val(T val, std::true_type)
{
	typedef typename std::conditional<sizeof(T) == 8, uint64_t, uint32_t>::type uint_t;
	uint_t bits = 0;
	std::memcpy(&bits, &val, sizeof(bits));
	return bits != 0;
}

template <typename T>
inline bool mask_get_val(T val, std::false_type)
{
	return val != 0;
}
} // namespace details

template <typename T, int LMUL = 1>
struct Rvd
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvd<T, LMUL> r;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	inline Rvd() = default;
	inline Rvd(rvd<T, LMUL> r0) : r(r0) {}
	inline Rvd(const T val) : r(mipp::set1<T, LMUL>(val)) {}
	inline Rvd(const T *p0) : r(mipp::loadu<T, LMUL>(p0)) {}

	// Implicit conversion to underlying functional SIMD register (C++ Func interop)
	inline operator rvd<T, LMUL>() const { return this->r; }
	inline Rvd& operator=(const rvd<T, LMUL>& r0) { this->r = r0; return *this; }
	inline Rvd& operator=(const T val) { this->r = mipp::set1<T, LMUL>(val); return *this; }

	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }
};

template <typename T, int LMUL = 1>
struct Rvm
{
	using value_type = T;
	static constexpr int lmul = LMUL;
	rvm<T, LMUL> m;

	static constexpr int N() { return mipp::N<T, LMUL>(); }

	inline Rvm() = default;
	inline Rvm(rvm<T, LMUL> m0) : m(m0) {}
	inline Rvm(const bool val) : m(mipp::set1_k<T, LMUL>(val ? 1 : 0)) {}
	inline Rvm(const int32_t vals[mipp::N<T, LMUL>()]) : m(mipp::set_k<T, LMUL>(vals)) {}

	// Implicit conversion to underlying functional SIMD mask (C++ Func interop)
	inline operator rvm<T, LMUL>() const { return this->m; }
	inline Rvm& operator=(const rvm<T, LMUL>& m0) { this->m = m0; return *this; }
	inline Rvm& operator=(const bool val) { this->m = mipp::set1_k<T, LMUL>(val ? 1 : 0); return *this; }

	inline bool operator[](const size_t index) const {
		return details::mask_get_val<T>(mipp::get(this->m, index), typename std::is_floating_point<T>::type());
	}
};

} // namespace mipp
