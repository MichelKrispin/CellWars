@echo off

rem Check first for non existent folder
if not exist .\build\ mkdir build
if not exist .\SFML\ goto CLONESFMLREPOSITORY
if not exist .\pybind11\ goto CLONEPYBINDREPOSITORY

:BUILD
    WHERE python>nul
    IF %ERRORLEVEL% NEQ 0 ECHO ERROR: Python has to be installed to build python (If you have python3 as a command please edit this file)
    python setup.py install
    goto :eof

:CLONESFMLREPOSITORY
    echo Downloading dependencies...
    git clone https://github.com/SFML/SFML.git
    if not exist .\pybind11\ goto CLONEPYBINDREPOSITORY
    goto BUILD
    

:CLONEPYBINDREPOSITORY
    echo Downloading dependencies...
    git clone https://github.com/pybind/pybind11.git
    goto BUILD