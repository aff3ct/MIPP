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

inline rvd_type<float64_t>& operator+= (const rvd_type<float64_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<float64_t> operator+= (const rvd_type<float64_t>& v) const { return this->add(v);}

inline rvd_type<float64_t>& operator+ (const rvd_type<float64_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<float64_t> operator+ (const rvd_type<float64_t>& v) const { return this->add(v);}

inline rvd_type<float64_t>& operator-= (const rvd_type<float64_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<float64_t> operator-= (const rvd_type<float64_t>& v) const { return this->sub(v);}

inline rvd_type<float64_t>& operator- (const rvd_type<float64_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<float64_t> operator- (const rvd_type<float64_t>& v) const { return this->sub(v);}

inline rvd_type<float64_t>& operator*= (const rvd_type<float64_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<float64_t> operator*= (const rvd_type<float64_t>& v) const { return this->mul(v);}

inline rvd_type<float64_t>& operator* (const rvd_type<float64_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<float64_t> operator* (const rvd_type<float64_t>& v) const { return this->mul(v);}

inline rvd_type<float64_t>& operator/= (const rvd_type<float64_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<float64_t> operator/= (const rvd_type<float64_t>& v) const { return this->div(v);}

inline rvd_type<float64_t>& operator/ (const rvd_type<float64_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<float64_t> operator/ (const rvd_type<float64_t>& v) const { return this->div(v);}

inline rvd_type<float64_t>& operator~ (const rvd_type<float64_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<float64_t> operator~ (const rvd_type<float64_t>& v) const { return this->notb(v);}

inline rvd_type<float64_t>& operator^= (const rvd_type<float64_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<float64_t> operator^= (const rvd_type<float64_t>& v) const { return this->xorb(v);}

inline rvd_type<float64_t>& operator^ (const rvd_type<float64_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<float64_t> operator^ (const rvd_type<float64_t>& v) const { return this->xorb(v);}

inline rvd_type<float64_t>& operator|= (const rvd_type<float64_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<float64_t> operator|= (const rvd_type<float64_t>& v) const { return this->orb(v);}

inline rvd_type<float64_t>& operator| (const rvd_type<float64_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<float64_t> operator| (const rvd_type<float64_t>& v) const { return this->orb(v);}

inline rvd_type<float64_t>& operator&= (const rvd_type<float64_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<float64_t> operator&= (const rvd_type<float64_t>& v) const { return this->andb(v);}

inline rvd_type<float64_t>& operator& (const rvd_type<float64_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<float64_t> operator& (const rvd_type<float64_t>& v) const { return this->andb(v);}

inline rvd_type<float64_t>& operator== (const rvd_type<float64_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<float64_t> operator== (const rvd_type<float64_t>& v) const { return this->cmpeq(v);}

inline rvd_type<float64_t>& operator!= (const rvd_type<float64_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<float64_t> operator!= (const rvd_type<float64_t>& v) const { return this->cmpneq(v);}

inline rvd_type<float64_t>& operator< (const rvd_type<float64_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<float64_t> operator< (const rvd_type<float64_t>& v) const { return this->cmplt(v);}

inline rvd_type<float64_t>& operator<= (const rvd_type<float64_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<float64_t> operator<= (const rvd_type<float64_t>& v) const { return this->cmple(v);}

inline rvd_type<float64_t>& operator> (const rvd_type<float64_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<float64_t> operator> (const rvd_type<float64_t>& v) const { return this->cmpgt(v);}

inline rvd_type<float64_t>& operator>= (const rvd_type<float64_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<float64_t> operator>= (const rvd_type<float64_t>& v) const { return this->cmpge(v);}

inline rvd_type<float32_t>& operator+= (const rvd_type<float32_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<float32_t> operator+= (const rvd_type<float32_t>& v) const { return this->add(v);}

inline rvd_type<float32_t>& operator+ (const rvd_type<float32_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<float32_t> operator+ (const rvd_type<float32_t>& v) const { return this->add(v);}

inline rvd_type<float32_t>& operator-= (const rvd_type<float32_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<float32_t> operator-= (const rvd_type<float32_t>& v) const { return this->sub(v);}

inline rvd_type<float32_t>& operator- (const rvd_type<float32_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<float32_t> operator- (const rvd_type<float32_t>& v) const { return this->sub(v);}

inline rvd_type<float32_t>& operator*= (const rvd_type<float32_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<float32_t> operator*= (const rvd_type<float32_t>& v) const { return this->mul(v);}

inline rvd_type<float32_t>& operator* (const rvd_type<float32_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<float32_t> operator* (const rvd_type<float32_t>& v) const { return this->mul(v);}

inline rvd_type<float32_t>& operator/= (const rvd_type<float32_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<float32_t> operator/= (const rvd_type<float32_t>& v) const { return this->div(v);}

inline rvd_type<float32_t>& operator/ (const rvd_type<float32_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<float32_t> operator/ (const rvd_type<float32_t>& v) const { return this->div(v);}

inline rvd_type<float32_t>& operator~ (const rvd_type<float32_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<float32_t> operator~ (const rvd_type<float32_t>& v) const { return this->notb(v);}

inline rvd_type<float32_t>& operator^= (const rvd_type<float32_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<float32_t> operator^= (const rvd_type<float32_t>& v) const { return this->xorb(v);}

inline rvd_type<float32_t>& operator^ (const rvd_type<float32_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<float32_t> operator^ (const rvd_type<float32_t>& v) const { return this->xorb(v);}

inline rvd_type<float32_t>& operator|= (const rvd_type<float32_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<float32_t> operator|= (const rvd_type<float32_t>& v) const { return this->orb(v);}

inline rvd_type<float32_t>& operator| (const rvd_type<float32_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<float32_t> operator| (const rvd_type<float32_t>& v) const { return this->orb(v);}

inline rvd_type<float32_t>& operator&= (const rvd_type<float32_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<float32_t> operator&= (const rvd_type<float32_t>& v) const { return this->andb(v);}

inline rvd_type<float32_t>& operator& (const rvd_type<float32_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<float32_t> operator& (const rvd_type<float32_t>& v) const { return this->andb(v);}

inline rvd_type<float32_t>& operator== (const rvd_type<float32_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<float32_t> operator== (const rvd_type<float32_t>& v) const { return this->cmpeq(v);}

inline rvd_type<float32_t>& operator!= (const rvd_type<float32_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<float32_t> operator!= (const rvd_type<float32_t>& v) const { return this->cmpneq(v);}

inline rvd_type<float32_t>& operator< (const rvd_type<float32_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<float32_t> operator< (const rvd_type<float32_t>& v) const { return this->cmplt(v);}

inline rvd_type<float32_t>& operator<= (const rvd_type<float32_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<float32_t> operator<= (const rvd_type<float32_t>& v) const { return this->cmple(v);}

inline rvd_type<float32_t>& operator> (const rvd_type<float32_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<float32_t> operator> (const rvd_type<float32_t>& v) const { return this->cmpgt(v);}

inline rvd_type<float32_t>& operator>= (const rvd_type<float32_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<float32_t> operator>= (const rvd_type<float32_t>& v) const { return this->cmpge(v);}

inline rvd_type<int64_t>& operator+= (const rvd_type<int64_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int64_t> operator+= (const rvd_type<int64_t>& v) const { return this->add(v);}

inline rvd_type<int64_t>& operator+ (const rvd_type<int64_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int64_t> operator+ (const rvd_type<int64_t>& v) const { return this->add(v);}

inline rvd_type<int64_t>& operator-= (const rvd_type<int64_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int64_t> operator-= (const rvd_type<int64_t>& v) const { return this->sub(v);}

inline rvd_type<int64_t>& operator- (const rvd_type<int64_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int64_t> operator- (const rvd_type<int64_t>& v) const { return this->sub(v);}

inline rvd_type<int64_t>& operator*= (const rvd_type<int64_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int64_t> operator*= (const rvd_type<int64_t>& v) const { return this->mul(v);}

inline rvd_type<int64_t>& operator* (const rvd_type<int64_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int64_t> operator* (const rvd_type<int64_t>& v) const { return this->mul(v);}

inline rvd_type<int64_t>& operator/= (const rvd_type<int64_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int64_t> operator/= (const rvd_type<int64_t>& v) const { return this->div(v);}

inline rvd_type<int64_t>& operator/ (const rvd_type<int64_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int64_t> operator/ (const rvd_type<int64_t>& v) const { return this->div(v);}

inline rvd_type<int64_t>& operator~ (const rvd_type<int64_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<int64_t> operator~ (const rvd_type<int64_t>& v) const { return this->notb(v);}

inline rvd_type<int64_t>& operator^= (const rvd_type<int64_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int64_t> operator^= (const rvd_type<int64_t>& v) const { return this->xorb(v);}

inline rvd_type<int64_t>& operator^ (const rvd_type<int64_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int64_t> operator^ (const rvd_type<int64_t>& v) const { return this->xorb(v);}

inline rvd_type<int64_t>& operator|= (const rvd_type<int64_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int64_t> operator|= (const rvd_type<int64_t>& v) const { return this->orb(v);}

inline rvd_type<int64_t>& operator| (const rvd_type<int64_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int64_t> operator| (const rvd_type<int64_t>& v) const { return this->orb(v);}

inline rvd_type<int64_t>& operator&= (const rvd_type<int64_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int64_t> operator&= (const rvd_type<int64_t>& v) const { return this->andb(v);}

inline rvd_type<int64_t>& operator& (const rvd_type<int64_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int64_t> operator& (const rvd_type<int64_t>& v) const { return this->andb(v);}

inline rvd_type<int64_t>& operator== (const rvd_type<int64_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<int64_t> operator== (const rvd_type<int64_t>& v) const { return this->cmpeq(v);}

inline rvd_type<int64_t>& operator!= (const rvd_type<int64_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<int64_t> operator!= (const rvd_type<int64_t>& v) const { return this->cmpneq(v);}

inline rvd_type<int64_t>& operator< (const rvd_type<int64_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<int64_t> operator< (const rvd_type<int64_t>& v) const { return this->cmplt(v);}

inline rvd_type<int64_t>& operator<= (const rvd_type<int64_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<int64_t> operator<= (const rvd_type<int64_t>& v) const { return this->cmple(v);}

inline rvd_type<int64_t>& operator> (const rvd_type<int64_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<int64_t> operator> (const rvd_type<int64_t>& v) const { return this->cmpgt(v);}

inline rvd_type<int64_t>& operator>= (const rvd_type<int64_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<int64_t> operator>= (const rvd_type<int64_t>& v) const { return this->cmpge(v);}

inline rvd_type<int32_t>& operator+= (const rvd_type<int32_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int32_t> operator+= (const rvd_type<int32_t>& v) const { return this->add(v);}

inline rvd_type<int32_t>& operator+ (const rvd_type<int32_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int32_t> operator+ (const rvd_type<int32_t>& v) const { return this->add(v);}

inline rvd_type<int32_t>& operator-= (const rvd_type<int32_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int32_t> operator-= (const rvd_type<int32_t>& v) const { return this->sub(v);}

inline rvd_type<int32_t>& operator- (const rvd_type<int32_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int32_t> operator- (const rvd_type<int32_t>& v) const { return this->sub(v);}

inline rvd_type<int32_t>& operator*= (const rvd_type<int32_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int32_t> operator*= (const rvd_type<int32_t>& v) const { return this->mul(v);}

inline rvd_type<int32_t>& operator* (const rvd_type<int32_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int32_t> operator* (const rvd_type<int32_t>& v) const { return this->mul(v);}

inline rvd_type<int32_t>& operator/= (const rvd_type<int32_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int32_t> operator/= (const rvd_type<int32_t>& v) const { return this->div(v);}

inline rvd_type<int32_t>& operator/ (const rvd_type<int32_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int32_t> operator/ (const rvd_type<int32_t>& v) const { return this->div(v);}

inline rvd_type<int32_t>& operator~ (const rvd_type<int32_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<int32_t> operator~ (const rvd_type<int32_t>& v) const { return this->notb(v);}

inline rvd_type<int32_t>& operator^= (const rvd_type<int32_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int32_t> operator^= (const rvd_type<int32_t>& v) const { return this->xorb(v);}

inline rvd_type<int32_t>& operator^ (const rvd_type<int32_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int32_t> operator^ (const rvd_type<int32_t>& v) const { return this->xorb(v);}

inline rvd_type<int32_t>& operator|= (const rvd_type<int32_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int32_t> operator|= (const rvd_type<int32_t>& v) const { return this->orb(v);}

inline rvd_type<int32_t>& operator| (const rvd_type<int32_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int32_t> operator| (const rvd_type<int32_t>& v) const { return this->orb(v);}

inline rvd_type<int32_t>& operator&= (const rvd_type<int32_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int32_t> operator&= (const rvd_type<int32_t>& v) const { return this->andb(v);}

inline rvd_type<int32_t>& operator& (const rvd_type<int32_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int32_t> operator& (const rvd_type<int32_t>& v) const { return this->andb(v);}

inline rvd_type<int32_t>& operator== (const rvd_type<int32_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<int32_t> operator== (const rvd_type<int32_t>& v) const { return this->cmpeq(v);}

inline rvd_type<int32_t>& operator!= (const rvd_type<int32_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<int32_t> operator!= (const rvd_type<int32_t>& v) const { return this->cmpneq(v);}

inline rvd_type<int32_t>& operator< (const rvd_type<int32_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<int32_t> operator< (const rvd_type<int32_t>& v) const { return this->cmplt(v);}

inline rvd_type<int32_t>& operator<= (const rvd_type<int32_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<int32_t> operator<= (const rvd_type<int32_t>& v) const { return this->cmple(v);}

inline rvd_type<int32_t>& operator> (const rvd_type<int32_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<int32_t> operator> (const rvd_type<int32_t>& v) const { return this->cmpgt(v);}

inline rvd_type<int32_t>& operator>= (const rvd_type<int32_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<int32_t> operator>= (const rvd_type<int32_t>& v) const { return this->cmpge(v);}

inline rvd_type<int16_t>& operator+= (const rvd_type<int16_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int16_t> operator+= (const rvd_type<int16_t>& v) const { return this->add(v);}

inline rvd_type<int16_t>& operator+ (const rvd_type<int16_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int16_t> operator+ (const rvd_type<int16_t>& v) const { return this->add(v);}

inline rvd_type<int16_t>& operator-= (const rvd_type<int16_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int16_t> operator-= (const rvd_type<int16_t>& v) const { return this->sub(v);}

inline rvd_type<int16_t>& operator- (const rvd_type<int16_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int16_t> operator- (const rvd_type<int16_t>& v) const { return this->sub(v);}

inline rvd_type<int16_t>& operator*= (const rvd_type<int16_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int16_t> operator*= (const rvd_type<int16_t>& v) const { return this->mul(v);}

inline rvd_type<int16_t>& operator* (const rvd_type<int16_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int16_t> operator* (const rvd_type<int16_t>& v) const { return this->mul(v);}

inline rvd_type<int16_t>& operator/= (const rvd_type<int16_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int16_t> operator/= (const rvd_type<int16_t>& v) const { return this->div(v);}

inline rvd_type<int16_t>& operator/ (const rvd_type<int16_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int16_t> operator/ (const rvd_type<int16_t>& v) const { return this->div(v);}

inline rvd_type<int16_t>& operator~ (const rvd_type<int16_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<int16_t> operator~ (const rvd_type<int16_t>& v) const { return this->notb(v);}

inline rvd_type<int16_t>& operator^= (const rvd_type<int16_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int16_t> operator^= (const rvd_type<int16_t>& v) const { return this->xorb(v);}

inline rvd_type<int16_t>& operator^ (const rvd_type<int16_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int16_t> operator^ (const rvd_type<int16_t>& v) const { return this->xorb(v);}

inline rvd_type<int16_t>& operator|= (const rvd_type<int16_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int16_t> operator|= (const rvd_type<int16_t>& v) const { return this->orb(v);}

inline rvd_type<int16_t>& operator| (const rvd_type<int16_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int16_t> operator| (const rvd_type<int16_t>& v) const { return this->orb(v);}

inline rvd_type<int16_t>& operator&= (const rvd_type<int16_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int16_t> operator&= (const rvd_type<int16_t>& v) const { return this->andb(v);}

inline rvd_type<int16_t>& operator& (const rvd_type<int16_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int16_t> operator& (const rvd_type<int16_t>& v) const { return this->andb(v);}

inline rvd_type<int16_t>& operator== (const rvd_type<int16_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<int16_t> operator== (const rvd_type<int16_t>& v) const { return this->cmpeq(v);}

inline rvd_type<int16_t>& operator!= (const rvd_type<int16_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<int16_t> operator!= (const rvd_type<int16_t>& v) const { return this->cmpneq(v);}

inline rvd_type<int16_t>& operator< (const rvd_type<int16_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<int16_t> operator< (const rvd_type<int16_t>& v) const { return this->cmplt(v);}

inline rvd_type<int16_t>& operator<= (const rvd_type<int16_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<int16_t> operator<= (const rvd_type<int16_t>& v) const { return this->cmple(v);}

inline rvd_type<int16_t>& operator> (const rvd_type<int16_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<int16_t> operator> (const rvd_type<int16_t>& v) const { return this->cmpgt(v);}

inline rvd_type<int16_t>& operator>= (const rvd_type<int16_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<int16_t> operator>= (const rvd_type<int16_t>& v) const { return this->cmpge(v);}

inline rvd_type<int8_t>& operator+= (const rvd_type<int8_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int8_t> operator+= (const rvd_type<int8_t>& v) const { return this->add(v);}

inline rvd_type<int8_t>& operator+ (const rvd_type<int8_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<int8_t> operator+ (const rvd_type<int8_t>& v) const { return this->add(v);}

inline rvd_type<int8_t>& operator-= (const rvd_type<int8_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int8_t> operator-= (const rvd_type<int8_t>& v) const { return this->sub(v);}

inline rvd_type<int8_t>& operator- (const rvd_type<int8_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<int8_t> operator- (const rvd_type<int8_t>& v) const { return this->sub(v);}

inline rvd_type<int8_t>& operator*= (const rvd_type<int8_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int8_t> operator*= (const rvd_type<int8_t>& v) const { return this->mul(v);}

inline rvd_type<int8_t>& operator* (const rvd_type<int8_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<int8_t> operator* (const rvd_type<int8_t>& v) const { return this->mul(v);}

inline rvd_type<int8_t>& operator/= (const rvd_type<int8_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int8_t> operator/= (const rvd_type<int8_t>& v) const { return this->div(v);}

inline rvd_type<int8_t>& operator/ (const rvd_type<int8_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<int8_t> operator/ (const rvd_type<int8_t>& v) const { return this->div(v);}

inline rvd_type<int8_t>& operator~ (const rvd_type<int8_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<int8_t> operator~ (const rvd_type<int8_t>& v) const { return this->notb(v);}

inline rvd_type<int8_t>& operator^= (const rvd_type<int8_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int8_t> operator^= (const rvd_type<int8_t>& v) const { return this->xorb(v);}

inline rvd_type<int8_t>& operator^ (const rvd_type<int8_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<int8_t> operator^ (const rvd_type<int8_t>& v) const { return this->xorb(v);}

inline rvd_type<int8_t>& operator|= (const rvd_type<int8_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int8_t> operator|= (const rvd_type<int8_t>& v) const { return this->orb(v);}

inline rvd_type<int8_t>& operator| (const rvd_type<int8_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<int8_t> operator| (const rvd_type<int8_t>& v) const { return this->orb(v);}

inline rvd_type<int8_t>& operator&= (const rvd_type<int8_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int8_t> operator&= (const rvd_type<int8_t>& v) const { return this->andb(v);}

inline rvd_type<int8_t>& operator& (const rvd_type<int8_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<int8_t> operator& (const rvd_type<int8_t>& v) const { return this->andb(v);}

inline rvd_type<int8_t>& operator== (const rvd_type<int8_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<int8_t> operator== (const rvd_type<int8_t>& v) const { return this->cmpeq(v);}

inline rvd_type<int8_t>& operator!= (const rvd_type<int8_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<int8_t> operator!= (const rvd_type<int8_t>& v) const { return this->cmpneq(v);}

inline rvd_type<int8_t>& operator< (const rvd_type<int8_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<int8_t> operator< (const rvd_type<int8_t>& v) const { return this->cmplt(v);}

inline rvd_type<int8_t>& operator<= (const rvd_type<int8_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<int8_t> operator<= (const rvd_type<int8_t>& v) const { return this->cmple(v);}

inline rvd_type<int8_t>& operator> (const rvd_type<int8_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<int8_t> operator> (const rvd_type<int8_t>& v) const { return this->cmpgt(v);}

inline rvd_type<int8_t>& operator>= (const rvd_type<int8_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<int8_t> operator>= (const rvd_type<int8_t>& v) const { return this->cmpge(v);}

inline rvd_type<uint64_t>& operator+= (const rvd_type<uint64_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint64_t> operator+= (const rvd_type<uint64_t>& v) const { return this->add(v);}

inline rvd_type<uint64_t>& operator+ (const rvd_type<uint64_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint64_t> operator+ (const rvd_type<uint64_t>& v) const { return this->add(v);}

inline rvd_type<uint64_t>& operator-= (const rvd_type<uint64_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint64_t> operator-= (const rvd_type<uint64_t>& v) const { return this->sub(v);}

inline rvd_type<uint64_t>& operator- (const rvd_type<uint64_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint64_t> operator- (const rvd_type<uint64_t>& v) const { return this->sub(v);}

inline rvd_type<uint64_t>& operator*= (const rvd_type<uint64_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint64_t> operator*= (const rvd_type<uint64_t>& v) const { return this->mul(v);}

inline rvd_type<uint64_t>& operator* (const rvd_type<uint64_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint64_t> operator* (const rvd_type<uint64_t>& v) const { return this->mul(v);}

inline rvd_type<uint64_t>& operator/= (const rvd_type<uint64_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint64_t> operator/= (const rvd_type<uint64_t>& v) const { return this->div(v);}

inline rvd_type<uint64_t>& operator/ (const rvd_type<uint64_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint64_t> operator/ (const rvd_type<uint64_t>& v) const { return this->div(v);}

inline rvd_type<uint64_t>& operator~ (const rvd_type<uint64_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<uint64_t> operator~ (const rvd_type<uint64_t>& v) const { return this->notb(v);}

inline rvd_type<uint64_t>& operator^= (const rvd_type<uint64_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint64_t> operator^= (const rvd_type<uint64_t>& v) const { return this->xorb(v);}

inline rvd_type<uint64_t>& operator^ (const rvd_type<uint64_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint64_t> operator^ (const rvd_type<uint64_t>& v) const { return this->xorb(v);}

inline rvd_type<uint64_t>& operator|= (const rvd_type<uint64_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint64_t> operator|= (const rvd_type<uint64_t>& v) const { return this->orb(v);}

inline rvd_type<uint64_t>& operator| (const rvd_type<uint64_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint64_t> operator| (const rvd_type<uint64_t>& v) const { return this->orb(v);}

inline rvd_type<uint64_t>& operator&= (const rvd_type<uint64_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint64_t> operator&= (const rvd_type<uint64_t>& v) const { return this->andb(v);}

inline rvd_type<uint64_t>& operator& (const rvd_type<uint64_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint64_t> operator& (const rvd_type<uint64_t>& v) const { return this->andb(v);}

inline rvd_type<uint64_t>& operator== (const rvd_type<uint64_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<uint64_t> operator== (const rvd_type<uint64_t>& v) const { return this->cmpeq(v);}

inline rvd_type<uint64_t>& operator!= (const rvd_type<uint64_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<uint64_t> operator!= (const rvd_type<uint64_t>& v) const { return this->cmpneq(v);}

inline rvd_type<uint64_t>& operator< (const rvd_type<uint64_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<uint64_t> operator< (const rvd_type<uint64_t>& v) const { return this->cmplt(v);}

inline rvd_type<uint64_t>& operator<= (const rvd_type<uint64_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<uint64_t> operator<= (const rvd_type<uint64_t>& v) const { return this->cmple(v);}

inline rvd_type<uint64_t>& operator> (const rvd_type<uint64_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<uint64_t> operator> (const rvd_type<uint64_t>& v) const { return this->cmpgt(v);}

inline rvd_type<uint64_t>& operator>= (const rvd_type<uint64_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<uint64_t> operator>= (const rvd_type<uint64_t>& v) const { return this->cmpge(v);}

inline rvd_type<uint32_t>& operator+= (const rvd_type<uint32_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint32_t> operator+= (const rvd_type<uint32_t>& v) const { return this->add(v);}

inline rvd_type<uint32_t>& operator+ (const rvd_type<uint32_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint32_t> operator+ (const rvd_type<uint32_t>& v) const { return this->add(v);}

inline rvd_type<uint32_t>& operator-= (const rvd_type<uint32_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint32_t> operator-= (const rvd_type<uint32_t>& v) const { return this->sub(v);}

inline rvd_type<uint32_t>& operator- (const rvd_type<uint32_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint32_t> operator- (const rvd_type<uint32_t>& v) const { return this->sub(v);}

inline rvd_type<uint32_t>& operator*= (const rvd_type<uint32_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint32_t> operator*= (const rvd_type<uint32_t>& v) const { return this->mul(v);}

inline rvd_type<uint32_t>& operator* (const rvd_type<uint32_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint32_t> operator* (const rvd_type<uint32_t>& v) const { return this->mul(v);}

inline rvd_type<uint32_t>& operator/= (const rvd_type<uint32_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint32_t> operator/= (const rvd_type<uint32_t>& v) const { return this->div(v);}

inline rvd_type<uint32_t>& operator/ (const rvd_type<uint32_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint32_t> operator/ (const rvd_type<uint32_t>& v) const { return this->div(v);}

inline rvd_type<uint32_t>& operator~ (const rvd_type<uint32_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<uint32_t> operator~ (const rvd_type<uint32_t>& v) const { return this->notb(v);}

inline rvd_type<uint32_t>& operator^= (const rvd_type<uint32_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint32_t> operator^= (const rvd_type<uint32_t>& v) const { return this->xorb(v);}

inline rvd_type<uint32_t>& operator^ (const rvd_type<uint32_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint32_t> operator^ (const rvd_type<uint32_t>& v) const { return this->xorb(v);}

inline rvd_type<uint32_t>& operator|= (const rvd_type<uint32_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint32_t> operator|= (const rvd_type<uint32_t>& v) const { return this->orb(v);}

inline rvd_type<uint32_t>& operator| (const rvd_type<uint32_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint32_t> operator| (const rvd_type<uint32_t>& v) const { return this->orb(v);}

inline rvd_type<uint32_t>& operator&= (const rvd_type<uint32_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint32_t> operator&= (const rvd_type<uint32_t>& v) const { return this->andb(v);}

inline rvd_type<uint32_t>& operator& (const rvd_type<uint32_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint32_t> operator& (const rvd_type<uint32_t>& v) const { return this->andb(v);}

inline rvd_type<uint32_t>& operator== (const rvd_type<uint32_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<uint32_t> operator== (const rvd_type<uint32_t>& v) const { return this->cmpeq(v);}

inline rvd_type<uint32_t>& operator!= (const rvd_type<uint32_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<uint32_t> operator!= (const rvd_type<uint32_t>& v) const { return this->cmpneq(v);}

inline rvd_type<uint32_t>& operator< (const rvd_type<uint32_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<uint32_t> operator< (const rvd_type<uint32_t>& v) const { return this->cmplt(v);}

inline rvd_type<uint32_t>& operator<= (const rvd_type<uint32_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<uint32_t> operator<= (const rvd_type<uint32_t>& v) const { return this->cmple(v);}

inline rvd_type<uint32_t>& operator> (const rvd_type<uint32_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<uint32_t> operator> (const rvd_type<uint32_t>& v) const { return this->cmpgt(v);}

inline rvd_type<uint32_t>& operator>= (const rvd_type<uint32_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<uint32_t> operator>= (const rvd_type<uint32_t>& v) const { return this->cmpge(v);}

inline rvd_type<uint16_t>& operator+= (const rvd_type<uint16_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint16_t> operator+= (const rvd_type<uint16_t>& v) const { return this->add(v);}

inline rvd_type<uint16_t>& operator+ (const rvd_type<uint16_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint16_t> operator+ (const rvd_type<uint16_t>& v) const { return this->add(v);}

inline rvd_type<uint16_t>& operator-= (const rvd_type<uint16_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint16_t> operator-= (const rvd_type<uint16_t>& v) const { return this->sub(v);}

inline rvd_type<uint16_t>& operator- (const rvd_type<uint16_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint16_t> operator- (const rvd_type<uint16_t>& v) const { return this->sub(v);}

inline rvd_type<uint16_t>& operator*= (const rvd_type<uint16_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint16_t> operator*= (const rvd_type<uint16_t>& v) const { return this->mul(v);}

inline rvd_type<uint16_t>& operator* (const rvd_type<uint16_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint16_t> operator* (const rvd_type<uint16_t>& v) const { return this->mul(v);}

inline rvd_type<uint16_t>& operator/= (const rvd_type<uint16_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint16_t> operator/= (const rvd_type<uint16_t>& v) const { return this->div(v);}

inline rvd_type<uint16_t>& operator/ (const rvd_type<uint16_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint16_t> operator/ (const rvd_type<uint16_t>& v) const { return this->div(v);}

inline rvd_type<uint16_t>& operator~ (const rvd_type<uint16_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<uint16_t> operator~ (const rvd_type<uint16_t>& v) const { return this->notb(v);}

inline rvd_type<uint16_t>& operator^= (const rvd_type<uint16_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint16_t> operator^= (const rvd_type<uint16_t>& v) const { return this->xorb(v);}

inline rvd_type<uint16_t>& operator^ (const rvd_type<uint16_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint16_t> operator^ (const rvd_type<uint16_t>& v) const { return this->xorb(v);}

inline rvd_type<uint16_t>& operator|= (const rvd_type<uint16_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint16_t> operator|= (const rvd_type<uint16_t>& v) const { return this->orb(v);}

inline rvd_type<uint16_t>& operator| (const rvd_type<uint16_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint16_t> operator| (const rvd_type<uint16_t>& v) const { return this->orb(v);}

inline rvd_type<uint16_t>& operator&= (const rvd_type<uint16_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint16_t> operator&= (const rvd_type<uint16_t>& v) const { return this->andb(v);}

inline rvd_type<uint16_t>& operator& (const rvd_type<uint16_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint16_t> operator& (const rvd_type<uint16_t>& v) const { return this->andb(v);}

inline rvd_type<uint16_t>& operator== (const rvd_type<uint16_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<uint16_t> operator== (const rvd_type<uint16_t>& v) const { return this->cmpeq(v);}

inline rvd_type<uint16_t>& operator!= (const rvd_type<uint16_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<uint16_t> operator!= (const rvd_type<uint16_t>& v) const { return this->cmpneq(v);}

inline rvd_type<uint16_t>& operator< (const rvd_type<uint16_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<uint16_t> operator< (const rvd_type<uint16_t>& v) const { return this->cmplt(v);}

inline rvd_type<uint16_t>& operator<= (const rvd_type<uint16_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<uint16_t> operator<= (const rvd_type<uint16_t>& v) const { return this->cmple(v);}

inline rvd_type<uint16_t>& operator> (const rvd_type<uint16_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<uint16_t> operator> (const rvd_type<uint16_t>& v) const { return this->cmpgt(v);}

inline rvd_type<uint16_t>& operator>= (const rvd_type<uint16_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<uint16_t> operator>= (const rvd_type<uint16_t>& v) const { return this->cmpge(v);}

inline rvd_type<uint8_t>& operator+= (const rvd_type<uint8_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint8_t> operator+= (const rvd_type<uint8_t>& v) const { return this->add(v);}

inline rvd_type<uint8_t>& operator+ (const rvd_type<uint8_t>& v) { r = this->add(v).r; return *this;}
inline rvd_type<uint8_t> operator+ (const rvd_type<uint8_t>& v) const { return this->add(v);}

inline rvd_type<uint8_t>& operator-= (const rvd_type<uint8_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint8_t> operator-= (const rvd_type<uint8_t>& v) const { return this->sub(v);}

inline rvd_type<uint8_t>& operator- (const rvd_type<uint8_t>& v) { r = this->sub(v).r; return *this;}
inline rvd_type<uint8_t> operator- (const rvd_type<uint8_t>& v) const { return this->sub(v);}

inline rvd_type<uint8_t>& operator*= (const rvd_type<uint8_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint8_t> operator*= (const rvd_type<uint8_t>& v) const { return this->mul(v);}

inline rvd_type<uint8_t>& operator* (const rvd_type<uint8_t>& v) { r = this->mul(v).r; return *this;}
inline rvd_type<uint8_t> operator* (const rvd_type<uint8_t>& v) const { return this->mul(v);}

inline rvd_type<uint8_t>& operator/= (const rvd_type<uint8_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint8_t> operator/= (const rvd_type<uint8_t>& v) const { return this->div(v);}

inline rvd_type<uint8_t>& operator/ (const rvd_type<uint8_t>& v) { r = this->div(v).r; return *this;}
inline rvd_type<uint8_t> operator/ (const rvd_type<uint8_t>& v) const { return this->div(v);}

inline rvd_type<uint8_t>& operator~ (const rvd_type<uint8_t>& v) { r = this->notb(v).r; return *this;}
inline rvd_type<uint8_t> operator~ (const rvd_type<uint8_t>& v) const { return this->notb(v);}

inline rvd_type<uint8_t>& operator^= (const rvd_type<uint8_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint8_t> operator^= (const rvd_type<uint8_t>& v) const { return this->xorb(v);}

inline rvd_type<uint8_t>& operator^ (const rvd_type<uint8_t>& v) { r = this->xorb(v).r; return *this;}
inline rvd_type<uint8_t> operator^ (const rvd_type<uint8_t>& v) const { return this->xorb(v);}

inline rvd_type<uint8_t>& operator|= (const rvd_type<uint8_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint8_t> operator|= (const rvd_type<uint8_t>& v) const { return this->orb(v);}

inline rvd_type<uint8_t>& operator| (const rvd_type<uint8_t>& v) { r = this->orb(v).r; return *this;}
inline rvd_type<uint8_t> operator| (const rvd_type<uint8_t>& v) const { return this->orb(v);}

inline rvd_type<uint8_t>& operator&= (const rvd_type<uint8_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint8_t> operator&= (const rvd_type<uint8_t>& v) const { return this->andb(v);}

inline rvd_type<uint8_t>& operator& (const rvd_type<uint8_t>& v) { r = this->andb(v).r; return *this;}
inline rvd_type<uint8_t> operator& (const rvd_type<uint8_t>& v) const { return this->andb(v);}

inline rvd_type<uint8_t>& operator== (const rvd_type<uint8_t>& v) { r = this->cmpeq(v).r; return *this;}
inline rvd_type<uint8_t> operator== (const rvd_type<uint8_t>& v) const { return this->cmpeq(v);}

inline rvd_type<uint8_t>& operator!= (const rvd_type<uint8_t>& v) { r = this->cmpneq(v).r; return *this;}
inline rvd_type<uint8_t> operator!= (const rvd_type<uint8_t>& v) const { return this->cmpneq(v);}

inline rvd_type<uint8_t>& operator< (const rvd_type<uint8_t>& v) { r = this->cmplt(v).r; return *this;}
inline rvd_type<uint8_t> operator< (const rvd_type<uint8_t>& v) const { return this->cmplt(v);}

inline rvd_type<uint8_t>& operator<= (const rvd_type<uint8_t>& v) { r = this->cmple(v).r; return *this;}
inline rvd_type<uint8_t> operator<= (const rvd_type<uint8_t>& v) const { return this->cmple(v);}

inline rvd_type<uint8_t>& operator> (const rvd_type<uint8_t>& v) { r = this->cmpgt(v).r; return *this;}
inline rvd_type<uint8_t> operator> (const rvd_type<uint8_t>& v) const { return this->cmpgt(v);}

inline rvd_type<uint8_t>& operator>= (const rvd_type<uint8_t>& v) { r = this->cmpge(v).r; return *this;}
inline rvd_type<uint8_t> operator>= (const rvd_type<uint8_t>& v) const { return this->cmpge(v);}
}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */
