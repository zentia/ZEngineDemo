@echo off
REM ZEngine Generate Script for Windows
REM This script generates the project files using CMake presets

echo.
echo ========================================
echo ZEngine Project Generation
echo ========================================
echo.
echo [TIP] For faster builds, use: build_windows.bat --jobs N
echo       (where N is the number of CPU cores, default: auto-detected)
echo.

REM Check if Python is available (for unified tool)
python --version >nul 2>&1
if errorlevel 1 (
    echo [WARNING] Python not found, using CMake directly
    cmake --preset "windows_visual_studio"
) else (
    echo [INFO] Using unified build tool...
    python zbuild.py configure --preset windows_visual_studio
)

if errorlevel 1 (
    echo [ERROR] Generation failed
    pause
    exit /b 1
)

echo.
echo [SUCCESS] Project files generated successfully!
echo.
pause