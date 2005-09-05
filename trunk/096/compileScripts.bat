@echo off

@echo compile_all.bat by Austin
@echo -------------------------
@echo Compiling all scripts and writing results to ecompile.txt
scripts\ecompile.exe -b -r >ecompile.txt
@echo Compilation of all scripts finished 
@echo Check ecompile.txt for errors and output
@echo -------------------------

pause