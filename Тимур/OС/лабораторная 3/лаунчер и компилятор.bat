@echo off
g++ creator.cpp -o creator
cls
g++ child_process.cpp -o child_process
cls
creator.exe
choice /C YN /D Y /T 3600 > nul
