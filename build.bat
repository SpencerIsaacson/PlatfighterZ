@tcc -shared SourceCode/SGL.c -luser32
@REM "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\Roslyn\csc.exe" -out:P:\Game.exe -recurse:P:\SourceCode\*.cs -debug -optimize+ -langversion:7.3 -define:Windows -define:DEBUG -nologo -unsafe -platform:x64 -win32icon:Assets\icon.ico

@if not errorlevel 1 (
	if not "%~1"=="" (
		if "%~1"=="-r" Game.exe
	)
)