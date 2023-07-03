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

inline Rvd<float64_t>& operator+= (const Rvd<float64_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<float64_t> operator+= (Rvd<float64_t>& rvd) const { return this->add(rvd); }

inline Rvd<float64_t>& operator+ (const Rvd<float64_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<float64_t> operator+ (Rvd<float64_t>& rvd) const { return this->add(rvd); }

inline Rvd<float64_t>& operator-= (const Rvd<float64_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<float64_t> operator-= (Rvd<float64_t>& rvd) const { return this->sub(rvd); }

inline Rvd<float64_t>& operator- (const Rvd<float64_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<float64_t> operator- (Rvd<float64_t>& rvd) const { return this->sub(rvd); }

inline Rvd<float64_t>& operator*= (const Rvd<float64_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<float64_t> operator*= (Rvd<float64_t>& rvd) const { return this->mul(rvd); }

inline Rvd<float64_t>& operator* (const Rvd<float64_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<float64_t> operator* (Rvd<float64_t>& rvd) const { return this->mul(rvd); }

inline Rvd<float64_t>& operator/= (const Rvd<float64_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<float64_t> operator/= (Rvd<float64_t>& rvd) const { return this->div(rvd); }

inline Rvd<float64_t>& operator/ (const Rvd<float64_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<float64_t> operator/ (Rvd<float64_t>& rvd) const { return this->div(rvd); }

inline Rvd<float64_t>& operator~ (const Rvd<float64_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<float64_t> operator~ (Rvd<float64_t>& rvd) const { return this->notb(rvd); }

inline Rvd<float64_t>& operator^= (const Rvd<float64_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<float64_t> operator^= (Rvd<float64_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<float64_t>& operator^ (const Rvd<float64_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<float64_t> operator^ (Rvd<float64_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<float64_t>& operator|= (const Rvd<float64_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<float64_t> operator|= (Rvd<float64_t>& rvd) const { return this->orb(rvd); }

inline Rvd<float64_t>& operator| (const Rvd<float64_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<float64_t> operator| (Rvd<float64_t>& rvd) const { return this->orb(rvd); }

inline Rvd<float64_t>& operator&= (const Rvd<float64_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<float64_t> operator&= (Rvd<float64_t>& rvd) const { return this->andb(rvd); }

inline Rvd<float64_t>& operator& (const Rvd<float64_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<float64_t> operator& (Rvd<float64_t>& rvd) const { return this->andb(rvd); }

inline Rvd<float64_t>& operator== (const Rvd<float64_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<float64_t> operator== (Rvd<float64_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<float64_t>& operator!= (const Rvd<float64_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<float64_t> operator!= (Rvd<float64_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<float64_t>& operator< (const Rvd<float64_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<float64_t> operator< (Rvd<float64_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<float64_t>& operator<= (const Rvd<float64_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<float64_t> operator<= (Rvd<float64_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<float64_t>& operator> (const Rvd<float64_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<float64_t> operator> (Rvd<float64_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<float64_t>& operator>= (const Rvd<float64_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<float64_t> operator>= (Rvd<float64_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<float32_t>& operator+= (const Rvd<float32_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<float32_t> operator+= (Rvd<float32_t>& rvd) const { return this->add(rvd); }

inline Rvd<float32_t>& operator+ (const Rvd<float32_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<float32_t> operator+ (Rvd<float32_t>& rvd) const { return this->add(rvd); }

inline Rvd<float32_t>& operator-= (const Rvd<float32_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<float32_t> operator-= (Rvd<float32_t>& rvd) const { return this->sub(rvd); }

inline Rvd<float32_t>& operator- (const Rvd<float32_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<float32_t> operator- (Rvd<float32_t>& rvd) const { return this->sub(rvd); }

inline Rvd<float32_t>& operator*= (const Rvd<float32_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<float32_t> operator*= (Rvd<float32_t>& rvd) const { return this->mul(rvd); }

inline Rvd<float32_t>& operator* (const Rvd<float32_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<float32_t> operator* (Rvd<float32_t>& rvd) const { return this->mul(rvd); }

inline Rvd<float32_t>& operator/= (const Rvd<float32_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<float32_t> operator/= (Rvd<float32_t>& rvd) const { return this->div(rvd); }

inline Rvd<float32_t>& operator/ (const Rvd<float32_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<float32_t> operator/ (Rvd<float32_t>& rvd) const { return this->div(rvd); }

inline Rvd<float32_t>& operator~ (const Rvd<float32_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<float32_t> operator~ (Rvd<float32_t>& rvd) const { return this->notb(rvd); }

inline Rvd<float32_t>& operator^= (const Rvd<float32_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<float32_t> operator^= (Rvd<float32_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<float32_t>& operator^ (const Rvd<float32_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<float32_t> operator^ (Rvd<float32_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<float32_t>& operator|= (const Rvd<float32_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<float32_t> operator|= (Rvd<float32_t>& rvd) const { return this->orb(rvd); }

inline Rvd<float32_t>& operator| (const Rvd<float32_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<float32_t> operator| (Rvd<float32_t>& rvd) const { return this->orb(rvd); }

inline Rvd<float32_t>& operator&= (const Rvd<float32_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<float32_t> operator&= (Rvd<float32_t>& rvd) const { return this->andb(rvd); }

inline Rvd<float32_t>& operator& (const Rvd<float32_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<float32_t> operator& (Rvd<float32_t>& rvd) const { return this->andb(rvd); }

inline Rvd<float32_t>& operator== (const Rvd<float32_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<float32_t> operator== (Rvd<float32_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<float32_t>& operator!= (const Rvd<float32_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<float32_t> operator!= (Rvd<float32_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<float32_t>& operator< (const Rvd<float32_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<float32_t> operator< (Rvd<float32_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<float32_t>& operator<= (const Rvd<float32_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<float32_t> operator<= (Rvd<float32_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<float32_t>& operator> (const Rvd<float32_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<float32_t> operator> (Rvd<float32_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<float32_t>& operator>= (const Rvd<float32_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<float32_t> operator>= (Rvd<float32_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int64_t>& operator+= (const Rvd<int64_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int64_t> operator+= (Rvd<int64_t>& rvd) const { return this->add(rvd); }

inline Rvd<int64_t>& operator+ (const Rvd<int64_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int64_t> operator+ (Rvd<int64_t>& rvd) const { return this->add(rvd); }

inline Rvd<int64_t>& operator-= (const Rvd<int64_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int64_t> operator-= (Rvd<int64_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int64_t>& operator- (const Rvd<int64_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int64_t> operator- (Rvd<int64_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int64_t>& operator*= (const Rvd<int64_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int64_t> operator*= (Rvd<int64_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int64_t>& operator* (const Rvd<int64_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int64_t> operator* (Rvd<int64_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int64_t>& operator/= (const Rvd<int64_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int64_t> operator/= (Rvd<int64_t>& rvd) const { return this->div(rvd); }

inline Rvd<int64_t>& operator/ (const Rvd<int64_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int64_t> operator/ (Rvd<int64_t>& rvd) const { return this->div(rvd); }

inline Rvd<int64_t>& operator~ (const Rvd<int64_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<int64_t> operator~ (Rvd<int64_t>& rvd) const { return this->notb(rvd); }

inline Rvd<int64_t>& operator^= (const Rvd<int64_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int64_t> operator^= (Rvd<int64_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int64_t>& operator^ (const Rvd<int64_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int64_t> operator^ (Rvd<int64_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int64_t>& operator|= (const Rvd<int64_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int64_t> operator|= (Rvd<int64_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int64_t>& operator| (const Rvd<int64_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int64_t> operator| (Rvd<int64_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int64_t>& operator&= (const Rvd<int64_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int64_t> operator&= (Rvd<int64_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int64_t>& operator& (const Rvd<int64_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int64_t> operator& (Rvd<int64_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int64_t>& operator== (const Rvd<int64_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int64_t> operator== (Rvd<int64_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int64_t>& operator!= (const Rvd<int64_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int64_t> operator!= (Rvd<int64_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int64_t>& operator< (const Rvd<int64_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int64_t> operator< (Rvd<int64_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int64_t>& operator<= (const Rvd<int64_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int64_t> operator<= (Rvd<int64_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int64_t>& operator> (const Rvd<int64_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int64_t> operator> (Rvd<int64_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int64_t>& operator>= (const Rvd<int64_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int64_t> operator>= (Rvd<int64_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int32_t>& operator+= (const Rvd<int32_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int32_t> operator+= (Rvd<int32_t>& rvd) const { return this->add(rvd); }

inline Rvd<int32_t>& operator+ (const Rvd<int32_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int32_t> operator+ (Rvd<int32_t>& rvd) const { return this->add(rvd); }

inline Rvd<int32_t>& operator-= (const Rvd<int32_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int32_t> operator-= (Rvd<int32_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int32_t>& operator- (const Rvd<int32_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int32_t> operator- (Rvd<int32_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int32_t>& operator*= (const Rvd<int32_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int32_t> operator*= (Rvd<int32_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int32_t>& operator* (const Rvd<int32_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int32_t> operator* (Rvd<int32_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int32_t>& operator/= (const Rvd<int32_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int32_t> operator/= (Rvd<int32_t>& rvd) const { return this->div(rvd); }

inline Rvd<int32_t>& operator/ (const Rvd<int32_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int32_t> operator/ (Rvd<int32_t>& rvd) const { return this->div(rvd); }

inline Rvd<int32_t>& operator~ (const Rvd<int32_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<int32_t> operator~ (Rvd<int32_t>& rvd) const { return this->notb(rvd); }

inline Rvd<int32_t>& operator^= (const Rvd<int32_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int32_t> operator^= (Rvd<int32_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int32_t>& operator^ (const Rvd<int32_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int32_t> operator^ (Rvd<int32_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int32_t>& operator|= (const Rvd<int32_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int32_t> operator|= (Rvd<int32_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int32_t>& operator| (const Rvd<int32_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int32_t> operator| (Rvd<int32_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int32_t>& operator&= (const Rvd<int32_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int32_t> operator&= (Rvd<int32_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int32_t>& operator& (const Rvd<int32_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int32_t> operator& (Rvd<int32_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int32_t>& operator== (const Rvd<int32_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int32_t> operator== (Rvd<int32_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int32_t>& operator!= (const Rvd<int32_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int32_t> operator!= (Rvd<int32_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int32_t>& operator< (const Rvd<int32_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int32_t> operator< (Rvd<int32_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int32_t>& operator<= (const Rvd<int32_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int32_t> operator<= (Rvd<int32_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int32_t>& operator> (const Rvd<int32_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int32_t> operator> (Rvd<int32_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int32_t>& operator>= (const Rvd<int32_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int32_t> operator>= (Rvd<int32_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int16_t>& operator+= (const Rvd<int16_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int16_t> operator+= (Rvd<int16_t>& rvd) const { return this->add(rvd); }

inline Rvd<int16_t>& operator+ (const Rvd<int16_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int16_t> operator+ (Rvd<int16_t>& rvd) const { return this->add(rvd); }

inline Rvd<int16_t>& operator-= (const Rvd<int16_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int16_t> operator-= (Rvd<int16_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int16_t>& operator- (const Rvd<int16_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int16_t> operator- (Rvd<int16_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int16_t>& operator*= (const Rvd<int16_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int16_t> operator*= (Rvd<int16_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int16_t>& operator* (const Rvd<int16_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int16_t> operator* (Rvd<int16_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int16_t>& operator/= (const Rvd<int16_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int16_t> operator/= (Rvd<int16_t>& rvd) const { return this->div(rvd); }

inline Rvd<int16_t>& operator/ (const Rvd<int16_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int16_t> operator/ (Rvd<int16_t>& rvd) const { return this->div(rvd); }

inline Rvd<int16_t>& operator~ (const Rvd<int16_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<int16_t> operator~ (Rvd<int16_t>& rvd) const { return this->notb(rvd); }

inline Rvd<int16_t>& operator^= (const Rvd<int16_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int16_t> operator^= (Rvd<int16_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int16_t>& operator^ (const Rvd<int16_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int16_t> operator^ (Rvd<int16_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int16_t>& operator|= (const Rvd<int16_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int16_t> operator|= (Rvd<int16_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int16_t>& operator| (const Rvd<int16_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int16_t> operator| (Rvd<int16_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int16_t>& operator&= (const Rvd<int16_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int16_t> operator&= (Rvd<int16_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int16_t>& operator& (const Rvd<int16_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int16_t> operator& (Rvd<int16_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int16_t>& operator== (const Rvd<int16_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int16_t> operator== (Rvd<int16_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int16_t>& operator!= (const Rvd<int16_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int16_t> operator!= (Rvd<int16_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int16_t>& operator< (const Rvd<int16_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int16_t> operator< (Rvd<int16_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int16_t>& operator<= (const Rvd<int16_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int16_t> operator<= (Rvd<int16_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int16_t>& operator> (const Rvd<int16_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int16_t> operator> (Rvd<int16_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int16_t>& operator>= (const Rvd<int16_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int16_t> operator>= (Rvd<int16_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int8_t>& operator+= (const Rvd<int8_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int8_t> operator+= (Rvd<int8_t>& rvd) const { return this->add(rvd); }

inline Rvd<int8_t>& operator+ (const Rvd<int8_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<int8_t> operator+ (Rvd<int8_t>& rvd) const { return this->add(rvd); }

inline Rvd<int8_t>& operator-= (const Rvd<int8_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int8_t> operator-= (Rvd<int8_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int8_t>& operator- (const Rvd<int8_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<int8_t> operator- (Rvd<int8_t>& rvd) const { return this->sub(rvd); }

inline Rvd<int8_t>& operator*= (const Rvd<int8_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int8_t> operator*= (Rvd<int8_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int8_t>& operator* (const Rvd<int8_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<int8_t> operator* (Rvd<int8_t>& rvd) const { return this->mul(rvd); }

inline Rvd<int8_t>& operator/= (const Rvd<int8_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int8_t> operator/= (Rvd<int8_t>& rvd) const { return this->div(rvd); }

inline Rvd<int8_t>& operator/ (const Rvd<int8_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<int8_t> operator/ (Rvd<int8_t>& rvd) const { return this->div(rvd); }

inline Rvd<int8_t>& operator~ (const Rvd<int8_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<int8_t> operator~ (Rvd<int8_t>& rvd) const { return this->notb(rvd); }

inline Rvd<int8_t>& operator^= (const Rvd<int8_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int8_t> operator^= (Rvd<int8_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int8_t>& operator^ (const Rvd<int8_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<int8_t> operator^ (Rvd<int8_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<int8_t>& operator|= (const Rvd<int8_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int8_t> operator|= (Rvd<int8_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int8_t>& operator| (const Rvd<int8_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<int8_t> operator| (Rvd<int8_t>& rvd) const { return this->orb(rvd); }

inline Rvd<int8_t>& operator&= (const Rvd<int8_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int8_t> operator&= (Rvd<int8_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int8_t>& operator& (const Rvd<int8_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<int8_t> operator& (Rvd<int8_t>& rvd) const { return this->andb(rvd); }

inline Rvd<int8_t>& operator== (const Rvd<int8_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int8_t> operator== (Rvd<int8_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int8_t>& operator!= (const Rvd<int8_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int8_t> operator!= (Rvd<int8_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int8_t>& operator< (const Rvd<int8_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int8_t> operator< (Rvd<int8_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int8_t>& operator<= (const Rvd<int8_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int8_t> operator<= (Rvd<int8_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int8_t>& operator> (const Rvd<int8_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int8_t> operator> (Rvd<int8_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int8_t>& operator>= (const Rvd<int8_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int8_t> operator>= (Rvd<int8_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint64_t>& operator+= (const Rvd<uint64_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint64_t> operator+= (Rvd<uint64_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint64_t>& operator+ (const Rvd<uint64_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint64_t> operator+ (Rvd<uint64_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint64_t>& operator-= (const Rvd<uint64_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint64_t> operator-= (Rvd<uint64_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint64_t>& operator- (const Rvd<uint64_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint64_t> operator- (Rvd<uint64_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint64_t>& operator*= (const Rvd<uint64_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint64_t> operator*= (Rvd<uint64_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint64_t>& operator* (const Rvd<uint64_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint64_t> operator* (Rvd<uint64_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint64_t>& operator/= (const Rvd<uint64_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint64_t> operator/= (Rvd<uint64_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint64_t>& operator/ (const Rvd<uint64_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint64_t> operator/ (Rvd<uint64_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint64_t>& operator~ (const Rvd<uint64_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<uint64_t> operator~ (Rvd<uint64_t>& rvd) const { return this->notb(rvd); }

inline Rvd<uint64_t>& operator^= (const Rvd<uint64_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint64_t> operator^= (Rvd<uint64_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint64_t>& operator^ (const Rvd<uint64_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint64_t> operator^ (Rvd<uint64_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint64_t>& operator|= (const Rvd<uint64_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint64_t> operator|= (Rvd<uint64_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint64_t>& operator| (const Rvd<uint64_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint64_t> operator| (Rvd<uint64_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint64_t>& operator&= (const Rvd<uint64_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint64_t> operator&= (Rvd<uint64_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint64_t>& operator& (const Rvd<uint64_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint64_t> operator& (Rvd<uint64_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint64_t>& operator== (const Rvd<uint64_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint64_t> operator== (Rvd<uint64_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint64_t>& operator!= (const Rvd<uint64_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint64_t> operator!= (Rvd<uint64_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint64_t>& operator< (const Rvd<uint64_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint64_t> operator< (Rvd<uint64_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint64_t>& operator<= (const Rvd<uint64_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint64_t> operator<= (Rvd<uint64_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint64_t>& operator> (const Rvd<uint64_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint64_t> operator> (Rvd<uint64_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint64_t>& operator>= (const Rvd<uint64_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint64_t> operator>= (Rvd<uint64_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint32_t>& operator+= (const Rvd<uint32_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint32_t> operator+= (Rvd<uint32_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint32_t>& operator+ (const Rvd<uint32_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint32_t> operator+ (Rvd<uint32_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint32_t>& operator-= (const Rvd<uint32_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint32_t> operator-= (Rvd<uint32_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint32_t>& operator- (const Rvd<uint32_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint32_t> operator- (Rvd<uint32_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint32_t>& operator*= (const Rvd<uint32_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint32_t> operator*= (Rvd<uint32_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint32_t>& operator* (const Rvd<uint32_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint32_t> operator* (Rvd<uint32_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint32_t>& operator/= (const Rvd<uint32_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint32_t> operator/= (Rvd<uint32_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint32_t>& operator/ (const Rvd<uint32_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint32_t> operator/ (Rvd<uint32_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint32_t>& operator~ (const Rvd<uint32_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<uint32_t> operator~ (Rvd<uint32_t>& rvd) const { return this->notb(rvd); }

inline Rvd<uint32_t>& operator^= (const Rvd<uint32_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint32_t> operator^= (Rvd<uint32_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint32_t>& operator^ (const Rvd<uint32_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint32_t> operator^ (Rvd<uint32_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint32_t>& operator|= (const Rvd<uint32_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint32_t> operator|= (Rvd<uint32_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint32_t>& operator| (const Rvd<uint32_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint32_t> operator| (Rvd<uint32_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint32_t>& operator&= (const Rvd<uint32_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint32_t> operator&= (Rvd<uint32_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint32_t>& operator& (const Rvd<uint32_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint32_t> operator& (Rvd<uint32_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint32_t>& operator== (const Rvd<uint32_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint32_t> operator== (Rvd<uint32_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint32_t>& operator!= (const Rvd<uint32_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint32_t> operator!= (Rvd<uint32_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint32_t>& operator< (const Rvd<uint32_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint32_t> operator< (Rvd<uint32_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint32_t>& operator<= (const Rvd<uint32_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint32_t> operator<= (Rvd<uint32_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint32_t>& operator> (const Rvd<uint32_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint32_t> operator> (Rvd<uint32_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint32_t>& operator>= (const Rvd<uint32_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint32_t> operator>= (Rvd<uint32_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint16_t>& operator+= (const Rvd<uint16_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint16_t> operator+= (Rvd<uint16_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint16_t>& operator+ (const Rvd<uint16_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint16_t> operator+ (Rvd<uint16_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint16_t>& operator-= (const Rvd<uint16_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint16_t> operator-= (Rvd<uint16_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint16_t>& operator- (const Rvd<uint16_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint16_t> operator- (Rvd<uint16_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint16_t>& operator*= (const Rvd<uint16_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint16_t> operator*= (Rvd<uint16_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint16_t>& operator* (const Rvd<uint16_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint16_t> operator* (Rvd<uint16_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint16_t>& operator/= (const Rvd<uint16_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint16_t> operator/= (Rvd<uint16_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint16_t>& operator/ (const Rvd<uint16_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint16_t> operator/ (Rvd<uint16_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint16_t>& operator~ (const Rvd<uint16_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<uint16_t> operator~ (Rvd<uint16_t>& rvd) const { return this->notb(rvd); }

inline Rvd<uint16_t>& operator^= (const Rvd<uint16_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint16_t> operator^= (Rvd<uint16_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint16_t>& operator^ (const Rvd<uint16_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint16_t> operator^ (Rvd<uint16_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint16_t>& operator|= (const Rvd<uint16_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint16_t> operator|= (Rvd<uint16_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint16_t>& operator| (const Rvd<uint16_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint16_t> operator| (Rvd<uint16_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint16_t>& operator&= (const Rvd<uint16_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint16_t> operator&= (Rvd<uint16_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint16_t>& operator& (const Rvd<uint16_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint16_t> operator& (Rvd<uint16_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint16_t>& operator== (const Rvd<uint16_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint16_t> operator== (Rvd<uint16_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint16_t>& operator!= (const Rvd<uint16_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint16_t> operator!= (Rvd<uint16_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint16_t>& operator< (const Rvd<uint16_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint16_t> operator< (Rvd<uint16_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint16_t>& operator<= (const Rvd<uint16_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint16_t> operator<= (Rvd<uint16_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint16_t>& operator> (const Rvd<uint16_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint16_t> operator> (Rvd<uint16_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint16_t>& operator>= (const Rvd<uint16_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint16_t> operator>= (Rvd<uint16_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint8_t>& operator+= (const Rvd<uint8_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint8_t> operator+= (Rvd<uint8_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint8_t>& operator+ (const Rvd<uint8_t>& rvd) { r = this->add(rvd).r; return *this; }
inline Rvd<uint8_t> operator+ (Rvd<uint8_t>& rvd) const { return this->add(rvd); }

inline Rvd<uint8_t>& operator-= (const Rvd<uint8_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint8_t> operator-= (Rvd<uint8_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint8_t>& operator- (const Rvd<uint8_t>& rvd) { r = this->sub(rvd).r; return *this; }
inline Rvd<uint8_t> operator- (Rvd<uint8_t>& rvd) const { return this->sub(rvd); }

inline Rvd<uint8_t>& operator*= (const Rvd<uint8_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint8_t> operator*= (Rvd<uint8_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint8_t>& operator* (const Rvd<uint8_t>& rvd) { r = this->mul(rvd).r; return *this; }
inline Rvd<uint8_t> operator* (Rvd<uint8_t>& rvd) const { return this->mul(rvd); }

inline Rvd<uint8_t>& operator/= (const Rvd<uint8_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint8_t> operator/= (Rvd<uint8_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint8_t>& operator/ (const Rvd<uint8_t>& rvd) { r = this->div(rvd).r; return *this; }
inline Rvd<uint8_t> operator/ (Rvd<uint8_t>& rvd) const { return this->div(rvd); }

inline Rvd<uint8_t>& operator~ (const Rvd<uint8_t>& rvd) { r = this->notb(rvd).r; return *this; }
inline Rvd<uint8_t> operator~ (Rvd<uint8_t>& rvd) const { return this->notb(rvd); }

inline Rvd<uint8_t>& operator^= (const Rvd<uint8_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint8_t> operator^= (Rvd<uint8_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint8_t>& operator^ (const Rvd<uint8_t>& rvd) { r = this->xorb(rvd).r; return *this; }
inline Rvd<uint8_t> operator^ (Rvd<uint8_t>& rvd) const { return this->xorb(rvd); }

inline Rvd<uint8_t>& operator|= (const Rvd<uint8_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint8_t> operator|= (Rvd<uint8_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint8_t>& operator| (const Rvd<uint8_t>& rvd) { r = this->orb(rvd).r; return *this; }
inline Rvd<uint8_t> operator| (Rvd<uint8_t>& rvd) const { return this->orb(rvd); }

inline Rvd<uint8_t>& operator&= (const Rvd<uint8_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint8_t> operator&= (Rvd<uint8_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint8_t>& operator& (const Rvd<uint8_t>& rvd) { r = this->andb(rvd).r; return *this; }
inline Rvd<uint8_t> operator& (Rvd<uint8_t>& rvd) const { return this->andb(rvd); }

inline Rvd<uint8_t>& operator== (const Rvd<uint8_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint8_t> operator== (Rvd<uint8_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint8_t>& operator!= (const Rvd<uint8_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint8_t> operator!= (Rvd<uint8_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint8_t>& operator< (const Rvd<uint8_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint8_t> operator< (Rvd<uint8_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint8_t>& operator<= (const Rvd<uint8_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint8_t> operator<= (Rvd<uint8_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint8_t>& operator> (const Rvd<uint8_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint8_t> operator> (Rvd<uint8_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint8_t>& operator>= (const Rvd<uint8_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint8_t> operator>= (Rvd<uint8_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<float64_t>& operator== (const Rvd<float64_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<float64_t> operator== (Rvd<float64_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<float64_t>& operator!= (const Rvd<float64_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<float64_t> operator!= (Rvd<float64_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<float64_t>& operator< (const Rvd<float64_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<float64_t> operator< (Rvd<float64_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<float64_t>& operator<= (const Rvd<float64_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<float64_t> operator<= (Rvd<float64_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<float64_t>& operator> (const Rvd<float64_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<float64_t> operator> (Rvd<float64_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<float64_t>& operator>= (const Rvd<float64_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<float64_t> operator>= (Rvd<float64_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<float32_t>& operator== (const Rvd<float32_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<float32_t> operator== (Rvd<float32_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<float32_t>& operator!= (const Rvd<float32_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<float32_t> operator!= (Rvd<float32_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<float32_t>& operator< (const Rvd<float32_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<float32_t> operator< (Rvd<float32_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<float32_t>& operator<= (const Rvd<float32_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<float32_t> operator<= (Rvd<float32_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<float32_t>& operator> (const Rvd<float32_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<float32_t> operator> (Rvd<float32_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<float32_t>& operator>= (const Rvd<float32_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<float32_t> operator>= (Rvd<float32_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int64_t>& operator== (const Rvd<int64_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int64_t> operator== (Rvd<int64_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int64_t>& operator!= (const Rvd<int64_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int64_t> operator!= (Rvd<int64_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int64_t>& operator< (const Rvd<int64_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int64_t> operator< (Rvd<int64_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int64_t>& operator<= (const Rvd<int64_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int64_t> operator<= (Rvd<int64_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int64_t>& operator> (const Rvd<int64_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int64_t> operator> (Rvd<int64_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int64_t>& operator>= (const Rvd<int64_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int64_t> operator>= (Rvd<int64_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int32_t>& operator== (const Rvd<int32_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int32_t> operator== (Rvd<int32_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int32_t>& operator!= (const Rvd<int32_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int32_t> operator!= (Rvd<int32_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int32_t>& operator< (const Rvd<int32_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int32_t> operator< (Rvd<int32_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int32_t>& operator<= (const Rvd<int32_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int32_t> operator<= (Rvd<int32_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int32_t>& operator> (const Rvd<int32_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int32_t> operator> (Rvd<int32_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int32_t>& operator>= (const Rvd<int32_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int32_t> operator>= (Rvd<int32_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int16_t>& operator== (const Rvd<int16_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int16_t> operator== (Rvd<int16_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int16_t>& operator!= (const Rvd<int16_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int16_t> operator!= (Rvd<int16_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int16_t>& operator< (const Rvd<int16_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int16_t> operator< (Rvd<int16_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int16_t>& operator<= (const Rvd<int16_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int16_t> operator<= (Rvd<int16_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int16_t>& operator> (const Rvd<int16_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int16_t> operator> (Rvd<int16_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int16_t>& operator>= (const Rvd<int16_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int16_t> operator>= (Rvd<int16_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<int8_t>& operator== (const Rvd<int8_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<int8_t> operator== (Rvd<int8_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<int8_t>& operator!= (const Rvd<int8_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<int8_t> operator!= (Rvd<int8_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<int8_t>& operator< (const Rvd<int8_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<int8_t> operator< (Rvd<int8_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<int8_t>& operator<= (const Rvd<int8_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<int8_t> operator<= (Rvd<int8_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<int8_t>& operator> (const Rvd<int8_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<int8_t> operator> (Rvd<int8_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<int8_t>& operator>= (const Rvd<int8_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<int8_t> operator>= (Rvd<int8_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint64_t>& operator== (const Rvd<uint64_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint64_t> operator== (Rvd<uint64_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint64_t>& operator!= (const Rvd<uint64_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint64_t> operator!= (Rvd<uint64_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint64_t>& operator< (const Rvd<uint64_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint64_t> operator< (Rvd<uint64_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint64_t>& operator<= (const Rvd<uint64_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint64_t> operator<= (Rvd<uint64_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint64_t>& operator> (const Rvd<uint64_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint64_t> operator> (Rvd<uint64_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint64_t>& operator>= (const Rvd<uint64_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint64_t> operator>= (Rvd<uint64_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint32_t>& operator== (const Rvd<uint32_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint32_t> operator== (Rvd<uint32_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint32_t>& operator!= (const Rvd<uint32_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint32_t> operator!= (Rvd<uint32_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint32_t>& operator< (const Rvd<uint32_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint32_t> operator< (Rvd<uint32_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint32_t>& operator<= (const Rvd<uint32_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint32_t> operator<= (Rvd<uint32_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint32_t>& operator> (const Rvd<uint32_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint32_t> operator> (Rvd<uint32_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint32_t>& operator>= (const Rvd<uint32_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint32_t> operator>= (Rvd<uint32_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint16_t>& operator== (const Rvd<uint16_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint16_t> operator== (Rvd<uint16_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint16_t>& operator!= (const Rvd<uint16_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint16_t> operator!= (Rvd<uint16_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint16_t>& operator< (const Rvd<uint16_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint16_t> operator< (Rvd<uint16_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint16_t>& operator<= (const Rvd<uint16_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint16_t> operator<= (Rvd<uint16_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint16_t>& operator> (const Rvd<uint16_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint16_t> operator> (Rvd<uint16_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint16_t>& operator>= (const Rvd<uint16_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint16_t> operator>= (Rvd<uint16_t>& rvd) const { return this->cmpge(rvd); }

inline Rvd<uint8_t>& operator== (const Rvd<uint8_t>& rvd) { r = this->cmpeq(rvd).r; return *this; }
inline Rvd<uint8_t> operator== (Rvd<uint8_t>& rvd) const { return this->cmpeq(rvd); }

inline Rvd<uint8_t>& operator!= (const Rvd<uint8_t>& rvd) { r = this->cmpneq(rvd).r; return *this; }
inline Rvd<uint8_t> operator!= (Rvd<uint8_t>& rvd) const { return this->cmpneq(rvd); }

inline Rvd<uint8_t>& operator< (const Rvd<uint8_t>& rvd) { r = this->cmplt(rvd).r; return *this; }
inline Rvd<uint8_t> operator< (Rvd<uint8_t>& rvd) const { return this->cmplt(rvd); }

inline Rvd<uint8_t>& operator<= (const Rvd<uint8_t>& rvd) { r = this->cmple(rvd).r; return *this; }
inline Rvd<uint8_t> operator<= (Rvd<uint8_t>& rvd) const { return this->cmple(rvd); }

inline Rvd<uint8_t>& operator> (const Rvd<uint8_t>& rvd) { r = this->cmpgt(rvd).r; return *this; }
inline Rvd<uint8_t> operator> (Rvd<uint8_t>& rvd) const { return this->cmpgt(rvd); }

inline Rvd<uint8_t>& operator>= (const Rvd<uint8_t>& rvd) { r = this->cmpge(rvd).r; return *this; }
inline Rvd<uint8_t> operator>= (Rvd<uint8_t>& rvd) const { return this->cmpge(rvd); }
}
// ------------------------------------------------------------------------------------------------------ operators (Msk) 
class Rvm
{
public:
	rvm<T, LMUL>  m;

	static constexpr int size() {return mipp::N<T, LMUL>(); };

	Rvm() {}
	Rvm(rvm<T, LMUL>  m) : m(m) {}
inline Rvm<N<float64_t>()> operator== (rvm<float64_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<float64_t>()> operator!= (rvm<float64_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<float64_t>()> operator< (rvm<float64_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<float64_t>()> operator<= (rvm<float64_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<float64_t>()> operator> (rvm<float64_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<float64_t>()> operator>= (rvm<float64_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<float32_t>()> operator== (rvm<float32_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<float32_t>()> operator!= (rvm<float32_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<float32_t>()> operator< (rvm<float32_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<float32_t>()> operator<= (rvm<float32_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<float32_t>()> operator> (rvm<float32_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<float32_t>()> operator>= (rvm<float32_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<int64_t>()> operator== (rvm<int64_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<int64_t>()> operator!= (rvm<int64_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<int64_t>()> operator< (rvm<int64_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<int64_t>()> operator<= (rvm<int64_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<int64_t>()> operator> (rvm<int64_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<int64_t>()> operator>= (rvm<int64_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<int32_t>()> operator== (rvm<int32_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<int32_t>()> operator!= (rvm<int32_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<int32_t>()> operator< (rvm<int32_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<int32_t>()> operator<= (rvm<int32_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<int32_t>()> operator> (rvm<int32_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<int32_t>()> operator>= (rvm<int32_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<int16_t>()> operator== (rvm<int16_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<int16_t>()> operator!= (rvm<int16_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<int16_t>()> operator< (rvm<int16_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<int16_t>()> operator<= (rvm<int16_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<int16_t>()> operator> (rvm<int16_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<int16_t>()> operator>= (rvm<int16_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<int8_t>()> operator== (rvm<int8_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<int8_t>()> operator!= (rvm<int8_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<int8_t>()> operator< (rvm<int8_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<int8_t>()> operator<= (rvm<int8_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<int8_t>()> operator> (rvm<int8_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<int8_t>()> operator>= (rvm<int8_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<uint64_t>()> operator== (rvm<uint64_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<uint64_t>()> operator!= (rvm<uint64_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<uint64_t>()> operator< (rvm<uint64_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<uint64_t>()> operator<= (rvm<uint64_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<uint64_t>()> operator> (rvm<uint64_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<uint64_t>()> operator>= (rvm<uint64_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<uint32_t>()> operator== (rvm<uint32_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<uint32_t>()> operator!= (rvm<uint32_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<uint32_t>()> operator< (rvm<uint32_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<uint32_t>()> operator<= (rvm<uint32_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<uint32_t>()> operator> (rvm<uint32_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<uint32_t>()> operator>= (rvm<uint32_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<uint16_t>()> operator== (rvm<uint16_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<uint16_t>()> operator!= (rvm<uint16_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<uint16_t>()> operator< (rvm<uint16_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<uint16_t>()> operator<= (rvm<uint16_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<uint16_t>()> operator> (rvm<uint16_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<uint16_t>()> operator>= (rvm<uint16_t> rvm) const { return this->cmpge (rvm);}
inline Rvm<N<uint8_t>()> operator== (rvm<uint8_t> rvm) const { return this->cmpeq (rvm);}
inline Rvm<N<uint8_t>()> operator!= (rvm<uint8_t> rvm) const { return this->cmpneq (rvm);}
inline Rvm<N<uint8_t>()> operator< (rvm<uint8_t> rvm) const { return this->cmplt (rvm);}
inline Rvm<N<uint8_t>()> operator<= (rvm<uint8_t> rvm) const { return this->cmple (rvm);}
inline Rvm<N<uint8_t>()> operator> (rvm<uint8_t> rvm) const { return this->cmpgt (rvm);}
inline Rvm<N<uint8_t>()> operator>= (rvm<uint8_t> rvm) const { return this->cmpge (rvm);}
}
#ifndef MIPP_NO_INTRINSICS
	inline bool operator[](const size_t index) const { return mipp::get<N>(this->, index); }
#else
	inline bool operator[](const size_t index) const { return m; }
#endif
};
}

#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_HPP_ */
