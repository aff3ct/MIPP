@echo on

set PATH=%PATH%;C:\Program Files\Git\cmd
set PATH=%PATH%;C:\Program Files\CMake\bin
set PATH=%PATH%;C:\Program Files\Git\mingw64\bin

set build_root=build_windows_x86_gcc
call :compile "%build_windows_x86_gcc%_nointr"   "-DMIPP_NO_INTRINSICS"
call :compile "%build_windows_x86_gcc%_sse2"     "-msse2"
call :compile "%build_windows_x86_gcc%_sse3"     "-msse3"
call :compile "%build_windows_x86_gcc%_ssse3"    "-mssse3"
call :compile "%build_windows_x86_gcc%_sse4_1"   "-msse4.1"
call :compile "%build_windows_x86_gcc%_sse4_2"   "-msse4.2"
call :compile "%build_windows_x86_gcc%_avx"      "-mavx"
call :compile "%build_windows_x86_gcc%_avx2"     "-mavx2"
call :compile "%build_windows_x86_gcc%_avx2_fma" "-mavx2 -mfma"
call :compile "%build_windows_x86_gcc%_avx512f"  "-mavx512f"

exit /B %ERRORLEVEL%

:compile
set build=%~1%
set params=%~2%
mkdir %build%
cd %build%
cmake .. -G"MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++.exe -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions %params%"
if %ERRORLEVEL% neq 0 exit /B %ERRORLEVEL%
mingw32-make
if %ERRORLEVEL% neq 0 exit /B %ERRORLEVEL%
cd ..
exit /B 0