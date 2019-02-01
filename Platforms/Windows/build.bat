@echo off
set path=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\Roslyn;%path%
csc -out:P:\Build\Game.exe -recurse:P:\SourceCode\*.cs -langversion:7 -define:Windows -nologo -unsafe -debug