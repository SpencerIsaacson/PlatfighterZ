@echo off
subst P: C:\Users\PesdiDev\Documents\PlatfighterZ
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path=P:\shell;%path%
P:
cls