#include "mipp.h"

// ---------------------------------------------------------------------------------------------- ARM SVE Specific size
// --------------------------------------------------------------------------------------------------------------------
#if defined(__ARM_FEATURE_SVE)

	// ---------------------------------------------------------------------------------------------------------- blend
	template <>
	inline reg blend<double>(const reg v1, const reg v2, const msk m) {
		return svreinterpret_f32_f64(svsel_f64(m,svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline reg blend<float>(const reg v1, const reg v2, const msk m) {
		return svsel_f32(m,v1,v2);
	}

	template <>
	inline reg blend<int64_t>(const reg v1, const reg v2, const msk m) {
		return svreinterpret_f32_s64(svsel_s64(m,svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2)));
	}


	template <>
	inline reg blend<int32_t>(const reg v1, const reg v2, const msk m) {
		return svreinterpret_f32_s32(svsel_s32(m,svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2)));
	}

	// all operations is masked so masked before
	// -------------------------------------------------------------------------------------------------------- maskzld
	inline reg _maskzld(const msk m, const float* memp){
		return svld1_f32(m, memp);
	}

	inline reg _maskzld(const msk m, const double* memp){
		return svreinterpret_f32_f64(svld1_f64(m, memp));
	}

	inline reg _maskzld(const msk m, const int64_t* memp){
		return svreinterpret_f32_s64(svld1_s64(m, memp));
	}

	inline reg _maskzld(const msk m, const int32_t* memp){
		return svreinterpret_f32_s32(svld1_s32(m, memp));
	}

	inline void _maskst(const msk m, double* memp, const reg a){
		svst1_f64(m,memp,svreinterpret_f64_f32(a));
	}

	inline void _maskst(const msk m, float* memp, const reg a){
		svst1_f32(m,memp,a);
	}

	inline void _maskst(const msk m, int64_t* memp, const reg a){
		svst1_s64(m,memp,svreinterpret_s64_f32(a));
	}

	inline void _maskst(const msk m, int32_t* memp, const reg a){
		svst1_s32(m,memp,svreinterpret_s32_f32(a));
	}

	// ----------------------------------------------------------------------------------------------------------- load
	template <>
	inline reg load<float>(const float *mem_addr) {
		return _maskzld(svptrue_b32(),mem_addr);
	}

	template <>
	inline reg load<double>(const double *mem_addr) {
		return _maskzld(svptrue_b64(),mem_addr);
	}

	template <>
	inline reg load<int64_t>(const int64_t *mem_addr) {
		return _maskzld(svptrue_b64(),mem_addr);
	}

	template <>
	inline reg load<int32_t>(const int32_t *mem_addr) {
		return _maskzld(svptrue_b32(),mem_addr);
	}

	// ---------------------------------------------------------------------------------------------------------- store
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		_maskst(svptrue_b32(),mem_addr,v);
	}

	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		_maskst(svptrue_b64(),mem_addr,v);
	}

	template <>
	inline void store<int64_t>(int64_t *mem_addr, const reg v) {
		_maskst(svptrue_b64(),mem_addr,v);
	}

	template <>
	inline void store<int32_t>(int32_t *mem_addr, const reg v) {
		_maskst(svptrue_b32(),mem_addr,v);
	}

#ifdef __ARM_FEATURE_UNALIGNED
	// ---------------------------------------------------------------------------------------------------------- loadu
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return load<float>(mem_addr);
	}

	template <>
	inline reg loadu<double>(const double *mem_addr) {
		return load<double>(mem_addr);
	}

	template <>
	inline reg loadu<int64_t>(const int64_t *mem_addr) {
		return load<int64_t>(mem_addr);
	}

	template <>
	inline reg loadu<int32_t>(const int32_t *mem_addr) {
		return load<int32_t>(mem_addr);
	}

	// --------------------------------------------------------------------------------------------------------- storeu
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		store<float>(mem_addr,v);
	}

	template <>
	inline void storeu<double>(double *mem_addr, const reg v) {
		store<double>(mem_addr,v);
	}

	template <>
	inline void storeu<int64_t>(int64_t *mem_addr, const reg v) {
		store<int64_t>(mem_addr,v);
	}

	template <>
	inline void storeu<int32_t>(int32_t *mem_addr, const reg v) {
		store<int32_t>(mem_addr,v);
	}

#endif
	template <>
	inline reg maskzld<float>(const msk m, const float* memp){
		return _maskzld(m,memp);
	}

	template <>
	inline reg maskzld<double>(const msk m, const double* memp){
		return _maskzld(m,memp);
	}

	template <>
	inline reg maskzld<int64_t>(const msk m, const int64_t* memp){
		return _maskzld(m,memp);
	}

	template <>
	inline reg maskzld<int32_t>(const msk m, const int32_t* memp){
		return _maskzld(m,memp);
	}

	// --------------------------------------------------------------------------------------------------------- maskst
	template <>
	inline void maskst<double>(const msk m, double* memp, const reg a){
		_maskst(m,memp,a);
	}

	template <>
	inline void maskst<float>(const msk m, float* memp, const reg a){
		_maskst(m,memp,a);
	}

	template <>
	inline void maskst<int64_t>(const msk m, int64_t* memp, const reg a){
		_maskst(m,memp,a);
	}

	template <>
	inline void maskst<int32_t>(const msk m, int32_t* memp, const reg a){
		_maskst(m,memp,a);
	}

	// all operations masked do it first
	// -------------------------------------------------------------------------------------------------- masked gather
	template <>
	inline reg maskzgat<double,int64_t>(const msk m, const double *mem_addr, const reg idx) {
		return svreinterpret_f32_f64(svld1_gather_s64index_f64(m,mem_addr,svreinterpret_s64_f32(idx)));
	}

	template <>
	inline reg maskzgat<float,int32_t>(const msk m, const float *mem_addr, const reg idx) {
		return svld1_gather_s32index_f32(m,mem_addr,svreinterpret_s32_f32(idx));
	}

	template <>
	inline reg maskzgat<int64_t,int64_t>(const msk m, const int64_t *mem_addr, const reg idx) {
		return svreinterpret_f32_s64(svld1_gather_s64index_s64(m,mem_addr,svreinterpret_s64_f32(idx)));
	}

	template <>
	inline reg maskzgat<int32_t,int32_t>(const msk m, const int32_t *mem_addr, const reg idx) {
		return svreinterpret_f32_s32(svld1_gather_s32index_s32(m,mem_addr,svreinterpret_s32_f32(idx)));
	}

	// --------------------------------------------------------------------------------------------------------- gather
	template <>
	inline reg gather<double,int64_t>(const double *mem_addr, const reg idx) {
		return maskzgat<double,int64_t>(svptrue_b64(),mem_addr,idx);
	}

	template <>
	inline reg gather<float,int32_t>(const float *mem_addr, const reg idx) {
		return maskzgat<float,int32_t>(svptrue_b32(),mem_addr,idx);
	}

	template <>
	inline reg gather<int64_t,int64_t>(const int64_t *mem_addr, const reg idx) {
		return maskzgat<int64_t,int64_t>(svptrue_b64(),mem_addr,idx);
	}

	template <>
	inline reg gather<int32_t,int32_t>(const int32_t *mem_addr, const reg idx) {
		return maskzgat<int32_t,int32_t>(svptrue_b32(),mem_addr,idx);
	}

	// ------------------------------------------------------------------------------------------------- masked scatter
	template <>
	inline void masksca<double,int64_t>(const msk m, double *mem_addr, const reg idx, const reg r) {
		svst1_scatter_s64index_f64(m,mem_addr,svreinterpret_s64_f32(idx),svreinterpret_f64_f32(r));
	}

	template <>
	inline void masksca<float,int32_t>(const msk m, float *mem_addr, const reg idx, const reg r) {
		svst1_scatter_s32index_f32(m,mem_addr,svreinterpret_s32_f32(idx),r);
	}

	template <>
	inline void masksca<int64_t,int64_t>(const msk m, int64_t *mem_addr, const reg idx, const reg r) {
		svst1_scatter_s64index_s64(m,mem_addr,svreinterpret_s64_f32(idx),svreinterpret_s64_f32(r));
	}

	template <>
	inline void masksca<int32_t,int32_t>(const msk m, int32_t *mem_addr, const reg idx, const reg r) {
		svst1_scatter_s32index_s32(m,mem_addr,svreinterpret_s32_f32(idx),svreinterpret_s32_f32(r));
	}

	// -------------------------------------------------------------------------------------------------------- scatter
	template <>
	inline void scatter<double,int64_t>(double *mem_addr, const reg idx, const reg r) {
		masksca<double,int64_t>(svptrue_b64(),mem_addr,idx,r);
	}

	template <>
	inline void scatter<float,int32_t>(float *mem_addr, const reg idx, const reg r) {
		masksca<float,int32_t>(svptrue_b32(),mem_addr,idx,r);
	}

	template <>
	inline void scatter<int64_t,int64_t>(int64_t *mem_addr, const reg idx, const reg r) {
		masksca<int64_t,int64_t>(svptrue_b64(),mem_addr,idx,r);
	}

	template <>
	inline void scatter<int32_t,int32_t>(int32_t *mem_addr, const reg idx, const reg r) {
		masksca<int32_t,int32_t>(svptrue_b32(),mem_addr,idx,r);
	}
	// ------------------------------------------------------------------------------------------------------------ add
	// ------------------ float
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return svadd_f32_z(svptrue_b32(),v1,v2);
	}

	template <>
	inline reg mask<float,add<float>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svadd_f32_m(m,blend<float>(v1,src,m),v2);
	}

	template <>
	inline Reg<float> mask<float,add<float>>(const Msk<nElReg<float>()> m, const Reg<float> src, const Reg<float> v1, const Reg<float> v2) {
		return mask<float,add<float>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<float,add<float>>(const msk m, const reg v1, const reg v2) {
		return svadd_f32_z(m,v1,v2);
	}

	template <>
	inline Reg<float> maskz<float,add<float>>(const Msk<nElReg<float>()> m, const Reg<float> v1, const Reg<float> v2) {
		return maskz<float,add<float>>(m.m, v1.r, v2.r);
	}

	// ------------------ double
	template <>
	inline reg add<double>(const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svadd_f64_z(svptrue_b64(),svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline reg mask<double,add<double>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svadd_f64_m(m,svreinterpret_f64_f32(blend<double>(v1,src,m)),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline Reg<double> mask<double,add<double>>(const Msk<nElReg<double>()> m, const Reg<double> src, const Reg<double> v1, const Reg<double> v2) {
		return mask<double,add<double>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<double,add<double>>(const msk m, const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svadd_f64_z(m,svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline Reg<double> maskz<double,add<double>>(const Msk<nElReg<double>()> m, const Reg<double> v1, const Reg<double> v2) {
		return maskz<double,add<double>>(m.m, v1.r, v2.r);
	}

	// ------------------ int64_t
	template <>
	inline reg add<int64_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svadd_s64_z(svptrue_b64(),svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline reg mask<int64_t,add<int64_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svadd_s64_m(m,svreinterpret_s64_f32(blend<int64_t>(v1,src,m)),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline Reg<int64_t> mask<int64_t,add<int64_t>>(const Msk<nElReg<int64_t>()> m, const Reg<int64_t> src, const Reg<int64_t> v1, const Reg<int64_t> v2) {
		return mask<int64_t,add<int64_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int64_t,add<int64_t>>(const msk m, const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svadd_s64_z(m,svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline Reg<int64_t> maskz<int64_t,add<int64_t>>(const Msk<nElReg<int64_t>()> m, const Reg<int64_t> v1, const Reg<int64_t> v2) {
		return maskz<int64_t,add<int64_t>>(m.m, v1.r, v2.r);
	}

	// ------------------ int32_t
	template <>
	inline reg add<int32_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svadd_s32_z(svptrue_b32(),svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2)));
	}

	template <>
	inline reg mask<int32_t,add<int32_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svadd_s32_m(m,svreinterpret_s32_f32(blend<int32_t>(v1,src,m)),svreinterpret_s32_f32(v2)));
	}

	template <>
	inline Reg<int32_t> mask<int32_t,add<int32_t>>(const Msk<nElReg<int32_t>()> m, const Reg<int32_t> src, const Reg<int32_t> v1, const Reg<int32_t> v2) {
		return mask<int32_t,add<int32_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int32_t,add<int32_t>>(const msk m, const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svadd_s32_z(m,svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2)));
	}

	template <>
	inline Reg<int32_t> maskz<int32_t,add<int32_t>>(const Msk<nElReg<int32_t>()> m, const Reg<int32_t> v1, const Reg<int32_t> v2) {
		return maskz<int32_t,add<int32_t>>(m.m, v1.r, v2.r);
	}

	// ------------------------------------------------------------------------------------------------------------ sub
	// ------------------ float
	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return svsub_f32_z(svptrue_b32(),v1,v2);
	}

	template <>
	inline reg mask<float,sub<float>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svsub_f32_m(m,blend<float>(v1,src,m),v2);
	}

	template <>
	inline Reg<float> mask<float,sub<float>>(const Msk<nElReg<float>()> m, const Reg<float> src, const Reg<float> v1, const Reg<float> v2) {
		return mask<float,sub<float>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<float,sub<float>>(const msk m, const reg v1, const reg v2) {
		return svsub_f32_z(m,v1,v2);
	}

	template <>
	inline Reg<float> maskz<float,sub<float>>(const Msk<nElReg<float>()> m, const Reg<float> v1, const Reg<float> v2) {
		return maskz<float,sub<float>>(m.m, v1.r, v2.r);
	}

	// ------------------ double
	template <>
	inline reg sub<double>(const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svsub_f64_z(svptrue_b64(),svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline reg mask<double,sub<double>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svsub_f64_m(m,svreinterpret_f64_f32(blend<double>(v1,src,m)),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline Reg<double> mask<double,sub<double>>(const Msk<nElReg<double>()> m, const Reg<double> src, const Reg<double> v1, const Reg<double> v2) {
		return mask<double,sub<double>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<double,sub<double>>(const msk m, const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svsub_f64_z(m,svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline Reg<double> maskz<double,sub<double>>(const Msk<nElReg<double>()> m, const Reg<double> v1, const Reg<double> v2) {
		return maskz<double,sub<double>>(m.m, v1.r, v2.r);
	}

	// ------------------ int64_t
	template <>
	inline reg sub<int64_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svsub_s64_z(svptrue_b64(),svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline reg mask<int64_t,sub<int64_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svsub_s64_m(m,svreinterpret_s64_f32(blend<int64_t>(v1,src,m)),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline Reg<int64_t> mask<int64_t,sub<int64_t>>(const Msk<nElReg<int64_t>()> m, const Reg<int64_t> src, const Reg<int64_t> v1, const Reg<int64_t> v2) {
		return mask<int64_t,sub<int64_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int64_t,sub<int64_t>>(const msk m, const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svsub_s64_z(m,svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline Reg<int64_t> maskz<int64_t,sub<int64_t>>(const Msk<nElReg<int64_t>()> m, const Reg<int64_t> v1, const Reg<int64_t> v2) {
		return maskz<int64_t,sub<int64_t>>(m.m, v1.r, v2.r);
	}

	// ------------------ int32_t
	template <>
	inline reg sub<int32_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svsub_s32_z(svptrue_b32(),svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2)));
	}

	template <>
	inline reg mask<int32_t,sub<int32_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svsub_s32_m(m,svreinterpret_s32_f32(blend<int32_t>(v1,src,m)),svreinterpret_s32_f32(v2)));
	}

	template <>
	inline Reg<int32_t> mask<int32_t,sub<int32_t>>(const Msk<nElReg<int32_t>()> m, const Reg<int32_t> src, const Reg<int32_t> v1, const Reg<int32_t> v2) {
		return mask<int32_t,sub<int32_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int32_t,sub<int32_t>>(const msk m, const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svsub_s32_z(m,svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2)));
	}

	template <>
	inline Reg<int32_t> maskz<int32_t,sub<int32_t>>(const Msk<nElReg<int32_t>()> m, const Reg<int32_t> v1, const Reg<int32_t> v2) {
		return maskz<int32_t,sub<int32_t>>(m.m, v1.r, v2.r);
	}

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<double>(const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svmul_f64_z(svptrue_b64(),svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return svmul_f32_z(svptrue_b32(),v1,v2);
	}

	template <>
	inline reg mul<int64_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svmul_s64_z(svptrue_b64(),svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2)));
	}

	template <>
	inline reg mul<int32_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svmul_s32_z(svptrue_b32(),svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2)));
	}

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg div<double>(const reg v1, const reg v2) {
		return svreinterpret_f32_f64(svdiv_f64_z(svptrue_b64(),svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2)));
	}

	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return svdiv_f32_z(svptrue_b32(),v1,v2);
	}

	// ---------------------------------------------------------------------------------------------------------- fmadd
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return svmla_f32_m(svptrue_b32(), v3, v2, v1);
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return svreinterpret_f32_f64(svmla_f64_m(svptrue_b64(), svreinterpret_f64_f32(v3), svreinterpret_f64_f32(v2), svreinterpret_f64_f32(v1)));
	}

	// ----------------------------------------------------------------------------------------------------------- set0
	template <>
	inline reg set0<double>() {
		return svreinterpret_f32_f64(svdup_f64(0.0d));
	}

	template <>
	inline reg set0<float>() {
		return svdup_f32(0.0f);
	}

	template <>
	inline reg set0<int64_t>() {
		return svreinterpret_f32_s64(svdup_s64(0LL));
	}

	template <>
	inline reg set0<int32_t>() {
		return svreinterpret_f32_s32(svdup_s32(0));
	}

	// ----------------------------------------------------------------------------------------------------------- set1
	template <>
	inline reg set1<double>(const double val) {
		return svreinterpret_f32_f64(svdup_f64(val));
	}

	template <>
	inline reg set1<float>(const float val) {
		return svdup_f32(val);
	}

	template <>
	inline reg set1<int64_t>(const int64_t val) {
		return svreinterpret_f32_s64(svdup_s64(val));
	}

	template <>
	inline reg set1<int32_t>(const int32_t val) {
		return svreinterpret_f32_s32(svdup_s32(val));
	}

	// ------------------------------------------------------------------------------------------------------- getfirst

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	template <>
	inline msk cmpeq<double>(const reg v1, const reg v2) {
		return svcmpeq_f64(svptrue_b64(),svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2));
	}

	template <>
	inline msk cmpeq<float>(const reg v1, const reg v2) {
		return svcmpeq_f32(svptrue_b32(),v1,v2);
	}

	template <>
	inline msk cmpeq<int64_t>(const reg v1, const reg v2) {
		return svcmpeq_s64(svptrue_b64(),svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2));
	}

	template <>
	inline msk cmpeq<int32_t>(const reg v1, const reg v2) {
		return svcmpeq_s32(svptrue_b32(),svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2));
	}

	// --------------------------------------------------------------------------------------------------------- cmnpeq
	template <>
	inline msk cmpneq<double>(const reg v1, const reg v2) {
		return svcmpne_f64(svptrue_b64(),svreinterpret_f64_f32(v1),svreinterpret_f64_f32(v2));
	}

	template <>
	inline msk cmpneq<float>(const reg v1, const reg v2) {
		return svcmpne_f32(svptrue_b32(),v1,v2);
	}

	template <>
	inline msk cmpneq<int64_t>(const reg v1, const reg v2) {
		return svcmpne_s64(svptrue_b64(),svreinterpret_s64_f32(v1),svreinterpret_s64_f32(v2));
	}

	template <>
	inline msk cmpneq<int32_t>(const reg v1, const reg v2) {
		return svcmpne_s32(svptrue_b32(),svreinterpret_s32_f32(v1),svreinterpret_s32_f32(v2));
	}

	// ---------------------------------------------------------------------------------------------------- set1 (mask)
	template <>
	inline msk set1<nElReg<int64_t>()>(const bool val) {
		return svdup_b64(val);
	}

	template <>
	inline msk set1<nElReg<int32_t>()>(const bool val) {
		return svdup_b32(val);
	}

	template <>
	inline msk set1<nElReg<int16_t>()>(const bool val) {
		return svdup_b16(val);
	}

	template <>
	inline msk set1<nElReg<int8_t>()>(const bool val) {
		return svdup_b8(val);
	}

	// ---------------------------------------------------------------------------------------------------- set0 (mask)

	template <>
	inline msk set0<nElReg<int64_t>()>() {
		return svpfalse_b();
	}

	template <>
	inline msk set0<nElReg<int32_t>()>() {
		return svpfalse_b();
	}

	template <>
	inline msk set0<nElReg<int16_t>()>() {
		return svpfalse_b();
	}

	template <>
	inline msk set0<nElReg<int8_t>()>() {
		return svpfalse_b();
	}

	// ------------------------------------------------------------------------------------------------------------ set
	template <>
	inline reg set<double>(const double vals[nElReg<double>()]) {
		return load<double>(vals);
	}

	template <>
	inline reg set<float>(const float vals[nElReg<float>()]) {
		return load<float>(vals);
	}

	template <>
	inline reg set<int64_t>(const int64_t vals[nElReg<int64_t>()]) {
		return load<int64_t>(vals);
	}

	template <>
	inline reg set<int32_t>(const int32_t vals[nElReg<int32_t>()]) {
		return load<int32_t>(vals);
	}

	// ----------------------------------------------------------------------------------------------------- set (mask)
	template <>
	inline msk set<nElReg<int64_t>()>(const bool vals[nElReg<int64_t>()]) {
	#ifdef __ARM_FEATURE_SVE_PREDICATE_OPERATORS
		msk m = vals;
		return m;
	#else
		uint64_t v[nElReg<int64_t>()];
		for (int i = 0; i < nElReg<int64_t>(); i++)
			v[i] = vals[i] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0;
		auto r1 = set<int64_t>((int64_t*)v);
		auto r2 = set1<int64_t>((uint64_t)0xFFFFFFFFFFFFFFFF);

		return cmpeq<int64_t>(r1, r2);
	#endif
	}

	template <>
	inline msk set<nElReg<int32_t>()>(const bool vals[nElReg<int32_t>()]) {
		uint32_t v[nElReg<int32_t>()];
		for (int i = 0; i < nElReg<int32_t>(); i++)
			v[i] = vals[i] ? 0xFFFFFFFF : 0;
		auto r1 = set <int32_t>((int32_t*)v);
		auto r2 = set1<int32_t>(0xFFFFFFFF);

		return (msk) cmpeq<int32_t>(r1, r2);
	}

	// ---------------------------------------------------------------------------------------------------------- toreg
	template <>
	inline reg toreg<nElReg<int64_t>()>(const msk m) {
		auto one  = set1<int64_t>((uint64_t)0xFFFFFFFFFFFFFFFF);
		auto zero = set1<int64_t>(0);

		return blend<int64_t>(one, zero, m);
	}

	template <>
	inline reg toreg<nElReg<int32_t>()>(const msk m) {
		auto one  = set1<int32_t>(0xFFFFFFFF);
		auto zero = set1<int32_t>(0);

		return blend<int32_t>(one, zero, m);
	}

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<int64_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s64(svand_s64_z(svptrue_b64(), svreinterpret_s64_f32(v1), svreinterpret_s64_f32(v2)));
	}

	template <>
	inline reg andb<int32_t>(const reg v1, const reg v2) {
		return svreinterpret_f32_s32(svand_s32_z(svptrue_b32(), svreinterpret_s32_f32(v1), svreinterpret_s32_f32(v2)));
	}

	template <>
	inline reg andb<double>(const reg v1, const reg v2) {
		return andb<int64_t>(v1,v2);
	}

	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return andb<int>(v1,v2);
	}

	// ---------------------------------------------------------------------------------------------------- andb (mask)
	template <>
	inline msk andb<nElReg<int64_t>()>(const msk v1, const msk v2) {
		return svand_z(svptrue_b64(), v1, v2);
	}

	template <>
	inline msk andb<nElReg<int32_t>()>(const msk v1, const msk v2) {
		return svand_z(svptrue_b32(), v1, v2);
	}

	// ---------------------------------------------------------------------------------------------------- notb (mask)
	template <>
	inline msk notb<nElReg<int64_t>()>(const msk v) {
		return svnot_z(svptrue_b64(), v);
	}

	template <>
	inline msk notb<nElReg<int32_t>()>(const msk v) {
		return svnot_z(svptrue_b32(), v);
	}

	// --------------------------------------------------------------------------------------------------- testz (mask)
	template <>
	inline bool testz<nElReg<int64_t>()>(const msk v1) {
		return !svptest_any(svptrue_b64(), v1);
	}

	template <>
	inline bool testz<nElReg<int32_t>()>(const msk v1) {
		return !svptest_any(svptrue_b32(), v1);
	}

	// ------------------------------------------------------------------------------------------------------ reduction
	template <>
	struct _reduction<double, mipp::add<double>>
	{
		static double sapply(const reg v1) {
			return svaddv_f64(svptrue_b64(), svreinterpret_f64_f32(v1));
		}
	};

	template <>
	struct _reduction<float, mipp::add<float>>
	{
		static float sapply(const reg v1) {
			return svaddv_f32(svptrue_b32(), v1);
		}
	};

	template <>
	struct _Reduction<double, mipp::add<double>>
	{
		static double sapply(const Reg<double> v1) {
			return svaddv_f64(svptrue_b64(), svreinterpret_f64_f32(v1.r));
		}
	};

	template <>
	struct _Reduction<float, mipp::add<float>>
	{
		static float sapply(const Reg<float> v1) {
			return svaddv_f32(svptrue_b32(), v1.r);
		}
	};

	// -------------------------------------------------------------- reg_2 use
	template <>
	inline reg cvt<int32_t, int64_t>(const reg_2 v) {
		return svreinterpret_f32_s64(svunpklo_s64(v));
	}

	template <>
	inline reg_2 low<int32_t>(const reg v) {
		// clean it here reg_2 eq reg<int>
		return svreinterpret_s32_f32(v);
	}

#endif

