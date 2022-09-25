#include "mipp.h"

template <typename T>
class Reg;

template <typename T> inline Reg<T> add(const Reg<T> v1, const Reg<T> v2);
template <typename T> inline Reg<T> sub(const Reg<T> v1, const Reg<T> v2);
template <typename T> inline Reg<T> mul(const Reg<T> v1, const Reg<T> v2);
template <typename T> inline Reg<T> div(const Reg<T> v1, const Reg<T> v2);
template <typename T> inline Reg<T> min(const Reg<T> v1, const Reg<T> v2);
template <typename T> inline Reg<T> max(const Reg<T> v1, const Reg<T> v2);

template <typename T>
class Reg_2;

template <typename T>
class Regx2;

template <int N>
class Msk;

template <typename T>
class Reg
{
public:
#ifndef MIPP_NO_INTRINSICS
	reg r;
#else
	T r;
#endif

#ifndef MIPP_NO_INTRINSICS
	Reg(                            )                         {}
	Reg(const reg r                 ) : r(r)                  {}
	Reg(const T   val               ) : r(mipp::set1<T>(val)) {}
//	Reg(const T   vals[mipp::N<T>()]) : r(mipp::set <T>(vals)){}
	Reg(const T  *data              ) : r(mipp::load<T>(data)){}

	Reg(const std::initializer_list<T> &l)
	{
		if (l.size() >= (unsigned)mipp::nElReg<T>())
			r = mipp::loadu<T>(l.begin());
		else
			throw std::runtime_error("mipp::Reg<T>: invalid 'initializer_list' size.");
	}

	~Reg() {}
#else
	Reg(                )              {}
	Reg(const T  val    ) : r(val)     {}
	Reg(const T  vals[1]) : r(vals[0]) {}
//	Reg(const T *data   ) : r(data[0]) {}

	Reg(const std::initializer_list<T> &l)
	{
		auto vec = mipp::vector<T>(mipp::nElReg<T>());
		vec = l;
		r = vec[0];
	}

	~Reg() = default;
#endif

#ifndef MIPP_NO_INTRINSICS
	static inline Reg<T> cmask (const uint32_t mask[nElReg<T>()  ]) { return mipp::cmask <T>(mask); }
	static inline Reg<T> cmask2(const uint32_t mask[nElReg<T>()/2]) { return mipp::cmask2<T>(mask); }
	static inline Reg<T> cmask4(const uint32_t mask[nElReg<T>()/4]) { return mipp::cmask4<T>(mask); }
#else
	static inline Reg<T> cmask (const uint32_t mask[1]) { return Reg<T>((T)0);          }
	static inline Reg<T> cmask2(const uint32_t mask[1]) { return Reg<T>((T)0);          }
	static inline Reg<T> cmask4(const uint32_t mask[1]) { return Reg<T>((T)0);          }
#endif

	static inline void transpose(Reg<T> regs[nElReg<T>()])
	{
#ifndef MIPP_NO_INTRINSICS
		reg rs[nElReg<T>()];
		for (auto i = 0; i < nElReg<T>(); i++) rs[i] = regs[i].r;
		mipp::transpose<T>(rs);
		for (auto i = 0; i < nElReg<T>(); i++) regs[i].r = rs[i];
#endif
	}

	static inline void transpose8x8(Reg<T> regs[8])
	{
#ifndef MIPP_NO_INTRINSICS
		reg rs[8];
		for (auto i = 0; i < 8; i++) rs[i] = regs[i].r;
		mipp::transpose8x8<T>(rs);
		for (auto i = 0; i < 8; i++) regs[i].r = rs[i];
#else
		throw std::runtime_error("mipp::Reg<T>::transpose8x8: non-sense in sequential mode.");
#endif
	}

	static inline void transpose2(Reg<T> regs[nElReg<T>()/2])
	{
#ifndef MIPP_NO_INTRINSICS
		reg rs[nElReg<T>()/2];
		for (auto i = 0; i < nElReg<T>()/2; i++) rs[i] = regs[i].r;
		mipp::transpose2<T>(rs);
		for (auto i = 0; i < nElReg<T>()/2; i++) regs[i].r = rs[i];
#else
		throw std::runtime_error("mipp::Reg<T>::transpose2: non-sense in sequential mode.");
#endif
	}

	static inline void transpose28x8(Reg<T> regs[8])
	{
#ifndef MIPP_NO_INTRINSICS
		reg rs[8];
		for (auto i = 0; i < 8; i++) rs[i] = regs[i].r;
		mipp::transpose28x8<T>(rs);
		for (auto i = 0; i < 8; i++) regs[i].r = rs[i];
#else
		throw std::runtime_error("mipp::Reg<T>::transpose28x8: non-sense in sequential mode.");
#endif
	}

#ifndef MIPP_NO_INTRINSICS
	inline void        set0         ()                                           { r = mipp::set0<T>();                           }
	inline void        set1         (const T val)                                { r = mipp::set1<T>(val);                        }
	inline void        set          (const T vals[mipp::N<T>()])                 { r = mipp::set <T>(vals);                       }
	inline void        load         (const T* data)                              { r = mipp::load<T>(data);                       }
	inline void        loadu        (const T* data)                              { r = mipp::loadu<T>(data);                      }
	inline void        store        (T* data)                              const { mipp::store<T>(data, r);                       }
	inline void        storeu       (T* data)                              const { mipp::storeu<T>(data, r);                      }
	inline T           get          (const size_t index)                   const { return mipp::get<T>(r, index);                 }
	inline T           getfirst     ()                                     const { return mipp::getfirst<T>(r);                   }
	inline Reg_2<T>    low          ()                                     const { return mipp::low <T>(r);                       }
	inline Reg_2<T>    high         ()                                     const { return mipp::high<T>(r);                       }
	inline Reg<T>      shuff        (const Reg<T> v_shu)                   const { return mipp::shuff        <T>(r, v_shu.r);     }
	inline Reg<T>      shuff2       (const Reg<T> v_shu)                   const { return mipp::shuff2       <T>(r, v_shu.r);     }
	inline Reg<T>      shuff4       (const Reg<T> v_shu)                   const { return mipp::shuff4       <T>(r, v_shu.r);     }
	inline Reg<T>      interleavelo (const Reg<T> v)                       const { return mipp::interleavelo <T>(r, v.r);         }
	inline Reg<T>      interleavehi (const Reg<T> v)                       const { return mipp::interleavehi <T>(r, v.r);         }
	inline Reg<T>      interleavelo2(const Reg<T> v)                       const { return mipp::interleavelo2<T>(r, v.r);         }
	inline Reg<T>      interleavehi2(const Reg<T> v)                       const { return mipp::interleavehi2<T>(r, v.r);         }
	inline Reg<T>      interleavelo4(const Reg<T> v)                       const { return mipp::interleavelo4<T>(r, v.r);         }
	inline Reg<T>      interleavehi4(const Reg<T> v)                       const { return mipp::interleavehi4<T>(r, v.r);         }
	inline Regx2<T>    interleave   (const Reg<T> v)                       const { return mipp::interleave   <T>(r, v.r);         }
	inline Regx2<T>    deinterleave (const Reg<T> v)                       const { return mipp::deinterleave <T>(r, v.r);         }
	inline Regx2<T>    interleave2  (const Reg<T> v)                       const { return mipp::interleave2  <T>(r, v.r);         }
	inline Regx2<T>    interleave4  (const Reg<T> v)                       const { return mipp::interleave4  <T>(r, v.r);         }
	inline Reg<T>      interleave   ()                                     const { return mipp::interleave   <T>(r);              }
	inline Regx2<T>    interleavex2 (const Reg<T> v)                       const { return mipp::interleavex2 <T>(r, v.r);         }
	inline Reg<T>      interleavex4 ()                                     const { return mipp::interleavex4 <T>(r);              }
	inline Reg<T>      interleavex16()                                     const { return mipp::interleavex16<T>(r);              }
	inline Reg<T>      andb         (const Reg<T> v)                       const { return mipp::andb         <T>(r, v.r);         }
	inline Reg<T>      andnb        (const Reg<T> v)                       const { return mipp::andnb        <T>(r, v.r);         }
	inline Reg<T>      notb         ()                                     const { return mipp::notb         <T>(r);              }
	inline Reg<T>      orb          (const Reg<T> v)                       const { return mipp::orb          <T>(r, v.r);         }
	inline Reg<T>      xorb         (const Reg<T> v)                       const { return mipp::xorb         <T>(r, v.r);         }
	inline Reg<T>      lshift       (const uint32_t n)                     const { return mipp::lshift       <T>(r, n);           }
	inline Reg<T>      lshiftr      (const Reg<T> v)                       const { return mipp::lshiftr      <T>(r, v.r);         }
	inline Reg<T>      rshift       (const uint32_t n)                     const { return mipp::rshift       <T>(r, n);           }
	inline Reg<T>      rshiftr      (const Reg<T> v)                       const { return mipp::rshiftr      <T>(r, v.r);         }
	inline Msk<N<T>()> cmpeq        (const Reg<T> v)                       const { return mipp::cmpeq        <T>(r, v.r);         }
	inline Msk<N<T>()> cmpneq       (const Reg<T> v)                       const { return mipp::cmpneq       <T>(r, v.r);         }
	inline Msk<N<T>()> cmplt        (const Reg<T> v)                       const { return mipp::cmplt        <T>(r, v.r);         }
	inline Msk<N<T>()> cmple        (const Reg<T> v)                       const { return mipp::cmple        <T>(r, v.r);         }
	inline Msk<N<T>()> cmpgt        (const Reg<T> v)                       const { return mipp::cmpgt        <T>(r, v.r);         }
	inline Msk<N<T>()> cmpge        (const Reg<T> v)                       const { return mipp::cmpge        <T>(r, v.r);         }
	inline Reg<T>      add          (const Reg<T> v)                       const { return mipp::add          <T>(r, v.r);         }
	inline Reg<T>      sub          (const Reg<T> v)                       const { return mipp::sub          <T>(r, v.r);         }
	inline Reg<T>      mul          (const Reg<T> v)                       const { return mipp::mul          <T>(r, v.r);         }
	inline Reg<T>      div          (const Reg<T> v)                       const { return mipp::div          <T>(r, v.r);         }
	inline Reg<T>      min          (const Reg<T> v)                       const { return mipp::min          <T>(r, v.r);         }
	inline Reg<T>      max          (const Reg<T> v)                       const { return mipp::max          <T>(r, v.r);         }
	inline Reg<T>      msb          ()                                     const { return mipp::msb          <T>(r);              }
	inline Reg<T>      msb          (const Reg<T> v)                       const { return mipp::msb          <T>(r, v.r);         }
	inline Msk<N<T>()> sign         ()                                     const { return mipp::sign         <T>(r);              }
	inline Reg<T>      neg          (const Reg<T> v)                       const { return mipp::neg          <T>(r, v.r);         }
	inline Reg<T>      neg          (const Msk<N<T>()> v)                  const { return mipp::neg          <T>(r, v.m);         }
	inline Reg<T>      copysign     (const Reg<T> v)                       const { return mipp::copysign     <T>(r, v.r);         }
	inline Reg<T>      copysign     (const Msk<N<T>()> v)                  const { return mipp::copysign     <T>(r, v.m);         }
	inline Reg<T>      abs          ()                                     const { return mipp::abs          <T>(r);              }
	inline Reg<T>      sqrt         ()                                     const { return mipp::sqrt         <T>(r);              }
	inline Reg<T>      rsqrt        ()                                     const { return mipp::rsqrt        <T>(r);              }
	inline Reg<T>      log          ()                                     const { return mipp::log          <T>(r);              }
	inline Reg<T>      exp          ()                                     const { return mipp::exp          <T>(r);              }
	inline Reg<T>      sin          ()                                     const { return mipp::sin          <T>(r);              }
	inline Reg<T>      cos          ()                                     const { return mipp::cos          <T>(r);              }
	inline Reg<T>      tan          ()                                     const { return mipp::tan          <T>(r);              }
	inline void        sincos       (      Reg<T> &s,       Reg<T> &c)     const {        mipp::sincos       <T>(r,  s.r,  c.r);  }
	inline Regx2<T>    sincos       ()                                     const { return mipp::sincos       <T>(r);              }
	inline Regx2<T>    cossin       ()                                     const { return mipp::cossin       <T>(r);              }
	inline Reg<T>      sinh         ()                                     const { return mipp::sinh         <T>(r);              }
	inline Reg<T>      cosh         ()                                     const { return mipp::cosh         <T>(r);              }
	inline Reg<T>      tanh         ()                                     const { return mipp::tanh         <T>(r);              }
	inline Reg<T>      asinh        ()                                     const { return mipp::asinh        <T>(r);              }
	inline Reg<T>      acosh        ()                                     const { return mipp::acosh        <T>(r);              }
	inline Reg<T>      atanh        ()                                     const { return mipp::atanh        <T>(r);              }
//	inline Reg<T>      csch         ()                                     const { return mipp::csch         <T>(r);              }
//	inline Reg<T>      sech         ()                                     const { return mipp::sech         <T>(r);              }
//	inline Reg<T>      coth         ()                                     const { return mipp::coth         <T>(r);              }
//	inline Reg<T>      acsch        ()                                     const { return mipp::acsch        <T>(r);              }
//	inline Reg<T>      asech        ()                                     const { return mipp::asech        <T>(r);              }
//	inline Reg<T>      acoth        ()                                     const { return mipp::acoth        <T>(r);              }
	inline Reg<T>      fmadd        (const Reg<T> v1, const Reg<T> v2)     const { return mipp::fmadd        <T>(r, v1.r, v2.r);  }
	inline Reg<T>      fnmadd       (const Reg<T> v1, const Reg<T> v2)     const { return mipp::fnmadd       <T>(r, v1.r, v2.r);  }
	inline Reg<T>      fmsub        (const Reg<T> v1, const Reg<T> v2)     const { return mipp::fmsub        <T>(r, v1.r, v2.r);  }
	inline Reg<T>      fnmsub       (const Reg<T> v1, const Reg<T> v2)     const { return mipp::fnmsub       <T>(r, v1.r, v2.r);  }
	inline Reg<T>      blend        (const Reg<T> v1, const Msk<N<T>()> m) const { return mipp::blend        <T>(r, v1.r,  m.m);  }
	inline Reg<T>      lrot         ()                                     const { return mipp::lrot         <T>(r);              }
	inline Reg<T>      rrot         ()                                     const { return mipp::rrot         <T>(r);              }
	inline Reg<T>      div2         ()                                     const { return mipp::div2         <T>(r);              }
	inline Reg<T>      div4         ()                                     const { return mipp::div4         <T>(r);              }
	inline Reg<T>      sat          (T min, T max)                         const { return mipp::sat          <T>(r, min, max);    }
	inline Reg<T>      round        ()                                     const { return mipp::round        <T>(r);              }
	inline Reg<T>      trunc        ()                                     const { return mipp::trunc        <T>(r);              }
	inline bool        testz        (const Reg<T> v)                       const { return mipp::testz        <T>(r, v.r);         }
	inline bool        testz        ()                                     const { return mipp::testz        <T>(r);              }
#else
	inline void        set0         ()                                           { r = 0;                                         }
	inline void        set1         (const T val)                                { r = val;                                       }
	inline void        set          (const T vals[1])                            { r = vals[0];                                   }
	inline void        load         (const T* data)                              { r = data[0];                                   }
	inline void        loadu        (const T* data)                              { r = data[0];                                   }
	inline void        store        (T* data)                              const { data[0] = r;                                   }
	inline void        storeu       (T* data)                              const { data[0] = r;                                   }
	inline T           get          (const size_t index)                   const { return r;                                      }
	inline T           getfirst     ()                                     const { return r;                                      }
	inline Reg_2<T>    low          ()                                     const { return r;                                      }
	inline Reg_2<T>    high         ()                                     const { return r;                                      }
	inline Reg<T>      shuff        (const Reg<T> v_shu)                   const { return *this;                                  }
	inline Reg<T>      shuff2       (const Reg<T> v_shu)                   const { return *this;                                  }
	inline Reg<T>      shuff4       (const Reg<T> v_shu)                   const { return *this;                                  }
	inline Reg<T>      interleavelo (const Reg<T> v)                       const { return *this;                                  }
	inline Reg<T>      interleavehi (const Reg<T> v)                       const { return *this;                                  }
	inline Reg<T>      interleavelo2(const Reg<T> v)                       const { return *this;                                  }
	inline Reg<T>      interleavehi2(const Reg<T> v)                       const { return *this;                                  }
	inline Reg<T>      interleavelo4(const Reg<T> v)                       const { return *this;                                  }
	inline Reg<T>      interleavehi4(const Reg<T> v)                       const { return *this;                                  }
	inline Regx2<T>    interleave   (const Reg<T> v)                       const { return Regx2<T>(*this, v);                     }
	inline Regx2<T>    deinterleave (const Reg<T> v)                       const { return Regx2<T>(*this, v);                     }
	inline Regx2<T>    interleave2  (const Reg<T> v)                       const { return Regx2<T>(*this, v);                     }
	inline Regx2<T>    interleave4  (const Reg<T> v)                       const { return Regx2<T>(*this, v);                     }
	inline Reg<T>      interleave   ()                                     const { return *this;                                  }
	inline Regx2<T>    interleavex2 (const Reg<T> v)                       const { return Regx2<T>(*this, v);                     }
	inline Reg<T>      interleavex4 ()                                     const { return *this;                                  }
	inline Reg<T>      interleavex16()                                     const { return *this;                                  }
	inline Reg<T>      andb         (const Reg<T> v)                       const { return mipp_scop::andb<T>( r, v.r);            }
	inline Reg<T>      andnb        (const Reg<T> v)                       const { return mipp_scop::andb<T>(~r, v.r);            }
	inline Reg<T>      notb         ()                                     const { return ~r;                                     }
	inline Reg<T>      orb          (const Reg<T> v)                       const { return  r  |  v.r;                             }
	inline Reg<T>      xorb         (const Reg<T> v)                       const { return mipp_scop::xorb<T>(r, v.r);             }
	inline Reg<T>      lshift       (const uint32_t n)                     const { return mipp_scop::lshift<T>(r, n);             }
	inline Reg<T>      lshiftr      (const Reg<T> v)                       const { return mipp_scop::lshift<T>(r, (uint32_t)v.r); }
	inline Reg<T>      rshift       (const uint32_t n)                     const { return mipp_scop::rshift<T>(r, n);             }
	inline Reg<T>      rshiftr      (const Reg<T> v)                       const { return mipp_scop::rshift<T>(r, (uint32_t)v.r); }
	inline Msk<N<T>()> cmpeq        (const Reg<T> v)                       const { return (msk)(r  == v.r);                       }
	inline Msk<N<T>()> cmpneq       (const Reg<T> v)                       const { return (msk)(r  != v.r);                       }
	inline Msk<N<T>()> cmplt        (const Reg<T> v)                       const { return (msk)(r  <  v.r);                       }
	inline Msk<N<T>()> cmple        (const Reg<T> v)                       const { return (msk)(r  <= v.r);                       }
	inline Msk<N<T>()> cmpgt        (const Reg<T> v)                       const { return (msk)(r  >  v.r);                       }
	inline Msk<N<T>()> cmpge        (const Reg<T> v)                       const { return (msk)(r  >= v.r);                       }
	inline Reg<T>      add          (const Reg<T> v)                       const { return mipp_scop::add<T>(r,v.r);               }
	inline Reg<T>      sub          (const Reg<T> v)                       const { return mipp_scop::sub<T>(r,v.r);               }
	inline Reg<T>      mul          (const Reg<T> v)                       const { return r  *  v.r;                              }
	inline Reg<T>      div          (const Reg<T> v)                       const { return r  /  v.r;                              }
	inline Reg<T>      min          (const Reg<T> v)                       const { return std::min<T>(r, v.r);                    }
	inline Reg<T>      max          (const Reg<T> v)                       const { return std::max<T>(r, v.r);                    }
	// (1 = positive, -1 = negative, 0 = 0)
	inline Reg<T>      msb          ()                                     const { return mipp_scop::msb<T>(r);                   }
	inline Reg<T>      msb          (const Reg<T> v)                       const { return msb(Reg<T>(r ^ v.r));                   }
	inline Msk<N<T>()> sign         ()                                     const { return r < 0;                                  }
	inline Reg<T>      neg          (const Reg<T> v)                       const { return v.r >= 0 ? Reg<T>(r) : Reg<T>(-r);      }
	inline Reg<T>      neg          (const Msk<N<T>()> v)                  const { return v.m == 0 ? Reg<T>(r) : Reg<T>(-r);      }
	inline Reg<T>      copysign     (const Reg<T> v)                       const { return this->neg(v);                           }
	inline Reg<T>      copysign     (const Msk<N<T>()> v)                  const { return this->neg(v);                           }
	inline Reg<T>      abs          ()                                     const { return std::abs(r);                            }
	inline Reg<T>      sqrt         ()                                     const { return (T)std::sqrt(r);                        }
	inline Reg<T>      rsqrt        ()                                     const { return (T)(1 / std::sqrt(r));                  }
	inline Reg<T>      log          ()                                     const { return (T)std::log(r);                         }
	inline Reg<T>      exp          ()                                     const { return (T)std::exp(r);                         }
	inline Reg<T>      sin          ()                                     const { return (T)std::sin(r);                         }
	inline Reg<T>      cos          ()                                     const { return (T)std::cos(r);                         }
	inline Reg<T>      tan          ()                                     const { return (T)std::tan(r);                         }
	inline void        sincos       (      Reg<T> &s,       Reg<T> &c)     const { s = std::sin(r); c = std::cos(r);              }
	inline Regx2<T>    sincos       ()                                     const { return Regx2<T>(std::sin(r), std::cos(r));     }
	inline Regx2<T>    cossin       ()                                     const { return Regx2<T>(std::cos(r), std::sin(r));     }
	inline Reg<T>      sinh         ()                                     const { return (T)std::sinh(r);                        }
	inline Reg<T>      cosh         ()                                     const { return (T)std::cosh(r);                        }
	inline Reg<T>      tanh         ()                                     const { return (T)std::tanh(r);                        }
	inline Reg<T>      asinh        ()                                     const { return (T)std::asinh(r);                       }
	inline Reg<T>      acosh        ()                                     const { return (T)std::acosh(r);                       }
	inline Reg<T>      atanh        ()                                     const { return (T)std::atanh(r);                       }
	inline Reg<T>      fmadd        (const Reg<T> v1, const Reg<T> v2)     const { return   r * v1.r + v2.r;                      }
	inline Reg<T>      fnmadd       (const Reg<T> v1, const Reg<T> v2)     const { return v2.r -(r * v1.r);                       }
	inline Reg<T>      fmsub        (const Reg<T> v1, const Reg<T> v2)     const { return   r * v1.r - v2.r;                      }
	inline Reg<T>      fnmsub       (const Reg<T> v1, const Reg<T> v2)     const { return -v2.r - (r * v1.r) ;                    }
	inline Reg<T>      blend        (const Reg<T> v1, const Msk<N<T>()> m) const { return (m.m) ? r : v1.r;                       }
	inline Reg<T>      lrot         ()                                     const { return r;                                      }
	inline Reg<T>      rrot         ()                                     const { return r;                                      }
	inline Reg<T>      div2         ()                                     const { return mipp_scop::div2<T>(r);                  }
	inline Reg<T>      div4         ()                                     const { return mipp_scop::div4<T>(r);                  }
	inline Reg<T>      sat          (T min, T max)                         const { return std::min(std::max(r, min), max);        }
	inline Reg<T>      round        ()                                     const { return std::round(r);                          }
	inline Reg<T>      trunc        ()                                     const { return std::trunc(r);                          }
	inline bool        testz        (const Reg<T> v)                       const { return mipp_scop::andb<T>(r, v.r) == 0 ? 1 : 0;}
	inline bool        testz        ()                                     const { return !r;                                     }
#endif
	inline Reg<T>      andb         (const Msk<N<T>()> m)                  const { return this->andb (m.template toReg<T>().r); }
	inline Reg<T>      andnb        (const Msk<N<T>()> m)                  const { return this->andnb(m.template toReg<T>().r); }
	inline Reg<T>      orb          (const Msk<N<T>()> m)                  const { return this->orb  (m.template toReg<T>().r); }
	inline Reg<T>      xorb         (const Msk<N<T>()> m)                  const { return this->xorb (m.template toReg<T>().r); }

#ifndef MIPP_NO_INTRINSICS
	template <typename TI>
	inline void gather(const T* mem, const Reg<TI> idx)
	{
		auto r = mipp::gather<T,TI>(mem, idx.r);
		this->r = r;
	}
	template <typename TI>
	inline void scatter(T* mem, const Reg<TI> idx) const
	{
		mipp::scatter<T,TI>(mem, idx.r, this->r);
	}
#else
	template <typename TI>
	inline void gather(const T* mem, const Reg<TI> idx)
	{
		this->r = mem[idx.r];
	}
	template <typename TI>
	inline void scatter(T* mem, const Reg<TI> idx) const
	{
		mem[idx.r] = this->r;
	}
#endif

#ifndef MIPP_NO_INTRINSICS
	template <typename T2> inline Reg<T2> cvt ()               const { return mipp::cvt<T,T2>(r);       }
	template <typename T2> inline Reg<T2> pack(const Reg<T> v) const { return mipp::pack<T,T2>(r, v.r); }
	template <typename T2> inline Reg<T2> cast()               const { return Reg<T2>(this->r);         }
#else
	template <typename T2> inline Reg<T2> cvt ()               const { return (T2)std::round(r);        }
	template <typename T2> inline Reg<T2> pack(const Reg<T> v) const
	{
		throw std::runtime_error("mipp::Reg<T>::pack: non-sense in sequential mode.");
	}
	template <typename T2> inline Reg<T2> cast()               const { return Reg<T2>((T2)this->r);     }
#endif

	inline Reg<T>& operator+= (const Reg<T>      &v)       { r =    this->add(v).r;    return *this;  }
	inline Reg<T>  operator+  (const Reg<T>       v) const { return this->add(v);                     }

	inline Reg<T>& operator-= (const Reg<T>      &v)       { r =    this->sub(v).r;    return *this;  }
	inline Reg<T>  operator-  (const Reg<T>       v) const { return this->sub(v);                     }
	inline Reg<T>  operator-  (                    ) const { return mipp::sub<T>(mipp::set0<T>(), r); }

	inline Reg<T>& operator*= (const Reg<T>      &v)       { r =    this->mul(v).r;    return *this;  }
	inline Reg<T>  operator*  (const Reg<T>       v) const { return this->mul(v);                     }

	inline Reg<T>& operator/= (const Reg<T>      &v)       { r =    this->div(v).r;    return *this;  }
	inline Reg<T>  operator/  (const Reg<T>       v) const { return this->div(v);                     }

	inline Reg<T>  operator~  (                    )       { return this->notb();                     }

	inline Reg<T>& operator^= (const Reg<T>      &v)       { r =    this->xorb(v).r;   return *this;  }
	inline Reg<T>  operator^  (const Reg<T>       v) const { return this->xorb(v);                    }
//	inline Reg<T>& operator^= (const Msk<N<T>()> &v)       { r =    this->xorb(v).r;   return *this;  }
//	inline Reg<T>  operator^  (const Msk<N<T>()>  v) const { return this->xorb(v);                    }

	inline Reg<T>& operator|= (const Reg<T>      &v)       { r =    this->orb(v).r;    return *this;  }
	inline Reg<T>  operator|  (const Reg<T>       v) const { return this->orb(v);                     }
//	inline Reg<T>& operator|= (const Msk<N<T>()> &v)       { r =    this->orb(v).r;    return *this;  }
//	inline Reg<T>  operator|  (const Msk<N<T>()>  v) const { return this->orb(v);                     }

	inline Reg<T>& operator&= (const Reg<T>      &v)       { r =    this->andb(v).r;   return *this;  }
	inline Reg<T>  operator&  (const Reg<T>       v) const { return this->andb(v);                    }
//	inline Reg<T>& operator&= (const Msk<N<T>()> &v)       { r =    this->andb(v).r;   return *this;  }
//	inline Reg<T>  operator&  (const Msk<N<T>()>  v) const { return this->andb(v);                    }

	inline Reg<T>& operator<<=(const uint32_t     n)       { r =    this->lshift(n).r; return *this;  }
	inline Reg<T>  operator<< (const uint32_t     n) const { return this->lshift(n);                  }

	inline Reg<T>& operator<<=(const Reg<T>      &v)       { r =    this->lshiftr(v).r; return *this; }
	inline Reg<T>  operator<< (const Reg<T>       v) const { return this->lshiftr(v);                 }

	inline Reg<T>& operator>>=(const uint32_t     n)       { r =    this->rshift(n).r; return *this;  }
	inline Reg<T>  operator>> (const uint32_t     n) const { return this->rshift(n);                  }

	inline Reg<T>& operator>>=(const Reg<T>      &v)       { r =    this->rshiftr(v).r; return *this; }
	inline Reg<T>  operator>> (const Reg<T>       v) const { return this->rshiftr(v);                 }

	inline Msk<N<T>()> operator==(Reg<T> v) const { return this->cmpeq (v); }
	inline Msk<N<T>()> operator!=(Reg<T> v) const { return this->cmpneq(v); }
	inline Msk<N<T>()> operator< (Reg<T> v) const { return this->cmplt (v); }
	inline Msk<N<T>()> operator<=(Reg<T> v) const { return this->cmple (v); }
	inline Msk<N<T>()> operator> (Reg<T> v) const { return this->cmpgt (v); }
	inline Msk<N<T>()> operator>=(Reg<T> v) const { return this->cmpge (v); }

#ifndef MIPP_NO_INTRINSICS
	inline T operator[](const size_t index) const { return this->get(index); }
#else
	inline T operator[](const size_t index) const { return r; }
#endif

	// ------------------------------------------------------------------------------------------------------ reduction
#ifndef MIPP_NO_INTRINSICS
	inline T sum () const { return Reduction<T,mipp::add>::sapply(*this); }
	inline T hadd() const { return Reduction<T,mipp::add>::sapply(*this); }
	inline T hmul() const { return Reduction<T,mipp::mul>::sapply(*this); }
	inline T hmin() const { return Reduction<T,mipp::min>::sapply(*this); }
	inline T hmax() const { return Reduction<T,mipp::max>::sapply(*this); }
#else
	inline T sum () const { return this->r; }
	inline T hadd() const { return this->r; }
	inline T hmul() const { return this->r; }
	inline T hmin() const { return this->r; }
	inline T hmax() const { return this->r; }
#endif

	// -------------------------------------------------------------------------------------------------------- masking
	template <proto_I1<T> I1>
	inline Reg<T> mask(const Msk<N<T>()> m, const Reg<T> src) const
	{
		return mipp::mask<T, I1>(m, src, *this);
	}

	template <proto_I2<T> I2>
	inline Reg<T> mask(const Msk<N<T>()> m, const Reg<T> src, const Reg<T> b) const
	{
		return mipp::mask<T, I2>(m, src, *this, b);
	}

	template <proto_I3<T> I3>
	inline Reg<T> mask(const Msk<N<T>()> m, const Reg<T> src, const Reg<T> b, const Reg<T> c) const
	{
		return mipp::mask<T, I3>(m, src, *this, b, c);
	}

	template <proto_I1<T> I1>
	inline Reg<T> maskz(const Msk<N<T>()> m) const
	{
		return mipp::maskz<T, I1>(m, *this);
	}

	template <proto_I2<T> I2>
	inline Reg<T> maskz(const Msk<N<T>()> m, const Reg<T> b) const
	{
		return mipp::maskz<T, I2>(m, *this, b);
	}

	template <proto_I3<T> I3>
	inline Reg<T> maskz(const Msk<N<T>()> m, const Reg<T> b, const Reg<T> c) const
	{
		return mipp::maskz<T, I3>(m, *this, b, c);
	}

	template <proto_IL<T> IL = mipp::oloadu<T>>
	inline void maskzld(const Msk<N<T>()> m, const T* memp)
	{
		mipp::Reg<T> r = mipp::maskzld<T, IL>(m, memp);
		this->r = r;
	}

	template <proto_IL<T> IL = mipp::oloadu<T>, proto_IS<T> IS = mipp::storeu<T>>
	inline void maskzlds(const Msk<N<T>()> m, const T* memp)
	{
		mipp::Reg<T> r = mipp::maskzld<T, IL, IS>(m, memp);
		this->r = r;
	}

	template <proto_IS<T> IS = mipp::storeu<T>, proto_IL<T> IL = mipp::oloadu<T>>
	inline void maskst(const Msk<N<T>()> m, T* memp) const
	{
		return mipp::maskst<T, IS, IL>(m, memp, *this);
	}

	template <proto_IS<T> IS = mipp::storeu<T>>
	inline void masksts(const Msk<N<T>()> m, T* memp) const
	{
		return mipp::masksts<T, IS>(m, memp, *this);
	}

	template <typename TI>
	inline void maskzgat(const Msk<N<T>()> m, const T* memp, const Reg<TI> idx)
	{
		mipp::Reg<T> r = mipp::maskzgat(m, memp, idx);
		this->r = r;
	}

	template <typename TI>
	inline void masksca(const Msk<N<T>()> m, T* memp, const Reg<TI> idx) const
	{
		mipp::masksca(m, memp, idx, *this);
	}
};

template <int N>
class Msk
{
public:
	msk m;

	Msk(){}
	Msk(const msk m) : m(m) {}

#ifndef MIPP_NO_INTRINSICS
	Msk(const bool val    ) : m(mipp::set1<N>(val) ) {}
	Msk(const bool vals[N]) : m(mipp::set <N>(vals)) {}
	Msk(const std::initializer_list<bool> &l)
	{
		if ((int)l.size() >= N)
			m = mipp::set<N>(l.begin());
		else
			throw std::runtime_error("mipp::Msk<N>: invalid 'initializer_list' size.");
	}

#else
	Msk(const bool val    ) : m(val     ? ~0 : 0) {}
	Msk(const bool vals[N]) : m(vals[0] ? ~0 : 0) {}
	Msk(const std::initializer_list<bool> &l)
	{
		auto vec = std::vector<bool>(N);
		vec = l;
		m = vec[0] ? ~0 : 0;
	}

#endif

#ifndef MIPP_NO_INTRINSICS
	template <typename T>
	inline Reg<T> toReg() const
	{
		static_assert(mipp::N<T>() == N, "mipp::Msk<N>: T type is invalid.");
		return Reg<T>(mipp::toreg<N>(this->m));
	}
#else
	template <typename T>
	inline Reg<T> toReg() const
	{
		return this->m ? (T)1 : (T)0;
	}
#endif

	~Msk() = default;

#ifndef MIPP_NO_INTRINSICS
	inline void set     (const bool vals[N])       { m = mipp::set <N>(vals);       }
	inline void set0    (                  )       { m = mipp::set0<N>(    );       }
	inline void set1    (const bool val    )       { m = mipp::set1<N>(val );       }
	inline bool get     (const size_t index) const { return mipp::get<N>(m, index); }
	inline bool getfirst(                  ) const { return mipp::getfirst<N>(m);   }
#else
	inline void set     (const bool vals[N])       { m = *vals ? ~0 : 0; }
	inline void set0    (                  )       { m = 0;              }
	inline void set1    (const bool val    )       { m = val ? ~0 : 0;   }
	inline bool get     (const size_t index) const { return m;           }
	inline bool getfirst(                  ) const { return m;           }
#endif

#ifndef MIPP_NO_INTRINSICS
	inline Msk<N> andb  (const Msk<N>   v) const { return mipp::andb  <N>(m, v.m); }
	inline Msk<N> andnb (const Msk<N>   v) const { return mipp::andnb <N>(m, v.m); }
	inline Msk<N> notb  ()                 const { return mipp::notb  <N>(m);      }
	inline Msk<N> orb   (const Msk<N>   v) const { return mipp::orb   <N>(m, v.m); }
	inline Msk<N> xorb  (const Msk<N>   v) const { return mipp::xorb  <N>(m, v.m); }
	inline Msk<N> lshift(const uint32_t n) const { return mipp::lshift<N>(m, n);   }
	inline Msk<N> rshift(const uint32_t n) const { return mipp::rshift<N>(m, n);   }
	inline bool   testz (const Msk<N>   v) const { return mipp::testz <N>(m, v.m); }
	inline bool   testz ()                 const { return mipp::testz <N>(m);      }
#else
	inline Msk<N> andb  (const Msk<N>   v) const { return mipp_scop::andb<msk>( m, v.m);                  }
	inline Msk<N> andnb (const Msk<N>   v) const { return mipp_scop::andb<msk>(~m, v.m);                  }
	inline Msk<N> notb  ()                 const { return (msk)~m;                                        }
	inline Msk<N> orb   (const Msk<N>   v) const { return (msk)(m | v.m);                                 }
	inline Msk<N> xorb  (const Msk<N>   v) const { return mipp_scop::xorb  <msk>(m, v.m);                 }
	inline Msk<N> lshift(const uint32_t n) const { return mipp_scop::lshift<msk>(m, n * sizeof(msk) * 8); }
	inline Msk<N> rshift(const uint32_t n) const { return mipp_scop::rshift<msk>(m, n * sizeof(msk) * 8); }
	inline bool   testz (const Msk<N>   v) const { return mipp_scop::andb  <msk>(m, v.m) == 0 ? 1 : 0;    }
	inline bool   testz ()                 const { return !m;                                             }
#endif

	template <typename T> inline Reg<T> andb  (const Reg<T> v)  const { return this->toReg<T>().andb (v); }
	template <typename T> inline Reg<T> andnb (const Reg<T> v)  const { return this->toReg<T>().andnb(v); }
	template <typename T> inline Reg<T> orb   (const Reg<T> v)  const { return this->toReg<T>().orb  (v); }
	template <typename T> inline Reg<T> xorb  (const Reg<T> v)  const { return this->toReg<T>().xorb (v); }

	inline Msk<N>  operator~  (                )       { return this->notb();                    }

//	template <typename T>
//	inline Reg<T>  operator^  (const Reg<T>   v) const { return this->xorb(v);                   }
	inline Msk<N>& operator^= (const Msk<N>  &v)       { m =    this->xorb(v).m;  return *this;  }
	inline Msk<N>  operator^  (const Msk<N>   v) const { return this->xorb(v);                   }

//	template <typename T>
//	inline Reg<T>  operator|  (const Reg<T>   v) const { return this->orb(v);                    }
	inline Msk<N>& operator|= (const Msk<N>  &v)       { m =    this->orb(v).m;   return *this;  }
	inline Msk<N>  operator|  (const Msk<N>   v) const { return this->orb(v);                    }

//	template <typename T>
//	inline Reg<T>  operator&  (const Reg<T>   v) const { return this->andb(v);                   }
	inline Msk<N>& operator&= (const Msk<N>  &v)       { m =    this->andb(v).m;  return *this;  }
	inline Msk<N>  operator&  (const Msk<N>   v) const { return this->andb(v);                   }

	inline Msk<N>& operator<<=(const uint32_t n)       { m =    this->lshift(n).m; return *this; }
	inline Msk<N>  operator<< (const uint32_t n) const { return this->lshift(n);                 }

	inline Msk<N>& operator>>=(const uint32_t n)       { m =    this->rshift(n).m; return *this; }
	inline Msk<N>  operator>> (const uint32_t n) const { return this->rshift(n);                 }

#ifndef MIPP_NO_INTRINSICS
	inline bool operator[](const size_t index) const { return this->get(index); }
#else
	inline bool operator[](const size_t index) const { return m; }
#endif
};

template <typename T>
class Reg_2
{
public:
#ifndef MIPP_NO_INTRINSICS
	reg_2 r;
#else
	T r;
#endif

#ifndef MIPP_NO_INTRINSICS
	Reg_2(const reg_2 r) : r(r)   {}
#else
	Reg_2(const T val  ) : r(val) {}
#endif

	virtual ~Reg_2() = default;

#ifndef MIPP_NO_INTRINSICS
	template <typename T2> inline Reg<T2> cvt() const { return mipp::cvt<T,T2>(r); }
#else
	template <typename T2> inline Reg<T2> cvt() const { return (T2)std::round(r);  }
#endif

#ifndef MIPP_NO_INTRINSICS
	inline T get       (const size_t index) const { return mipp::get<T>(r, index); }
	inline T getfirst  (                  ) const { return mipp::getfirst<T>(r);   }
	inline T operator[](const size_t index) const { return this->get(index);       }
#else
	inline T get       (const size_t index) const { return r; }
	inline T getfirst  (                  ) const { return r; }
	inline T operator[](const size_t index) const { return r; }
#endif

#ifndef MIPP_NO_INTRINSICS
	inline Reg<T> combine(const Reg_2 v) const { return mipp::combine<T>(r, v.r); }
#else
	inline Reg<T> combine(const Reg_2 v) const
	{
		throw std::runtime_error("Impossible to make the 'mipp::combine' operation in the 'MIPP_NO_INTRINSICS' mode.");
	}
#endif
};

template <typename T>
class Regx2
{
public:
	Reg<T> val[2];

	Regx2(                    )                                                                {}
	Regx2(Reg<T> r1, Reg<T> r2) : val{r1, r2}                                                  {}
#ifndef MIPP_NO_INTRINSICS
	Regx2(regx2 r2            ) : val{Reg<T>(r2.val[0]), Reg<T>(r2.val[1])}                    {}
	Regx2(const T  *data      ) : val{mipp::load<T>(data), mipp::load<T>(data + mipp::N<T>())} {}
#else
	Regx2(const T  vals[2]    ) : val{vals[0], vals[1]}                                        {}
#endif

	inline       Reg<T>& operator[](size_t index)       { return val[index]; }
	inline const Reg<T>& operator[](size_t index) const { return val[index]; }

	~Regx2() = default;

#ifndef MIPP_NO_INTRINSICS
	inline void     load        (const T* data   )       { val[0] = mipp::load <T>(data); val[1] = mipp::load <T>(data + mipp::N<T>());           }
	inline void     loadu       (const T* data   )       { val[0] = mipp::loadu<T>(data); val[1] = mipp::loadu<T>(data + mipp::N<T>());           }
	inline void     store       (T* data         ) const { mipp::store <T>(data, val[0].r); mipp::store <T>(data + mipp::N<T>(), val[1].r);       }
	inline void     storeu      (T* data         ) const { mipp::storeu<T>(data, val[0].r); mipp::storeu<T>(data + mipp::N<T>(), val[1].r);       }
	inline Regx2<T> interleave  (                ) const { return mipp::interleave  <T>(*(mipp::regx2*)this);                                     }
	inline Regx2<T> deinterleave(                ) const { return mipp::deinterleave<T>(*(mipp::regx2*)this);                                     }
	inline Regx2<T> conj        (                ) const { return mipp::conj        <T>(*(mipp::regx2*)this);                                     }
	inline Reg  <T> norm        (                ) const { return mipp::norm        <T>(*(mipp::regx2*)this);                                     }
	inline Regx2<T> cadd        (const Regx2<T> v) const { return mipp::cadd        <T>(*(mipp::regx2*)this, *(regx2*)&v);                        }
	inline Regx2<T> csub        (const Regx2<T> v) const { return mipp::csub        <T>(*(mipp::regx2*)this, *(regx2*)&v);                        }
	inline Regx2<T> cmul        (const Regx2<T> v) const { return mipp::cmul        <T>(*(mipp::regx2*)this, *(regx2*)&v);                        }
	inline Regx2<T> cmulconj    (const Regx2<T> v) const { return mipp::cmulconj    <T>(*(mipp::regx2*)this, *(regx2*)&v);                        }
	inline Regx2<T> cdiv        (const Regx2<T> v) const { return mipp::cdiv        <T>(*(mipp::regx2*)this, *(regx2*)&v);                        }
#else
	inline void     load        (const T* data   )       { val[0] = data[0]; val[1] = data[1];                                                    }
	inline void     loadu       (const T* data   )       { val[0] = data[0]; val[1] = data[1];                                                    }
	inline void     store       (T* data         ) const { data[0] = val[0]; data[1] = val[1];                                                    }
	inline void     storeu      (T* data         ) const { data[0] = val[0]; data[1] = val[1];                                                    }
	inline Regx2<T> interleave  (                ) const { return *this;                                                                          }
	inline Regx2<T> deinterleave(                ) const { return *this;                                                                          }
	inline Regx2<T> conj        (                ) const { return Regx2<T>(val[0].r, -val[1].r);                                                  }
	inline Reg  <T> norm        (                ) const { return val[0].r * val[0].r + val[1].r * val[1].r;                                      }
	inline Regx2<T> cadd        (const Regx2<T> v) const { return mipp::Regx2<T>(val[0].r + v.val[0].r, val[1].r + v.val[1].r);                   }
	inline Regx2<T> csub        (const Regx2<T> v) const { return mipp::Regx2<T>(val[0].r - v.val[0].r, val[1].r - v.val[1].r);                   }
	inline Regx2<T> cmul(const Regx2<T> v) const
	{
		auto re = val[0].r * v.val[0].r - val[1].r * v.val[1].r;
		auto im = val[0].r * v.val[1].r + val[1].r * v.val[0].r;
		return Regx2<T>(re, im);
	}
	inline Regx2<T> cmulconj(const Regx2<T> v) const
	{
		auto re = val[0].r * v.val[0].r + val[1].r * v.val[1].r;
		auto im = val[1].r * v.val[0].r - val[0].r * v.val[1].r;
		return Regx2<T>(re, im);
	}
	inline Regx2<T> cdiv(const Regx2<T> v) const
	{
		auto norm = v.val[0].r * v.val[0].r + v.val[1].r * v.val[1].r;
		auto re = (val[0].r * v.val[0].r + val[1].r * v.val[1].r) / norm;
		auto im = (val[1].r * v.val[0].r - val[0].r * v.val[1].r) / norm;
		return Regx2<T>(re, im);
	}
#endif

	inline Regx2<T>& operator+=(const Regx2<T> &v)       { auto res = this->cadd(v); val[0] = res.val[0]; val[1] = res.val[1]; return *this; }
	inline Regx2<T>  operator+ (const Regx2<T>  v) const { return this->cadd(v);                                                             }

	inline Regx2<T>& operator-=(const Regx2<T> &v)       { auto res = this->csub(v); val[0] = res.val[0]; val[1] = res.val[1]; return *this; }
	inline Regx2<T>  operator- (const Regx2<T>  v) const { return this->csub(v);                                                             }

	inline Regx2<T>& operator*=(const Regx2<T> &v)       { auto res = this->cmul(v); val[0] = res.val[0]; val[1] = res.val[1]; return *this; }
	inline Regx2<T>  operator* (const Regx2<T>  v) const { return this->cmul(v);                                                             }

	inline Regx2<T>& operator/=(const Regx2<T> &v)       { auto res = this->cdiv(v); val[0] = res.val[0]; val[1] = res.val[1]; return *this; }
	inline Regx2<T>  operator/ (const Regx2<T>  v) const { return this->cdiv(v);                                                             }
};

#ifndef MIPP_NO_INTRINSICS
template <typename T>
std::ostream& operator<<(std::ostream& os, const Reg<T>& r)
{
	dump<T>(r.r, os); return os;
}

template <int N>
std::ostream& operator<<(std::ostream& os, const Msk<N>& m)
{
	dump<N>(m.m, os); return os;
}
#else
template <typename T>
std::ostream& operator<<(std::ostream& os, const Reg<T>& r)
{
	os << +r.r;
	return os;
}

template <int N>
std::ostream& operator<<(std::ostream& os, const Msk<N>& m)
{
	os << (m.m ? 1 : 0);
	return os;
}
#endif

template <typename T> inline Reg<T>      oload        (const T* in)                                           { Reg<T> r; r.load (in); return r; }
template <typename T> inline Reg<T>      oloadu       (const T* in)                                           { Reg<T> r; r.loadu(in); return r; }
template <typename T> inline void        store        (T* out, const Reg<T> v)                                { v.store (out);                   }
template <typename T> inline void        storeu       (T* out, const Reg<T> v)                                { v.storeu(out);                   }
template <typename T> inline Reg<T>      oset         (const T in[N<T>()])                                    { Reg<T> r; r.set(in);   return r; }
#ifdef _MSC_VER
template <int      N> inline Msk<N>      oset         (const bool in[])                                       { Msk<N> m; m.set(in);   return m; }
#else
template <int      N> inline Msk<N>      oset         (const bool in[N])                                      { Msk<N> m; m.set(in);   return m; }
#endif
template <typename T> inline T           get          (const Reg<T> v, const size_t index)                    { return v.get(index);             }
template <typename T> inline T           get          (const Reg_2<T> v, const size_t index)                  { return v.get(index);             }
template <int      N> inline bool        get          (const Msk<N> m, const size_t index)                    { return m.get(index);             }
template <typename T> inline T           getfirst     (const Reg<T> v)                                        { return v.getfirst();             }
template <typename T> inline T           getfirst     (const Reg_2<T> v)                                      { return v.getfirst();             }
template <int      N> inline bool        getfirst     (const Msk<N> m)                                        { return m.getfirst();             }
template <typename T> inline Reg<T>      oset1        (const T val)                                           { Reg<T> r; r.set1(val); return r; }
template <int      N> inline Msk<N>      oset1        (const bool val)                                        { Msk<N> m; m.set1(val); return m; }
template <typename T> inline Reg<T>      oset0        ()                                                      { Reg<T> r; r.set0();    return r; }
template <int      N> inline Msk<N>      oset0        ()                                                      { Msk<N> m; m.set0();    return m; }
template <typename T> inline Reg_2<T>    low          (const Reg<T> v)                                        { return v.low();                  }
template <typename T> inline Reg_2<T>    high         (const Reg<T> v)                                        { return v.high();                 }
template <typename T> inline Reg<T>      shuff        (const Reg<T> v1, const Reg<T> v2)                      { return v1.shuff(v2);             }
template <typename T> inline Reg<T>      shuff2       (const Reg<T> v1, const Reg<T> v2)                      { return v1.shuff2(v2);            }
template <typename T> inline Reg<T>      shuff4       (const Reg<T> v1, const Reg<T> v2)                      { return v1.shuff4(v2);            }
template <typename T> inline Reg<T>      interleavelo (const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavelo(v2);      }
template <typename T> inline Reg<T>      interleavehi (const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavehi(v2);      }
template <typename T> inline Reg<T>      interleavelo2(const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavelo2(v2);     }
template <typename T> inline Reg<T>      interleavehi2(const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavehi2(v2);     }
template <typename T> inline Reg<T>      interleavelo4(const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavelo4(v2);     }
template <typename T> inline Reg<T>      interleavehi4(const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavehi4(v2);     }
template <typename T> inline Regx2<T>    interleave   (const Reg<T> v1, const Reg<T> v2)                      { return v1.interleave(v2);        }
template <typename T> inline Regx2<T>    interleave   (const Regx2<T> v)                                      { return v.interleave();           }
template <typename T> inline Regx2<T>    deinterleave (const Reg<T> v1, const Reg<T> v2)                      { return v1.deinterleave(v2);      }
template <typename T> inline Regx2<T>    deinterleave (const Regx2<T> v)                                      { return v.deinterleave();         }
template <typename T> inline Regx2<T>    interleave2  (const Reg<T> v1, const Reg<T> v2)                      { return v1.interleave2(v2);       }
template <typename T> inline Regx2<T>    interleave4  (const Reg<T> v1, const Reg<T> v2)                      { return v1.interleave4(v2);       }
template <typename T> inline Reg<T>      interleave   (const Reg<T> v)                                        { return v.interleave();           }
template <typename T> inline Regx2<T>    interleavex2 (const Reg<T> v1, const Reg<T> v2)                      { return v1.interleavex2(v2);      }
template <typename T> inline Reg<T>      interleavex4 (const Reg<T> v)                                        { return v.interleavex4();         }
template <typename T> inline Reg<T>      interleavex16(const Reg<T> v)                                        { return v.interleavex16();        }
template <typename T> inline Reg<T>      andb         (const Reg<T> v1, const Reg<T> v2)                      { return v1.andb(v2);              }
template <int      N> inline Msk<N>      andb         (const Msk<N> v1, const Msk<N> v2)                      { return v1.andb(v2);              }
template <typename T> inline Reg<T>      andb         (const Reg<T> v1, const Msk<N<T>()> v2)                 { return v1.andb(v2);              }
template <typename T> inline Reg<T>      andb         (const Msk<N<T>()> v1, const Reg<T> v2)                 { return v1.andb(v2);              }
template <typename T> inline Reg<T>      andnb        (const Reg<T> v1, const Reg<T>v2)                       { return v1.andnb(v2);             }
template <int      N> inline Msk<N>      andnb        (const Msk<N> v1, const Msk<N>v2)                       { return v1.andnb(v2);             }
template <typename T> inline Reg<T>      andnb        (const Reg<T> v1, const Msk<N<T>()> v2)                 { return v1.andnb(v2);             }
template <typename T> inline Reg<T>      andnb        (const Msk<N<T>()> v1, const Reg<T> v2)                 { return v1.andnb(v2);             }
template <typename T> inline Reg<T>      notb         (const Reg<T> v)                                        { return v.notb();                 }
template <int      N> inline Msk<N>      notb         (const Msk<N> v)                                        { return v.notb();                 }
template <typename T> inline Reg<T>      orb          (const Reg<T> v1, const Reg<T> v2)                      { return v1.orb(v2);               }
template <int      N> inline Msk<N>      orb          (const Msk<N> v1, const Msk<N> v2)                      { return v1.orb(v2);               }
template <typename T> inline Reg<T>      orb          (const Reg<T> v1, const Msk<N<T>()> v2)                 { return v1.orb(v2);               }
template <typename T> inline Reg<T>      orb          (const Msk<N<T>()> v1, const Reg<T> v2)                 { return v1.orb(v2);               }
template <typename T> inline Reg<T>      xorb         (const Reg<T> v1, const Reg<T> v2)                      { return v1.xorb(v2);              }
template <int      N> inline Msk<N>      xorb         (const Msk<N> v1, const Msk<N> v2)                      { return v1.xorb(v2);              }
template <typename T> inline Reg<T>      xorb         (const Reg<T> v1, const Msk<N<T>()> v2)                 { return v1.xorb(v2);              }
template <typename T> inline Reg<T>      xorb         (const Msk<N<T>()> v1, const Reg<T> v2)                 { return v1.xorb(v2);              }
template <typename T> inline Reg<T>      lshift       (const Reg<T> v,  const uint32_t n)                     { return v.lshift(n);              }
template <typename T> inline Reg<T>      lshiftr      (const Reg<T> v1, const Reg<T> v2)                      { return v1.lshiftr(v2);           }
template <int      N> inline Msk<N>      lshift       (const Msk<N> v,  const uint32_t n)                     { return v.lshift(n);              }
template <typename T> inline Reg<T>      rshift       (const Reg<T> v,  const uint32_t n)                     { return v.rshift(n);              }
template <typename T> inline Reg<T>      rshiftr      (const Reg<T> v1, const Reg<T> v2)                      { return v1.rshiftr(v2);           }
template <int      N> inline Msk<N>      rshift       (const Msk<N> v,  const uint32_t n)                     { return v.rshift(n);              }
template <typename T> inline Msk<N<T>()> cmpeq        (const Reg<T> v1, const Reg<T> v2)                      { return v1.cmpeq(v2);             }
template <typename T> inline Msk<N<T>()> cmpneq       (const Reg<T> v1, const Reg<T> v2)                      { return v1.cmpneq(v2);            }
template <typename T> inline Msk<N<T>()> cmplt        (const Reg<T> v1, const Reg<T> v2)                      { return v1.cmplt(v2);             }
template <typename T> inline Msk<N<T>()> cmple        (const Reg<T> v1, const Reg<T> v2)                      { return v1.cmple(v2);             }
template <typename T> inline Msk<N<T>()> cmpgt        (const Reg<T> v1, const Reg<T> v2)                      { return v1.cmpgt(v2);             }
template <typename T> inline Msk<N<T>()> cmpge        (const Reg<T> v1, const Reg<T> v2)                      { return v1.cmpge(v2);             }
template <typename T> inline Reg<T>      add          (const Reg<T> v1, const Reg<T> v2)                      { return v1.add(v2);               }
template <typename T> inline Reg<T>      sub          (const Reg<T> v1, const Reg<T> v2)                      { return v1.sub(v2);               }
template <typename T> inline Reg<T>      mul          (const Reg<T> v1, const Reg<T> v2)                      { return v1.mul(v2);               }
template <typename T> inline Reg<T>      div          (const Reg<T> v1, const Reg<T> v2)                      { return v1.div(v2);               }
template <typename T> inline Reg<T>      min          (const Reg<T> v1, const Reg<T> v2)                      { return v1.min(v2);               }
template <typename T> inline Reg<T>      max          (const Reg<T> v1, const Reg<T> v2)                      { return v1.max(v2);               }
template <typename T> inline Reg<T>      msb          (const Reg<T> v)                                        { return v.msb();                  }
template <typename T> inline Reg<T>      msb          (const Reg<T> v1, const Reg<T> v2)                      { return v1.msb(v2);               }
template <typename T> inline Msk<N<T>()> sign         (const Reg<T> v)                                        { return v.sign();                 }
template <typename T> inline Reg<T>      neg          (const Reg<T> v1, const Reg<T> v2)                      { return v1.neg(v2);               }
template <typename T> inline Reg<T>      neg          (const Reg<T> v1, const Msk<N<T>()> v2)                 { return v1.neg(v2);               }
template <typename T> inline Reg<T>      copysign     (const Reg<T> v1, const Reg<T> v2)                      { return v1.copysign(v2);          }
template <typename T> inline Reg<T>      copysign     (const Reg<T> v1, const Msk<N<T>()> v2)                 { return v1.copysign(v2);          }
template <typename T> inline Reg<T>      abs          (const Reg<T> v)                                        { return v.abs();                  }
template <typename T> inline Reg<T>      sqrt         (const Reg<T> v)                                        { return v.sqrt();                 }
template <typename T> inline Reg<T>      rsqrt        (const Reg<T> v)                                        { return v.rsqrt();                }
template <typename T> inline Reg<T>      log          (const Reg<T> v)                                        { return v.log();                  }
template <typename T> inline Reg<T>      exp          (const Reg<T> v)                                        { return v.exp();                  }
template <typename T> inline Reg<T>      sin          (const Reg<T> v)                                        { return v.sin();                  }
template <typename T> inline Reg<T>      cos          (const Reg<T> v)                                        { return v.cos();                  }
template <typename T> inline Reg<T>      tan          (const Reg<T> v)                                        { return v.tan();                  }
template <typename T> inline void        sincos       (const Reg<T> x,        Reg<T> &s,       Reg<T> &c)     { return x.sincos(s,c);            }
template <typename T> inline Regx2<T>    sincos       (const Reg<T> x)                                        { return x.sincos();               }
template <typename T> inline Regx2<T>    cossin       (const Reg<T> x)                                        { return x.cossin();               }
template <typename T> inline Reg<T>      sinh         (const Reg<T> v)                                        { return v.sinh();                 }
template <typename T> inline Reg<T>      cosh         (const Reg<T> v)                                        { return v.cosh();                 }
template <typename T> inline Reg<T>      tanh         (const Reg<T> v)                                        { return v.tanh();                 }
template <typename T> inline Reg<T>      asinh        (const Reg<T> v)                                        { return v.asinh();                }
template <typename T> inline Reg<T>      acosh        (const Reg<T> v)                                        { return v.acosh();                }
template <typename T> inline Reg<T>      atanh        (const Reg<T> v)                                        { return v.atanh();                }
template <typename T> inline Reg<T>      fmadd        (const Reg<T> v1, const Reg<T> v2, const Reg<T> v3)     { return v1.fmadd(v2, v3);         }
template <typename T> inline Reg<T>      fnmadd       (const Reg<T> v1, const Reg<T> v2, const Reg<T> v3)     { return v1.fnmadd(v2, v3);        }
template <typename T> inline Reg<T>      fmsub        (const Reg<T> v1, const Reg<T> v2, const Reg<T> v3)     { return v1.fmsub(v2, v3);         }
template <typename T> inline Reg<T>      fnmsub       (const Reg<T> v1, const Reg<T> v2, const Reg<T> v3)     { return v1.fnmsub(v2, v3);        }
template <typename T> inline Reg<T>      blend        (const Reg<T> v1, const Reg<T> v2, const Msk<N<T>()> m) { return v1.blend(v2, m );         }
template <typename T> inline Reg<T>      lrot         (const Reg<T> v)                                        { return v.lrot();                 }
template <typename T> inline Reg<T>      rrot         (const Reg<T> v)                                        { return v.rrot();                 }
template <typename T> inline Reg<T>      div2         (const Reg<T> v)                                        { return v.div2();                 }
template <typename T> inline Reg<T>      div4         (const Reg<T> v)                                        { return v.div4();                 }
template <typename T> inline Reg<T>      sat          (const Reg<T> v, T min, T max)                          { return v.sat(min, max);          }
template <typename T> inline Reg<T>      round        (const Reg<T> v)                                        { return v.round();                }
template <typename T> inline Reg<T>      trunc        (const Reg<T> v)                                        { return v.trunc();                }
template <typename T> inline bool        testz        (const Reg<T> v1, const Reg<T> v2)                      { return v1.testz(v2);             }
template <int      N> inline bool        testz        (const Msk<N> v1, const Msk<N> v2)                      { return v1.testz(v2);             }
template <typename T> inline bool        testz        (const Reg<T> v1)                                       { return v1.testz();               }
template <int      N> inline bool        testz        (const Msk<N> v1)                                       { return v1.testz();               }
template <typename T> inline     T       sum          (const Reg<T> v)                                        { return v.sum();                  }
template <typename T> inline     T       hadd         (const Reg<T> v)                                        { return v.hadd();                 }
template <typename T> inline     T       hmul         (const Reg<T> v)                                        { return v.hmul();                 }
template <typename T> inline     T       hmin         (const Reg<T> v)                                        { return v.hmin();                 }
template <typename T> inline     T       hmax         (const Reg<T> v)                                        { return v.hmax();                 }
template <typename T> inline Reg<T>      combine      (const Reg_2<T> v1, const Reg_2<T> v2)                  { return v1.combine(v2);           }
template <typename T> inline Regx2<T>    cadd         (const Regx2<T> v1, const Regx2<T> v2)                  { return v1.cadd(v2);              }
template <typename T> inline Regx2<T>    csub         (const Regx2<T> v1, const Regx2<T> v2)                  { return v1.csub(v2);              }
template <typename T> inline Regx2<T>    cmul         (const Regx2<T> v1, const Regx2<T> v2)                  { return v1.cmul(v2);              }
template <typename T> inline Regx2<T>    cmulconj     (const Regx2<T> v1, const Regx2<T> v2)                  { return v1.cmulconj(v2);          }
template <typename T> inline Regx2<T>    cdiv         (const Regx2<T> v1, const Regx2<T> v2)                  { return v1.cdiv(v2);              }
template <typename T> inline Regx2<T>    conj         (const Regx2<T> v)                                      { return v.conj();                 }
template <typename T> inline Reg<T>      norm         (const Regx2<T> v)                                      { return v.norm();                 }

template <typename T>
inline Reg<T> toReg(const Msk<N<T>()> m) {
	return m.template toReg<T>();
}

template <typename T1, typename T2>
inline Reg<T2> cvt(const Reg<T1> v) {
	return v.template cvt<T2>();
}

template <typename T1, typename T2>
inline Reg<T2> cvt(const Reg_2<T1> v) {
	return v.template cvt<T2>();
}

template <typename T1, typename T2>
inline Reg<T2> pack(const Reg<T1> v1, const Reg<T1> v2) {
	return v1.template pack<T2>(v2);
}

template <typename T1, typename T2>
inline Reg<T2> cast(const Reg<T1> v) {
	return v.template cast<T2>();
}

template <typename TD, typename TI>
inline Reg<TD> gather(const TD* mem, const Reg<TI> idx) {
	Reg<TD> r;
	r.gather(mem, idx);
	return r;
}

template <typename TD, typename TI>
inline void scatter(TD* mem, const Reg<TI> idx, const Reg<TD> r) {
	r.scatter(mem, idx);
}
