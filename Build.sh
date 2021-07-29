#!/bin/sh

PROGRAM_NAME=./CellWars

# First check whether the dependency folder exists
if [ ! -d "./SFML/" ]; then
    echo Downloading dependency - SFML
    git clone https://github.com/SFML/SFML.git
fi

# Then check whether the build folders exists
if [ ! -d "./cmake-build-debug/" ]; then
    mkdir cmake-build-debug
fi
if [ ! -d "./cmake-build-release/" ]; then
    mkdir cmake-build-release
fi

# Then building or running according to flags
if [ $# -eq 0 ]
then
    cd cmake-build-debug
    echo "Default building and running the project..."
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    cd ../bin/
    $PROGRAM_NAME
    cd ..
    exit 1

elif [ "$1" = "-r" ] || [ "$1" = "--run" ] ;
then
    cd cmake-build-release
    echo "Running the project..."
    cd ../bin/
    $PROGRAM_NAME
    cd ..
    exit 1

elif [ "$1" = "-d" ] || [ "$1" = "--debug" ] ;
then
    cd cmake-build-debug
    echo "Debug building..."
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    cd ..
    exit 1

elif [ "$1" = "-dr" ] || [ "$1" = "--debugrun" ] ;
then
    cd cmake-build-debug
    echo "Debug building and running..."
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    cd ../bin/
    $PROGRAM_NAME
    cd ..
    exit 1

elif [ "$1" = "-b" ] || [ "$1" = "--build" ] ;
then
    cd cmake-build-release
    echo "Default building..."
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    cd ..
    exit 1

elif [ "$1" = "-p" ] || [ "$1" = "--python" ] ;
then
    echo "Creating the Python binding..."
    if [ ! -d "./pybind11/" ]; then
        echo Downloading dependency - pybind11
        git clone https://github.com/pybind/pybind11.git
    fi
    python3 setup.py install
    if [ "$?" = "1" ]; then
        echo "Could not run the python command"
        echo "Please execute it yourself by running"
        echo "sudo python3 setup.py install"
        echo "or by activating a virtual environment and rerunning this script"
    fi
    exit 1
    
elif [ "$1" = "-h" ] || [ "$1" = "--help" ] ;
then
    echo "If no options are given then the script builds using the default config and runs the project.\n"
    echo "Options:"
    echo "\t-r  --run\t= Runs the executable without rebuilding."
    echo "\t-d  --debug\t= Builds with debug configuration without running the executable."
    echo "\t-dr --debugrun\t= Builds with debug configuration and runs the executable."
    echo "\t-b  --build\t= Build the project with default configuration without running the executable."
    exit 1

else
    echo "$0:$1: invalid option"
    echo "Use -h or --help to display all options"
fi
