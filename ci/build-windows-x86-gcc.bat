@echo on

call ./ci/tools/threads.bat

rem set build_root=build_windows_x86_gcc
call :compile "build_windows_x86_gcc_nointr"   "-Wno-attributes -DMIPP_NO_INTRINSICS"
call :compile "build_windows_x86_gcc_sse2"     "-Wno-attributes -msse2"
call :compile "build_windows_x86_gcc_sse3"     "-Wno-attributes -msse3"
call :compile "build_windows_x86_gcc_ssse3"    "-Wno-attributes -mssse3"
call :compile "build_windows_x86_gcc_sse4_1"   "-Wno-attributes -msse4.1"
call :compile "build_windows_x86_gcc_sse4_2"   "-Wno-attributes -msse4.2"
call :compile "build_windows_x86_gcc_avx"      "-Wno-attributes -mavx"
call :compile "build_windows_x86_gcc_avx2"     "-Wno-attributes -mavx2"
call :compile "build_windows_x86_gcc_avx2_fma" "-Wno-attributes -mavx2 -mfma"
rem call :compile "build_windows_x86_gcc_avx512f"  "-mavx512f"

exit /B %ERRORLEVEL%

:compile
set build=%~1%
set params=%~2%
mkdir %build%
cd %build%
cmake .. -G"MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++.exe -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions %params%" -DMIPP_STATIC_LIB=OFF
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
mingw32-make -j %THREADS%
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
cd ..
exit /B 0