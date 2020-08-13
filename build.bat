@/compiler/tcc SourceCode/Game.c -luser32 /Dependencies/SDL2.dll

@if not errorlevel 1 (
	if not "%~1"=="" (
		if "%~1"=="-r" Game.exe
	)
)