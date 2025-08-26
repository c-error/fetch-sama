@echo off

cd /d %~dp0
@REM :LOOP
echo.
echo Starting Build ...
echo.

echo BUILDING: icon ...
windres icon.rc -o icon.o

echo BUILDING: fetch.exe ...
gcc -O3 -march=native -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -s fetch.c icon.o -o fetch.exe

echo.
echo Cleaning ...
del /q icon.o

echo.
echo Task Completed (Press any key to exit) ...
pause >nul 2>&1
exit

@REM goto LOOP









