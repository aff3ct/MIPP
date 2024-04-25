@echo on

:Loop
IF "%~1"=="" goto End

   set build=%~1%
   cd %build%/bin/tests/
   run_tests.exe
   if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
   cd ../../

shift
goto Loop

:End