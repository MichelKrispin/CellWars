cmake_minimum_required (VERSION 3.14)
project (CellWars)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# The option to build the python library or the C++ executable
# Will only be activated when using the BuildPython script 
# (which invokes the setup.py where it is used in the Cmake call)
option(BUILD_PYTHON_LIBRARY "Build this project as a python library" OFF)

# Set the output directory of the exe inside a dedicated bin folder
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

# SFML Library build statically
set(BUILD_SHARED_LIBS false)
add_subdirectory(SFML)
include_directories(${SFML_SOURCE_DIR}/include)
# -----------

# Default source dir as include directory
set(SOURCE_DIR src/)
include_directories(${SOURCE_DIR})

# Bots
set(BOT_SRC ${SOURCE_DIR}/Bot/Bot.cpp
            ${SOURCE_DIR}/Bot/PlayerBot.cpp
            ${SOURCE_DIR}/Bot/Utilities.cpp)
# Renderer
set(RENDERER_SRC ${SOURCE_DIR}/Renderer/SFMLWindow.cpp
                 ${SOURCE_DIR}/Renderer/Button.cpp
                 ${SOURCE_DIR}/Renderer/Window.cpp)

# World
set(WORLD_SRC ${SOURCE_DIR}/World/ConfigurationLoader.cpp
              ${SOURCE_DIR}/World/Field.cpp
              ${SOURCE_DIR}/World/FieldList.cpp
              ${SOURCE_DIR}/World/FieldListIterator.cpp
              ${SOURCE_DIR}/World/Grid.cpp
              ${SOURCE_DIR}/World/Vector.cpp
              ${SOURCE_DIR}/World/World.cpp
              ${SOURCE_DIR}/World/WorldSnapshot.cpp)
# ------------------------------

# If build python library option is activated build a library
if (BUILD_PYTHON_LIBRARY)
        # First set the library source
        set(LIBRARY_SRC ${RENDERER_SRC}
                        ${WORLD_SRC}
                        ${BOT_SRC}
                        src/PythonBinding/Binding.cpp)
        
        # Add define BUILD_PYTHON to add individual files
        add_compile_definitions(BUILD_PYTHON)
        
        add_library(CellWars MODULE ${LIBRARY_SRC})
        # Add pybind library
        add_subdirectory(pybind11)
        include_directories(pybind11/include)
        
        target_link_libraries(CellWars PRIVATE pybind11::module
                                sfml-system
                                sfml-window
                                # sfml-network
                                # sfml-audio
                                sfml-graphics)
        set_target_properties(CellWars PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}")
else()
        # Add the cellwars library and link it with SFML
        set(LIBRARY_SRC ${RENDERER_SRC}
                        ${WORLD_SRC}
                        ${BOT_SRC})
        add_library(CellWarsLibrary ${LIBRARY_SRC})
        target_link_libraries(CellWarsLibrary
                        sfml-system
                        sfml-window
                        # sfml-network
                        # sfml-audio
                        sfml-graphics)

        # Create the executable
        add_executable(CellWars ${SOURCE_DIR}/Main.cpp)

        # Link all necessary libraries
        target_link_libraries(CellWars CellWarsLibrary)
endif()