@if "%1" == "make" GOTO MAKE
@if "%1" == "clean" GOTO CLEAN
@GOTO END

:MAKE
@cd premake5
@premake5.exe --file=../premake5.lua gmake2
@cd ../
@mingw32-make
@GOTO END

:CLEAN
@mingw32-make clean
@rmdir /s /q bin
@rmdir /s /q obj
@del /q *.make Makefile

:END