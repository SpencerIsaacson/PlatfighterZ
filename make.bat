rem own the libs
set LIBS=kernel32.lib user32.lib SDL2static.lib SDL2main.lib shell32.lib winmm.lib imm32.lib version.lib setupapi.lib advapi32.lib gdi32.lib ole32.lib oleaut32.lib
cl /nologo SourceCode/Client.c /link /NOLOGO /INCREMENTAL:NO /SUBSYSTEM:CONSOLE %LIBS%