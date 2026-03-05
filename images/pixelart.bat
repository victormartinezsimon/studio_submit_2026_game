@echo off
REM ================================
REM Pixel Art Batch + Paleta Global
REM ImageMagick (Windows)
REM ================================

REM --- CONFIGURACION ---
set INPUT_DIR=input
set OUTPUT_DIR=output

REM Resolucion "pixel"
set PIXEL_W=64
set PIXEL_H=64

REM Resolucion final (escalada)
set FINAL_W=512
set FINAL_H=512

REM Numero de colores
set COLORS=16

REM --------------------

echo.
echo ================================
echo Generando paleta global (%COLORS% colores)
echo ================================

REM Crear paleta global a partir de TODAS las imagenes
magick %INPUT_DIR%\*.png ^
  -filter point -resize %PIXEL_W%x%PIXEL_H%! ^
  -append +dither -colors %COLORS% -unique-colors ^
  palette.png

IF ERRORLEVEL 1 (
  echo ERROR al generar la paleta.
  pause
  exit /b
)

echo Paleta creada: palette.png
echo.

REM Crear carpeta de salida si no existe
if not exist %OUTPUT_DIR% (
  mkdir %OUTPUT_DIR%
)

echo ================================
echo Convirtiendo imagenes a pixel art
echo ================================

for %%F in (%INPUT_DIR%\*.png) do (
  echo Procesando %%~nxF
  magick "%%F" ^
    -filter point -resize %PIXEL_W%x%PIXEL_H%! ^
    -filter point -resize %FINAL_W%x%FINAL_H%! ^
    -dither none -remap palette.png ^
    "%OUTPUT_DIR%\%%~nxF"
)

echo.
echo ================================
echo Proceso terminado
echo Resultados en: %OUTPUT_DIR%
echo ================================
pause