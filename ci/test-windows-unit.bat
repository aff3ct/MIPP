@echo on

cd tests
:Loop
IF "%~1"=="" goto End

   set build=%~1%
   cd %build%/bin/
   run_tests.exe
   if %ERRORLEVEL% neq 0 exit /B %ERRORLEVEL%
   cd ../../

shift
goto Loop

:End