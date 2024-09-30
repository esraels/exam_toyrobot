@echo off

pushd "%~pd0"

set PROJ_PATH=..\..\
set APP_PATH=ExamToyRobot\x64\Debug
set APP_NAME=ExamToyRobot.exe

set "APP=%PROJ_PATH%\%APP_PATH%\%APP_NAME%"

rem "%APP%" < commands_fileA.txt
rem more commands_fileB.txt | %APP% 
rem type commands_fileB.txt | %APP%


rem "%APP%" < commands_fileD.txt

rem %APP%  --verbose
rem %APP%

rem "%APP%" --verbose < commands_fileD.txt > output.log 2>$1

rem "%APP%" --verbose < commands_fileD.txt


more commands_fileC.txt | %APP% --verbose 1> output_fileC.log 2>&1

::working correctly
rem more commands_fileE.txt | %APP% --verbose 2> error.log
rem more commands_fileC.txt | %APP% --verbose 2> error.log 1> output.log

rem pause>nul


popd

goto:eof