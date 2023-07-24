#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_

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


inline Rvd<T,LMUL>	notb	(const Rvd<T,LMUL> rvd)								const{ return mipp::notb(r, rvd.r);}
inline Rvd<T,LMUL>	operator~() const 					                            { return this->notb();}


inline Rvd<T,LMUL>	add	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::add(r, rvd.r);}
inline Rvd<T,LMUL>&	operator+=    (const Rvd<T,LMUL>& rvd) 									{  r = this->add(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator+     (const Rvd<T,LMUL> rvd) const 							{ return this->add(rvd);}

inline Rvd<T,LMUL>	sub	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::sub(r, rvd.r);}
inline Rvd<T,LMUL>&	operator-=    (const Rvd<T,LMUL>& rvd) 									{  r = this->sub(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator-     (const Rvd<T,LMUL> rvd) const 							{ return this->sub(rvd);}

inline Rvd<T,LMUL>	mul	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::mul(r, rvd.r);}
inline Rvd<T,LMUL>&	operator*=    (const Rvd<T,LMUL>& rvd) 									{  r = this->mul(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator*     (const Rvd<T,LMUL> rvd) const 							{ return this->mul(rvd);}

inline Rvd<T,LMUL>	div	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::div(r, rvd.r);}
inline Rvd<T,LMUL>&	operator/=    (const Rvd<T,LMUL>& rvd) 									{  r = this->div(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator/     (const Rvd<T,LMUL> rvd) const 							{ return this->div(rvd);}

inline Rvd<T,LMUL>	xorb	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::xorb(r, rvd.r);}
inline Rvd<T,LMUL>&	operator^=    (const Rvd<T,LMUL>& rvd) 									{  r = this->xorb(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator^     (const Rvd<T,LMUL> rvd) const 							{ return this->xorb(rvd);}

inline Rvd<T,LMUL>	orb	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::orb(r, rvd.r);}
inline Rvd<T,LMUL>&	operator|=    (const Rvd<T,LMUL>& rvd) 									{  r = this->orb(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator|     (const Rvd<T,LMUL> rvd) const 							{ return this->orb(rvd);}

inline Rvd<T,LMUL>	andb	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::andb(r, rvd.r);}
inline Rvd<T,LMUL>&	operator&=    (const Rvd<T,LMUL>& rvd) 									{  r = this->andb(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator&     (const Rvd<T,LMUL> rvd) const 							{ return this->andb(rvd);}

inline Rvd<T,LMUL>	cmpeq	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::cmpeq(r, rvd.r);}
inline Rvd<T,LMUL>&	operator==    (const Rvd<T,LMUL>& rvd) 									{  r = this->cmpeq(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator==     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpeq(rvd);}

inline Rvd<T,LMUL>	cmpneq	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::cmpneq(r, rvd.r);}
inline Rvd<T,LMUL>&	operator!=    (const Rvd<T,LMUL>& rvd) 									{  r = this->cmpneq(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator!=     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpneq(rvd);}

inline Rvd<T,LMUL>	cmplt	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::cmplt(r, rvd.r);}
inline Rvd<T,LMUL>&	operator<    (const Rvd<T,LMUL>& rvd) 									{  r = this->cmplt(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator<     (const Rvd<T,LMUL> rvd) const 							{ return this->cmplt(rvd);}

inline Rvd<T,LMUL>	cmple	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::cmple(r, rvd.r);}
inline Rvd<T,LMUL>&	operator<=    (const Rvd<T,LMUL>& rvd) 									{  r = this->cmple(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator<=     (const Rvd<T,LMUL> rvd) const 							{ return this->cmple(rvd);}

inline Rvd<T,LMUL>	cmpgt	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::cmpgt(r, rvd.r);}
inline Rvd<T,LMUL>&	operator>    (const Rvd<T,LMUL>& rvd) 									{  r = this->cmpgt(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator>     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpgt(rvd);}

inline Rvd<T,LMUL>	cmpge	          (const Rvd<T,LMUL> rvd)								   const{ return mipp::cmpge(r, rvd.r);}
inline Rvd<T,LMUL>&	operator>=    (const Rvd<T,LMUL>& rvd) 									{  r = this->cmpge(rvd).r; return *this; }
inline Rvd<T,LMUL>	operator>=     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpge(rvd);}


#ifndef MIPP_NO_INTRINSICS
	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }
#else
	inline T operator[](const size_t index) const { return r; }
#endif
};
// ------------------------------------------------------------------------------------------------------ operators (Msk) 
template <typename T, int LMUL = 1>
class Rvm
{

public:
	rvm<T, LMUL>  m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvm() {}
	Rvm(rvm<T, LMUL>  m) : m(m) {}

inline Rvm<T,LMUL>  cmpeq(const Rvm<T,LMUL>  rvm)             						const{ return mipp::cmpeq(m, rvm.m);}
inline Rvm<T,LMUL>& operator==(const Rvm<T,LMUL>& rvm) 								{ m = this->cmpeq(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator==(const Rvm<T,LMUL>  rvm) const 						{ return this->cmpeq(rvm);}

inline Rvm<T,LMUL>  cmpneq(const Rvm<T,LMUL>  rvm)             						const{ return mipp::cmpneq(m, rvm.m);}
inline Rvm<T,LMUL>& operator!=(const Rvm<T,LMUL>& rvm) 								{ m = this->cmpneq(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator!=(const Rvm<T,LMUL>  rvm) const 						{ return this->cmpneq(rvm);}

inline Rvm<T,LMUL>  cmplt(const Rvm<T,LMUL>  rvm)             						const{ return mipp::cmplt(m, rvm.m);}
inline Rvm<T,LMUL>& operator<(const Rvm<T,LMUL>& rvm) 								{ m = this->cmplt(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator<(const Rvm<T,LMUL>  rvm) const 						{ return this->cmplt(rvm);}

inline Rvm<T,LMUL>  cmple(const Rvm<T,LMUL>  rvm)             						const{ return mipp::cmple(m, rvm.m);}
inline Rvm<T,LMUL>& operator<=(const Rvm<T,LMUL>& rvm) 								{ m = this->cmple(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator<=(const Rvm<T,LMUL>  rvm) const 						{ return this->cmple(rvm);}

inline Rvm<T,LMUL>  cmpgt(const Rvm<T,LMUL>  rvm)             						const{ return mipp::cmpgt(m, rvm.m);}
inline Rvm<T,LMUL>& operator>(const Rvm<T,LMUL>& rvm) 								{ m = this->cmpgt(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator>(const Rvm<T,LMUL>  rvm) const 						{ return this->cmpgt(rvm);}

inline Rvm<T,LMUL>  cmpge(const Rvm<T,LMUL>  rvm)             						const{ return mipp::cmpge(m, rvm.m);}
inline Rvm<T,LMUL>& operator>=(const Rvm<T,LMUL>& rvm) 								{ m = this->cmpge(rvm).m; return *this; }
inline Rvm<T,LMUL>  operator>=(const Rvm<T,LMUL>  rvm) const 						{ return this->cmpge(rvm);}


#ifndef MIPP_NO_INTRINSICS
	inline T operator[](const size_t index) const { return mipp::get(this->m, index); }
#else
	inline T operator[](const size_t index) const { return m; }
#endif
};
}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */
