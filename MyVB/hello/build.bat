@echo off 
@echo Building the BILLY Project
"d:\Program Files\Microsoft Visual Studio\VB98\vb6.exe" /make Project1.vbp
ren Project1.exe billy.exe
@echo Stamping the EXE
"d:\Program Files\Armadillo\Armadillo.exe" billy.arm /p
@echo YAY!!!
