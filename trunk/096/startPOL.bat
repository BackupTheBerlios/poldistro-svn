@echo OFF

rem - ======================================================
rem - startPOL by Austin
rem -
rem - To set POL to immediately start back up after stopping
rem - set ENABLE_PAUSE to 0
rem - ======================================================

set ENABLE_PAUSE=1
set RESULT=0

goto :start

:start
CLS
@ECHO ==========
@ECHO Starting pol.exe
@ECHO ==========

rem - To Do: Capture POL output to RESULT
rem - Do an IF NOT "%RESULT%"=="1" GOTO :end

pol.exe

@ECHO.
@ECHO.
@ECHO ==========
@ECHO POL has stopped!
@ECHO Removing log\script.log
@ECHO ==========
@ECHO.
@ECHO.

del log\script.log

IF "%ENABLE_PAUSE%"=="1" pause

goto :start

:end
pause
