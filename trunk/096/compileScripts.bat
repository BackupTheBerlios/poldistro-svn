@ECHO OFF

@ECHO compile_all.bat by Austin
@ECHO -------------------------
@ECHO Compiling all scripts and writing results to ecompile.txt
@ECHO.

scripts\ecompile.exe -b -r >ecompile.txt

@ECHO.
@ECHO Compilation of all scripts finished 
@ECHO Check ecompile.txt for errors and output
@ECHO -------------------------

PAUSE