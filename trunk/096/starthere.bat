@ECHO OFF

REM -- If a special path is needed to the batch files set it here
SET BATCH_PATH=batchfiles\
REM ----------

GOTO :MENU()

REM -- MENU FUNCTION
:MENU()
CLS
ECHO StartHere.bat by Austin
ECHO ========================
ECHO Command        Purpose
ECHO  [ a ] - RealmGen menu        (Realm building tools)
ECHO  [ b ] - Ecompiler menu       (Ecompile tools)
ECHO  [ c ] - Cleanup menu         (File removal tools)
ECHO.
ECHO  [ d ] - Start POL.exe        (Returns to menu on exit)
ECHO  [ e ] - Keep POL.exe running (Restarts when it exits use CTRL+C to stop)
ECHO.
ECHO  [ x ] - Quit

SET /p CMD=Command:

IF "%CMD%" == "a" GOTO :REALM_GEN()
IF "%CMD%" == "b" GOTO :ECOMPILE()
IF "%CMD%" == "c" GOTO :CLEANUP()
IF "%CMD%" == "d" GOTO :POL()
IF "%CMD%" == "e" GOTO :POL_LOOP()
IF "%CMD%" == "x" GOTO :QUIT()

ECHO.
ECHO Invalid command.
GOTO :RETURN_TO_MENU()

REM -- RETURN_TO_MENU() FUNCTION
:RETURN_TO_MENU()
GOTO :MENU()

REM -- REALM_GEN() FUNCTION
:REALM_GEN()
CALL %BATCH_PATH%realmgen.bat
GOTO RETURN_TO_MENU()

REM -- ECOMPILE() FUNCTION
:ECOMPILE()
CALL %BATCH_PATH%ecompile.bat
GOTO :RETURN_TO_MENU()

REM -- CLEANUP() FUNCTION
:CLEANUP()
CALL %BATCH_PATH%cleanup.bat
GOTO :RETURN_TO_MENU()

REM -- POL() FUNCTION
:POL()
CALL %BATCH_PATH%pol.bat
GOTO :RETURN_TO_MENU()

REM -- ECOMPILE() FUNCTION
:POL_LOOP()
CALL %BATCH_PATH%loopPOL.bat
GOTO :RETURN_TO_MENU()

REM -- QUIT FUNCTION
:QUIT()