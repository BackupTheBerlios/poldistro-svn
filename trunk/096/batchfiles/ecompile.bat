@ECHO OFF

REM -- If a special path is needed to ecompile.exe set it here
REM -- Path is considered to be run from the root if started by starthere.bat
SET ECOMPILE_PATH=scripts\ecompile.exe
REM ----------

GOTO :MENU()

REM -- MENU FUNCTION
:MENU()
CLS
ECHO Ecompile.bat by Austin
ECHO ========================
ECHO Command        Purpose
ECHO  [ a ] - Compile a specific script.
ECHO  [ b ] - Compile all .src scripts.
ECHO  [ c ] - Compile all scripts and output to POL\ecompile.log
ECHO.
ECHO  [ x ] - Quit

SET /p CMD=Command:

IF "%CMD%" == "a" GOTO :COMPILE_SCRIPT()
IF "%CMD%" == "b" GOTO :COMPILE_ALL_SCRIPTS()
IF "%CMD%" == "c" GOTO :COMPILE_ALL_SCRIPTS_OPTXT()
IF "%CMD%" == "x" GOTO :QUIT()

ECHO.
ECHO Invalid command.
GOTO :RETURN_TO_MENU()

REM -- RETURN_TO_MENU() FUNCTION
:RETURN_TO_MENU()
PAUSE
GOTO :MENU()

REM -- COMPILE_SCRIPT() FUNCTION
:COMPILE_SCRIPT()
SET /p CMD="Path to script to compile:"
%ECOMPILE_PATH% %CMD%
GOTO RETURN_TO_MENU()

REM -- COMPILE_ALL_SCRIPTS() FUNCTION
:COMPILE_ALL_SCRIPTS()
%ECOMPILE_PATH% -b -r
GOTO RETURN_TO_MENU()

REM -- COMPILE_ALL_SCRIPTS_OPTXT() FUNCTION
:COMPILE_ALL_SCRIPTS_OPTXT()
%ECOMPILE_PATH% -b -r >ecompile.log
GOTO RETURN_TO_MENU()

REM -- QUIT FUNCTION
:QUIT()
