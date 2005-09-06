@ECHO OFF

GOTO :MENU()

REM -- MENU FUNCTION
:MENU()
CLS
ECHO CleanUp.bat by Austin
ECHO ========================
ECHO Command        Purpose
ECHO  [ a ] - Remove *.ecl files. (Will need to recompile scripts)
ECHO  [ b ] - Remove *.bak files
ECHO  [ c ] - Remove *.dep files
ECHO  [ d ] - Remove *.log files
ECHO  [ e ] - Remove *.lst files
ECHO  [ f ] - Remove *.dbg files
ECHO  [ g ] - Remove *.dbg.txt
ECHO  [ h ] - Remove other (disabled)
ECHO.
ECHO  [ x ] - Quit

SET /p CMD=Command:

SET REMOVE_TYPE=
IF "%CMD%" == "a" SET REMOVE_TYPE=*.ecl
IF "%CMD%" == "b" SET REMOVE_TYPE=*.bak
IF "%CMD%" == "c" SET REMOVE_TYPE=*.dep
IF "%CMD%" == "d" SET REMOVE_TYPE=*.log
IF "%CMD%" == "e" SET REMOVE_TYPE=*.lst
IF "%CMD%" == "f" SET REMOVE_TYPE=*.dbg
IF "%CMD%" == "g" SET REMOVE_TYPE=*.dbg.txt
IF "%CMD%" == "x" GOTO :QUIT()

IF NOT "%REMOVE_TYPE%"=="" GOTO REMOVE()

ECHO.
ECHO Invalid command.
GOTO :RETURN_TO_MENU()

REM -- RETURN_TO_MENU() FUNCTION
:RETURN_TO_MENU()
PAUSE
GOTO :MENU()

REM -- REMOVE FUNCTION()
:REMOVE()
DEL /S %REMOVE_TYPE%
GOTO RETURN_TO_MENU()

REM -- QUIT() FUNCTION
:QUIT()