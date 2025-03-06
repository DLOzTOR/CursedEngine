@echo off
rmdir /s /q out\build
echo Building project...

cmake -G "MinGW Makefiles" -S . -B out -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed.
    pause
    exit /b %ERRORLEVEL%
)

mingw32-make -C out
if %ERRORLEVEL% NEQ 0 (
    echo Build failed.
    pause
    exit /b %ERRORLEVEL%
)

echo Build completed.
pause