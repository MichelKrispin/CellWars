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

# Bots
set(BOT_SRC ${SOURCE_DIR}/Bot/Bot.cpp
            ${SOURCE_DIR}/Bot/EnemyBot.cpp
            ${SOURCE_DIR}/Bot/PlayerBot.cpp)
# Renderer
set(RENDERER_SRC ${SOURCE_DIR}/Renderer/Window.cpp)

# World
set(WORLD_SRC ${SOURCE_DIR}/World/Field.cpp
              ${SOURCE_DIR}/World/FieldList.cpp
              ${SOURCE_DIR}/World/FieldListIterator.cpp
              ${SOURCE_DIR}/World/Grid.cpp
              ${SOURCE_DIR}/World/Vector.cpp
              ${SOURCE_DIR}/World/World.cpp
              ${SOURCE_DIR}/World/WorldSnapshot.cpp)
# ------------------------------

project (CellWars)

# First create the library
set(LIBRARY_SRC ${RENDERER_SRC}
                ${WORLD_SRC}
                ${BOT_SRC})

add_library(CellWarsLibrary ${LIBRARY_SRC})
target_link_libraries(CellWarsLibrary
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio)


# Then create the executable
set(SOURCE_FILES ${SOURCE_DIR}/Main.cpp)

# Add the executable
add_executable(CellWars ${SOURCE_FILES})

# link all necessary libraries
# Link all necessary libraries
target_link_libraries(CellWars
        CellWarsLibrary)

