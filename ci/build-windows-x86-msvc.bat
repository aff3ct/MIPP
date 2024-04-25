@echo on

call ./ci/tools/threads.bat

set "VSCMD_START_DIR=%CD%"
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"

rem set build_root=build_windows_x86_msvc
call :compile "build_windows_x86_msvc_nointr"   "-DMIPP_NO_INTRINSICS"
call :compile "build_windows_x86_msvc_sse2"     "/arch:SSE2   -D__SSE__ -D__SSE2__"
call :compile "build_windows_x86_msvc_sse3"     "/arch:SSE3   -D__SSE__ -D__SSE2__ -D__SSE3__"
call :compile "build_windows_x86_msvc_ssse3"    "/arch:SSSE3  -D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__"
call :compile "build_windows_x86_msvc_sse4_1"   "/arch:SSE4.1 -D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__ -D__SSE4_1__"
call :compile "build_windows_x86_msvc_sse4_2"   "/arch:SSE4.2 -D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__ -D__SSE4_1__ -D__SSE4_2__"
call :compile "build_windows_x86_msvc_avx"      "/arch:AVX    -D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__ -D__SSE4_1__ -D__SSE4_2__ -D__AVX__"
call :compile "build_windows_x86_msvc_avx2"     "/arch:AVX2   -D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__ -D__SSE4_1__ -D__SSE4_2__ -D__AVX__ -D__AVX2__"
call :compile "build_windows_x86_msvc_avx2_fma" "/arch:AVX2   -D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__ -D__SSE4_1__ -D__SSE4_2__ -D__AVX__ -D__AVX2__ -D__FMA__"
rem call :compile "build_windows_x86_msvc_avx512f"  "/arch:AVX512"

exit /B %ERRORLEVEL%

:compile
set build=%~1%
set params=%~2%
mkdir %build%
cd %build%
cmake .. -G"Visual Studio 15 2017 Win64" -DCMAKE_CXX_FLAGS="-D_CRT_SECURE_NO_DEPRECATE /EHsc /MP%THREADS% %params%" -DMIPP_STATIC_LIB=OFF
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
rem devenv /build Release MIPP_tests.sln
msbuild MIPP_tests.sln /t:Build /p:Configuration=Release
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
move bin\Release\* bin\
rmdir bin\Release\
cd ..
exit /B 0