@echo off

if not "%~1"=="" (
	if "%~1"=="quick" (
		"compiler/tcc" -I"Dependencies\SDL_Headers" SourceCode/Game.c -luser32 Dependencies/SDL2.dll -bench 
	)			
	if "%~1"=="debug" (
		cl -Zi SourceCode/Game.c /I"Dependencies\SDL_Headers" /link /LIBPATH:"D:\Downloads\SDL2-devel-2.0.12-VC\SDL2-2.0.12\lib\x64" user32.lib SDL2.lib
	)		
	if "%~1"=="release" (
		cl -O2 -fp:fast SourceCode/Game.c /I"Dependencies\SDL_Headers" /link /LIBPATH:"D:\Downloads\SDL2-devel-2.0.12-VC\SDL2-2.0.12\lib\x64" user32.lib SDL2.lib
	)
) else (
	"compiler/tcc" -I"Dependencies\SDL_Headers" SourceCode/Game.c -luser32 Dependencies/SDL2.dll -bench 
)

if not errorlevel 1 (
	if not "%~2"=="" (
		if "%~2"=="-r" Game.exe
	) else if not "%~1"=="" (
		if "%~1"=="-r" Game.exe
	)	
)