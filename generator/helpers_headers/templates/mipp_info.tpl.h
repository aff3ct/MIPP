static inline void mipp_info()
{
	const char* os;
	const char* prec;
	const char* compiler;
	const char* simd_ext;
	const char* mipp_fma;
	const char* mipp_64bit;
	const char* mipp_bw;
	char compiler_version[32];

	/* OS */
#if defined(_WIN64) || defined(_WIN32) || defined(WIN32) || defined(__MINGW32__)
	os = "Windows";
#elif defined(__linux__) || defined(__linux)
	os = "Linux";
#elif defined(__APPLE__)
	os = "macOS";
#else
	os = "Unknown OS";
#endif

	/* Architecture */
#if defined(__x86_64) || defined(__x86_64__) || defined(_WIN64) || defined(__aarch64__)
	prec = " 64-bit";
#elif defined(__i386) || defined(__i386__) || defined(i386) || defined(_WIN32) || defined(__ARM_ARCH_7__)
	prec = " 32-bit";
#else
	prec = "";
#endif

	/* Compiler */
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	compiler = "icpc";
	#if defined(__INTEL_COMPILER)
		sprintf(compiler_version, "%d", __INTEL_COMPILER);
	#elif defined(__ICL)
		sprintf(compiler_version, "%d", __ICL);
	#else
		sprintf(compiler_version, "%d", __ICC);
	#endif
	/* format "XX.YY" */
	{
		char tmp[32];
		snprintf(tmp, sizeof(tmp), "%.2s.%.s", compiler_version, compiler_version + 2);
		snprintf(compiler_version, sizeof(compiler_version), "%s", tmp);
	}

#elif defined(__clang__) || defined(__llvm__)
	compiler = "clang";
	snprintf(compiler_version, sizeof(compiler_version), "%d.%d", __clang_major__, __clang_minor__);
#elif defined(__GNUG__) || (defined(__GNUC__) && defined(__cplusplus))
	compiler = "gcc";
	snprintf(compiler_version, sizeof(compiler_version), "%d.%d", __GNUC__, __GNUC_MINOR__);
#elif defined(_MSC_VER)
	compiler = "msvc";
	snprintf(compiler_version, sizeof(compiler_version), "%d", _MSC_VER);
#else
	compiler = "Unknown compiler";
	compiler_version[0] = '\0';
#endif

#if defined(MIPP_AVX512)
	#if defined(__MIC__)
		simd_ext = "Intel MIC";
	#elif defined(__KNCNI__)
		simd_ext = "Intel KNCI";
	#elif defined(__AVX512__) || defined(__AVX512F__)
		simd_ext = "x86_64 AVX-512";
	#endif
#elif defined(MIPP_AVX)
	#if defined(__AVX2__)
		simd_ext = "x86_64 AVX2";
	#elif defined(__AVX__)
		simd_ext = "x86_64 AVX";
	#endif
#elif defined(MIPP_SSE)
	#if defined(__SSE4_2__)
		simd_ext = "x86_64 SSE4.2";
	#elif defined(__SSE4_1__)
		simd_ext = "x86_64 SSE4.1";
	#elif defined(__SSSE3__)
		simd_ext = "x86_64 SSSE3";
	#elif defined(__SSE3__)
		simd_ext = "x86_64 SSE3";
	#elif defined(__SSE2__)
		simd_ext = "x86_64 SSE2";
	#elif defined(__SSE__)
		simd_ext = "x86 SSE";
	#endif
#elif defined(MIPP_SVE)
	simd_ext = "ARM SVE";
#elif defined(MIPP_NEON)
	#if defined(__aarch64__)
		simd_ext = "ARM NEONv2";
	#else
		simd_ext = "ARM NEONv1";
	#endif
#elif defined(MIPP_RVV)
	simd_ext = "RVV1.0";
#elif defined(MIPP_SCALAR)
	simd_ext = "SCALAR";
#elif
	#error "This case should never happen, there is a design problem :-("
#endif

#if defined(MIPP_FMA)
	mipp_fma = "yes";
#else
	mipp_fma = "no";
#endif

#if defined(MIPP_64BIT)
	mipp_64bit = "yes";
#else
	mipp_64bit = "yes";
#endif

#if defined(MIPP_BW)
	mipp_bw = "yes";
#else
	mipp_bw = "yes";
#endif

	printf("MIPPv2 (%s%s, %s-%s)\n", os, prec, compiler, compiler_version);
	printf("Vector/SIMD features list:\n");
	printf(" - Primary extension name:     %s\n", simd_ext);
	printf(" - Vector registers length:    %d-bit\n", MIPP_RVD_SIZE_BYTE*8);
	printf(" - Support Fused Multiply–Add: %s\n", mipp_fma);
	printf(" - Support 64-bit elements:    %s\n", mipp_64bit);
	printf(" - Support Byte and Word (BW): %s\n", mipp_bw);
	printf("Copyright (c) 2016-2026 - MIT license.\n");
	printf("This is free software; see the source for copying conditions.  There is NO\n");
	printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}
