#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_
	
	namespace mipp
	{
	

	
template <typename T, int LMUL>
class Rvm;

template <typename T, int LMUL = 1>
class Rvd
{
public:
	rvd<T, LMUL> r;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvd() {}
	Rvd(rvd<T, LMUL>  r) : r(r) {}
	Rvd(const T val)     : r(mipp::set1(val)) {}
	Rvd(const T *data)   : r(mipp::load(data)){}
	~Rvd() {}
	
	inline void set(const T vals[mipp::N<T, LMUL>])       { r = mipp::set(vals);       }
	inline void set0(                  )       { r = mipp::set0<T>();       }
	inline void set1(const T val    )       { r = mipp::set1(val);       }
    inline Rvd<T,LMUL>	notb	(const Rvd<T,LMUL> rvd)	const                           { return mipp::notb(r, rvd.r);}
    inline Rvd<T,LMUL>	operator~() const 					                            { return this->notb();}
    inline void	load(const T* ptr) const 					                            { return mipp::load(ptr);}

	inline Rvd<T,LMUL>	add	          (const Rvd<T,LMUL> rvd) const                      { return mipp::add(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator +=    (const Rvd<T,LMUL>& rvd) 									{  r = this->add(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator +     (const Rvd<T,LMUL> rvd) const 							{ return this->add(rvd);}

	inline Rvd<T,LMUL>	sub	          (const Rvd<T,LMUL> rvd) const                      { return mipp::sub(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator -=    (const Rvd<T,LMUL>& rvd) 									{  r = this->sub(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator -     (const Rvd<T,LMUL> rvd) const 							{ return this->sub(rvd);}

	inline Rvd<T,LMUL>	mul	          (const Rvd<T,LMUL> rvd) const                      { return mipp::mul(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator *=    (const Rvd<T,LMUL>& rvd) 									{  r = this->mul(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator *     (const Rvd<T,LMUL> rvd) const 							{ return this->mul(rvd);}

	inline Rvd<T,LMUL>	div	          (const Rvd<T,LMUL> rvd) const                      { return mipp::div(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator /=    (const Rvd<T,LMUL>& rvd) 									{  r = this->div(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator /     (const Rvd<T,LMUL> rvd) const 							{ return this->div(rvd);}

	inline Rvd<T,LMUL>	andb	          (const Rvd<T,LMUL> rvd) const                      { return mipp::andb(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator &=    (const Rvd<T,LMUL>& rvd) 									{  r = this->andb(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator &     (const Rvd<T,LMUL> rvd) const 							{ return this->andb(rvd);}

	inline Rvd<T,LMUL>	orb	          (const Rvd<T,LMUL> rvd) const                      { return mipp::orb(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator |=    (const Rvd<T,LMUL>& rvd) 									{  r = this->orb(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator |     (const Rvd<T,LMUL> rvd) const 							{ return this->orb(rvd);}

	inline Rvd<T,LMUL>	xorb	          (const Rvd<T,LMUL> rvd) const                      { return mipp::xorb(r, rvd.r);}
	inline Rvd<T,LMUL>&	operator ^=    (const Rvd<T,LMUL>& rvd) 									{  r = this->xorb(rvd).r; return *this; }
	inline Rvd<T,LMUL>	operator ^     (const Rvd<T,LMUL> rvd) const 							{ return this->xorb(rvd);}

	inline Rvm<T,LMUL>	cmpeq	          (const Rvd<T,LMUL> rvd) const                      { return mipp::cmpeq(r, rvd.r);}
	inline Rvm<T,LMUL>	operator ==     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpeq(rvd);}

	inline Rvm<T,LMUL>	cmpneq	          (const Rvd<T,LMUL> rvd) const                      { return mipp::cmpneq(r, rvd.r);}
	inline Rvm<T,LMUL>	operator !=     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpneq(rvd);}

	inline Rvm<T,LMUL>	cmplt	          (const Rvd<T,LMUL> rvd) const                      { return mipp::cmplt(r, rvd.r);}
	inline Rvm<T,LMUL>	operator <     (const Rvd<T,LMUL> rvd) const 							{ return this->cmplt(rvd);}

	inline Rvm<T,LMUL>	cmple	          (const Rvd<T,LMUL> rvd) const                      { return mipp::cmple(r, rvd.r);}
	inline Rvm<T,LMUL>	operator <=     (const Rvd<T,LMUL> rvd) const 							{ return this->cmple(rvd);}

	inline Rvm<T,LMUL>	cmpge	          (const Rvd<T,LMUL> rvd) const                      { return mipp::cmpge(r, rvd.r);}
	inline Rvm<T,LMUL>	operator >=     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpge(rvd);}

	inline Rvm<T,LMUL>	cmpgt	          (const Rvd<T,LMUL> rvd) const                      { return mipp::cmpgt(r, rvd.r);}
	inline Rvm<T,LMUL>	operator >     (const Rvd<T,LMUL> rvd) const 							{ return this->cmpgt(rvd);}

	inline T operator[](const size_t index) const { return mipp::get(this->r, index); }

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
    Rvm(const int32_t vals[mipp::N<T, LMUL>]) : m(mipp::set_k<T>(vals)) {}
    inline Rvd<T,LMUL> toReg() const                              { return Rvd<T,LMUL>(mipp::toreg(this->m)); }
    inline void set_k(const int32_t vals[mipp::N<T, LMUL>])       { m = mipp::set_k<T>(vals); }
	inline void set0_k()                                          { m = mipp::set0_k<T>(); }
	inline void set1_k(const int32_t val)                         { m = mipp::set1_k<T>(val); }
	inline int32_t get(const size_t index) const                  { return mipp::get(m, index); }

    inline Rvm<T,LMUL>  cmpeq(const Rvm<T,LMUL>  rvm) const                 { return mipp::cmpeq(m, rvm.m);}
    inline Rvm<T,LMUL>& operator==(const Rvm<T,LMUL>& rvm) 			 { m = this->cmpeq(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator==(const Rvm<T,LMUL>  rvm) const  { return this->cmpeq(rvm);}

    inline Rvm<T,LMUL>  cmpneq(const Rvm<T,LMUL>  rvm) const                 { return mipp::cmpneq(m, rvm.m);}
    inline Rvm<T,LMUL>& operator!=(const Rvm<T,LMUL>& rvm) 			 { m = this->cmpneq(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator!=(const Rvm<T,LMUL>  rvm) const  { return this->cmpneq(rvm);}

    inline Rvm<T,LMUL>  cmplt(const Rvm<T,LMUL>  rvm) const                 { return mipp::cmplt(m, rvm.m);}
    inline Rvm<T,LMUL>& operator<(const Rvm<T,LMUL>& rvm) 			 { m = this->cmplt(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator<(const Rvm<T,LMUL>  rvm) const  { return this->cmplt(rvm);}

    inline Rvm<T,LMUL>  cmple(const Rvm<T,LMUL>  rvm) const                 { return mipp::cmple(m, rvm.m);}
    inline Rvm<T,LMUL>& operator<=(const Rvm<T,LMUL>& rvm) 			 { m = this->cmple(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator<=(const Rvm<T,LMUL>  rvm) const  { return this->cmple(rvm);}

    inline Rvm<T,LMUL>  cmpgt(const Rvm<T,LMUL>  rvm) const                 { return mipp::cmpgt(m, rvm.m);}
    inline Rvm<T,LMUL>& operator>(const Rvm<T,LMUL>& rvm) 			 { m = this->cmpgt(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator>(const Rvm<T,LMUL>  rvm) const  { return this->cmpgt(rvm);}

    inline Rvm<T,LMUL>  cmpge(const Rvm<T,LMUL>  rvm) const                 { return mipp::cmpge(m, rvm.m);}
    inline Rvm<T,LMUL>& operator>=(const Rvm<T,LMUL>& rvm) 			 { m = this->cmpge(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator>=(const Rvm<T,LMUL>  rvm) const  { return this->cmpge(rvm);}

    inline Rvm<T,LMUL>  xorb(const Rvm<T,LMUL>  rvm) const                 { return mipp::xorb(m, rvm.m);}
    inline Rvm<T,LMUL>& operator^=(const Rvm<T,LMUL>& rvm) 			 { m = this->xorb(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator^(const Rvm<T,LMUL>  rvm) const  { return this->xorb(rvm);}

    inline Rvm<T,LMUL>  orb(const Rvm<T,LMUL>  rvm) const                 { return mipp::orb(m, rvm.m);}
    inline Rvm<T,LMUL>& operator|=(const Rvm<T,LMUL>& rvm) 			 { m = this->orb(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator|(const Rvm<T,LMUL>  rvm) const  { return this->orb(rvm);}

    inline Rvm<T,LMUL>  andb(const Rvm<T,LMUL>  rvm) const                 { return mipp::andb(m, rvm.m);}
    inline Rvm<T,LMUL>& operator&=(const Rvm<T,LMUL>& rvm) 			 { m = this->andb(rvm).m; return *this; }
    inline Rvm<T,LMUL>  operator&(const Rvm<T,LMUL>  rvm) const  { return this->andb(rvm);}

	inline T operator[](const size_t index) const { return mipp::get(this->m, index); }
};
}
	
#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */
