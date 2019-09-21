# Cell Wars

## Dependencies
You need git installed and CMake installed.\
The Build scripts will download the needed git repositories.\
(The project needs [SFML](https://github.com/SFML/SFML) to run correctly.)

## Building on Mac
The Build.sh has all build options included.\
By running\
`sh Build.sh`\
the projects builds and runs directly after building.\
On the first run the script will clone the needed repositories.\
There are multiple command line arguments for the build script.\
`sh Build.sh -b`  or `sh Build.sh --build`      for building only.\
`sh Build.sh -r`  or `sh Build.sh --run`        for running only.\
`sh Build.sh -d`  or `sh Build.sh --debug`      for building in debug mode.\
`sh Build.sh -dr` or `sh Build.sh --debugrun`   for building in debug mode and running afterwards.

## Building on Windows
The Build.bat has all build options included.\
By running\
`Build.bat`\
the projects builds and runs directly after building.\
On the first run the script will clone the needed repositories.\
There are multiple command line arguments for the build script.\
`Build.bat -b`  or `Build.bat --build`      for building only.\
`Build.bat -r`  or `Build.bat --run`        for running only.\
`Build.bat -d`  or `Build.bat --debug`      for building in debug mode.\
`Build.bat -dr` or `Build.bat --debugrun`   for building in debug mode and running afterwards.
