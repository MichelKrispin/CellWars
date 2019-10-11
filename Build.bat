@echo off

REM Check first whether the SFML directory exists and if not clone the directory
if not exist .\SFML\ goto CLONESFMLREPOSITORY

REM Then check whether the bin and build directories exist
if not exist .\bin\ mkdir bin
if not exist .\cmake-build-debug\ mkdir cmake-build-debug
if not exist .\cmake-build-release\ mkdir cmake-build-release

if "%1" == "" (
	goto DEFBUILDRUN
) else if "%1" == "-b" (
	goto DEFBUILD
) else if "%1" == "--build" (
	goto DEFBUILD
) else if "%1" == "-r" (
    cd cmake-build-release
	goto RUN
) else if "%1" == "--run" (
    cd cmake-build-release
	goto RUN
) else if "%1" == "-d" (
	goto DEBBUILD
) else if "%1" == "--debug" (
	goto DEBBUILD
) else if "%1" == "-dr" (
	goto DEBBUILDRUN
) else if "%1" == "--debugrun" (
	goto DEBBUILDRUN
) else if "%1" == "-h" (
    goto PRINTHELP
) else (
	echo Unknown arguments: %1
    goto PRINTHELP
)

:CLONESFMLREPOSITORY
    echo Downloading dependencies...
    git clone https://github.com/SFML/SFML.git
    echo Trying to build in the default way
    goto DEFBUILD

:DEFBUILD
    cd cmake-build-release
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release 
    cmake --build .
	goto END

:DEBBUILD
    cd cmake-build-release
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release 
    cmake --build .
    goto END

:DEBBUILDRUN
    cd cmake-build-debug
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug 
    cmake --build .
    goto RUN

:DEFBUILDRUN
    cd cmake-build-debug
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug 
    cmake --build .
    goto RUN

:RUN
    cd ..\bin
    CellWars.exe
    cd ..
	goto :eof

:END
    cd ..
    goto :eof

:PRINTHELP
    echo Possible arguments:
    echo 	-b  --build    - Default building
    echo 	-r  --run      - Runs the executable without rebuilding
    echo 	-d  --debug    - Builds with debug configuration without running the executable
    echo 	-dr --debugrun - Builds with debug configuration and runs the executable
    echo 	-b  --build    - Build the project with default configuration without running the executable
