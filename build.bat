@if "%1" == "make" GOTO MAKE
@if "%1" == "clean" GOTO CLEAN
@GOTO END

:MAKE
@cd premake5
@premake5.exe --file=../premake5.lua gmake2
@cd ../
@if "%2" == "Win64" GOTO WIN64
@if "%2" == "Linux" GOTO LINUX
@if "%2" == "All" GOTO ALL
@if "%2" == "" GOTO END else GOTO END

:WIN64
@if "%3" == "Debug" GOTO WIN64_DEBUG
@if "%3" == "Release" GOTO WIN64_RELEASE
@if "%3" == "" GOTO END else GOTO END

:WIN64_DEBUG
@mingw32-make config=debug_win64
@GOTO END

:WIN64_RELEASE
@mingw32-make config=release_win64
@GOTO END

:LINUX
@if "%3" == "Debug" GOTO LINUX_DEBUG
@if "%3" == "Release" GOTO LINUX_RELEASE
@if "%3" == "" GOTO END else GOTO END

:LINUX_DEBUG
@wsl make config=debug_linux
@GOTO END

:LINUX_RELEASE
@wsl make config=release_linux
@GOTO END

:ALL
@if "%3" == "Debug" GOTO ALL_DEBUG
@if "%3" == "Release" GOTO ALL_RELEASE
@if "%3" == "" GOTO END else GOTO END

:ALL_DEBUG
@mingw32-make config=debug_win64
@wsl make config=debug_linux
@GOTO END

:ALL_RELEASE
@mingw32-make config=release_win64
@wsl make config=release_linux
@GOTO END

:CLEAN
@mingw32-make clean
@rmdir /s /q bin
@rmdir /s /q obj
@del /q *.make Makefile
@GOTO END

:END