@echo off
mkdir DebugBuild > nul
csc -out:DebugBuild/Game.exe /unsafe Game.cs
cd DebugBuild
Game
cd ..