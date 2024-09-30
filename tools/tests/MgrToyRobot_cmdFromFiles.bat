@echo off

pushd "%~pd0"

set PROJ_PATH=..\..\
set APP_PATH=ExamToyRobot\x64\Debug
set APP_NAME=ExamToyRobot.exe

set "APP=%PROJ_PATH%\%APP_PATH%\%APP_NAME%"

"%APP%" < commands_fileA.txt
more commands_fileB.txt | %APP% 
type commands_fileC.txt | %APP%

type commands_fileC.txt | %APP% --verbose 2> errors_fileC.log

rem "%APP%" --verbose < commands_fileB.txt > output.log 2>&1
rem "%APP%" --verbose < commands_fileC.txt

rem more commands_fileE.txt | %APP% --verbose 2> error.log
rem more commands_fileC.txt | %APP% --verbose 2> error.log 1> output.log
rem more commands_fileC.txt | %APP% --verbose 1> output_fileC.log 2>&1

rem pause>nul

popd
goto:eof
