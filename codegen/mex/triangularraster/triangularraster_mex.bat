@echo off
call setEnv.bat
"D:\matlab\toolbox\shared\coder\ninja\win64\ninja.exe" -t compdb cc cxx cudac > compile_commands.json
"D:\matlab\toolbox\shared\coder\ninja\win64\ninja.exe" -v %*
