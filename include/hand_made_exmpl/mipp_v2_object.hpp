#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_

#include "mipp_v2.hpp"

namespace mipp
{

template <typename T, int LMUL = 1>
class Rvd
{
public:
	rvd<T, LMUL> m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvd() {}
	Rvd(rvd<T, LMUL>  m) : m(m) {}
	Rvd(const T* data_in) { this->loadu(data_in); }

	inline void loadu (const T* data_in )       { mipp::loadu (data_in,  this->m); }
	inline void storeu(      T* data_out) const { mipp::storeu(data_out, this->m); }

	inline Rvd<T, LMUL> add      (Rvd<T, LMUL> rvd) const { return mipp::add(this->m, rvd.m); }
	inline Rvd<T, LMUL> operator+(Rvd<T, LMUL> rvd) const { return this->add(rvd);            }
};

}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */