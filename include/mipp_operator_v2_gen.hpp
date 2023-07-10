#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OPERATORS_HPP_


namespace mipp
{

template <typename T, int LMUL = 1>
class Rvd
{
public:
	rvd<T, LMUL> r;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvd() {}
	Rvd(rvd<T, LMUL>  r) : r(r) {}
// ------------------------------------------------------------------------------------------------------ operators 

inline Rvd<T>& operator+= (const Rvd<T>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<T> operator+= (const Rvd<T>& rvd) const { return this->add(rvd); }

inline Rvd<T>& operator+ (const Rvd<T>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<T> operator+ (const Rvd<T>& rvd) const { return this->add(rvd); }

inline Rvd<T>& operator-= (const Rvd<T>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<T> operator-= (const Rvd<T>& rvd) const { return this->sub(rvd); }

inline Rvd<T>& operator- (const Rvd<T>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<T> operator- (const Rvd<T>& rvd) const { return this->sub(rvd); }

inline Rvd<T>& operator*= (const Rvd<T>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<T> operator*= (const Rvd<T>& rvd) const { return this->mul(rvd); }

inline Rvd<T>& operator* (const Rvd<T>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<T> operator* (const Rvd<T>& rvd) const { return this->mul(rvd); }

inline Rvd<T>& operator/= (const Rvd<T>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<T> operator/= (const Rvd<T>& rvd) const { return this->div(rvd); }

inline Rvd<T>& operator/ (const Rvd<T>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<T> operator/ (const Rvd<T>& rvd) const { return this->div(rvd); }

inline Rvd<T>& operator~ (const Rvd<T>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<T> operator~ (const Rvd<T>& rvd) const { return this->notb(rvd); }

inline Rvd<T>& operator^= (const Rvd<T>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<T> operator^= (const Rvd<T>& rvd) const { return this->xorb(rvd); }

inline Rvd<T>& operator^ (const Rvd<T>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<T> operator^ (const Rvd<T>& rvd) const { return this->xorb(rvd); }

inline Rvd<T>& operator|= (const Rvd<T>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<T> operator|= (const Rvd<T>& rvd) const { return this->orb(rvd); }

inline Rvd<T>& operator| (const Rvd<T>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<T> operator| (const Rvd<T>& rvd) const { return this->orb(rvd); }

inline Rvd<T>& operator&= (const Rvd<T>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<T> operator&= (const Rvd<T>& rvd) const { return this->andb(rvd); }

inline Rvd<T>& operator& (const Rvd<T>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<T> operator& (const Rvd<T>& rvd) const { return this->andb(rvd); }

inline Rvd<T>& operator== (const Rvd<T>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<T> operator== (const Rvd<T>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<T>& operator!= (const Rvd<T>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<T> operator!= (const Rvd<T>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<T>& operator< (const Rvd<T>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<T> operator< (const Rvd<T>& rvd) const { return this->cmplt(rvd); }

inline Rvd<T>& operator<= (const Rvd<T>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<T> operator<= (const Rvd<T>& rvd) const { return this->cmple(rvd); }

inline Rvd<T>& operator> (const Rvd<T>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<T> operator> (const Rvd<T>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<T>& operator>= (const Rvd<T>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<T> operator>= (const Rvd<T>& rvd) const { return this->cmpge(rvd); }

inline Rvd<T>& operator== (const Rvd<T>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<T> operator== (const Rvd<T>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<T>& operator!= (const Rvd<T>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<T> operator!= (const Rvd<T>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<T>& operator< (const Rvd<T>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<T> operator< (const Rvd<T>& rvd) const { return this->cmplt(rvd); }

inline Rvd<T>& operator<= (const Rvd<T>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<T> operator<= (const Rvd<T>& rvd) const { return this->cmple(rvd); }

inline Rvd<T>& operator> (const Rvd<T>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<T> operator> (const Rvd<T>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<T>& operator>= (const Rvd<T>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<T> operator>= (const Rvd<T>& rvd) const { return this->cmpge(rvd); }
}
// ------------------------------------------------------------------------------------------------------ operators (Msk) 
class Rvm
{
public:
	rvm<T, LMUL>  m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvm() {}
	Rvm(rvm<T, LMUL>  m) : m(m) {}

inline Rvm<N<T>()> operator== (rvm<T> rvm) const { return this->cmpeq (rvm);}

inline Rvm<N<T>()> operator!= (rvm<T> rvm) const { return this->cmpneq (rvm);}

inline Rvm<N<T>()> operator< (rvm<T> rvm) const { return this->cmplt (rvm);}

inline Rvm<N<T>()> operator<= (rvm<T> rvm) const { return this->cmple (rvm);}

inline Rvm<N<T>()> operator> (rvm<T> rvm) const { return this->cmpgt (rvm);}

inline Rvm<N<T>()> operator>= (rvm<T> rvm) const { return this->cmpge (rvm);}
}
#ifndef MIPP_NO_INTRINSICS
	inline bool operator[](const size_t index) const { return mipp::get<N>(this->, index); }
#else
	inline bool operator[](const size_t index) const { return m; }
#endif
};
}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */
