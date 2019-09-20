cmake_minimum_required (VERSION 3.14)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set the output directory of the exe inside a dedicated bin folder
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

# Add DEBUG macro if build type equals debug
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

# SFML Library build statically
set(BUILD_SHARED_LIBS false)
add_subdirectory(SFML)
include_directories(${SFML_SOURCE_DIR}/include)
# -----------

# Default source dir as include directory
set(SOURCE_DIR src/)
include_directories(${SOURCE_DIR})
# -----------

project (CellWars)

set(SOURCE_FILES ${SOURCE_DIR}/Main.cpp
                 ${SOURCE_DIR}/Bot.cpp
                 ${SOURCE_DIR}/Field.cpp
                 ${SOURCE_DIR}/FieldList.cpp
                 ${SOURCE_DIR}/FieldListIterator.cpp
                 ${SOURCE_DIR}/Window.cpp
                 ${SOURCE_DIR}/World.cpp
                 ${SOURCE_DIR}/WorldSnapshot.cpp
                 )

# add the executable
add_executable(CellWars ${SOURCE_FILES})

# link all necessary libraries
target_link_libraries(CellWars
    sfml-system
    sfml-window
    sfml-network
    sfml-graphics
    sfml-audio)

