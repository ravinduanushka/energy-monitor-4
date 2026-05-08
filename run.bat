@echo off
title Smart Energy Usage Monitor - Launcher
:menu
cls
echo ==================================================
echo         SMART ENERGY USAGE MONITOR
echo ==================================================
echo.
echo  1. Run C++ Console Application (The Engine)
echo  2. Open HTML Dashboard (The UI)
echo  3. Exit
echo.
echo ==================================================
set /p choice="Enter your choice (1-3): "

if "%choice%"=="1" goto run_cpp
if "%choice%"=="2" goto open_html
if "%choice%"=="3" goto exit
echo Invalid choice, try again.
pause
goto menu

:run_cpp
echo Starting C++ Application...
start monitor.exe
goto menu

:open_html
echo Opening HTML Dashboard...
start dashboard.html
goto menu

:exit
echo Goodbye!
exit
