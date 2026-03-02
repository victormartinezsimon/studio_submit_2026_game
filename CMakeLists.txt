cmake_minimum_required(VERSION 3.16)

project(StudioSummitGame)

# ==============================
# General configuration
# ==============================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/Main.cpp
    src/Plane.cpp
    src/Bullet.cpp
    src/InputManager.cpp
    src/RaylibPainter.cpp
)

set(HEADERS
    src/Pool.h
    src/Plane.h
    src/Bullet.h
    src/InputManager.h
    src/GameConfig.h
    src/WorldObject.h
    src/RaylibPainter.h
)

# ==============================
# Exe
# ==============================

add_executable(StudioSummitGame ${SOURCES} ${HEADERS})

target_compile_features(StudioSummitGame PRIVATE cxx_std_20)

# ==============================
# raylib with vcpkg
# ==============================

find_package(raylib CONFIG QUIET)

if (raylib_FOUND)

    message(STATUS "Usando raylib desde vcpkg o instalación con config")

    target_link_libraries(StudioSummitGame PRIVATE raylib)

    # only need heaers
    find_path(RAYLIB_CPP_INCLUDE_DIR
        NAMES raylib-cpp.hpp
    )

    if(NOT RAYLIB_CPP_INCLUDE_DIR)
        message(FATAL_ERROR "raylib-cpp no found. Install with vcpkg.")
    endif()

    target_include_directories(StudioSummitGame PRIVATE ${RAYLIB_CPP_INCLUDE_DIR})

else()

    message(STATUS "Not raylib found, trying with apt")

    # for linux, raylib installed by apt
    find_library(RAYLIB_LIB raylib REQUIRED)

    target_link_libraries(StudioSummitGame PRIVATE ${RAYLIB_LIB})

    find_path(RAYLIB_CPP_INCLUDE_DIR
        NAMES raylib-cpp.hpp
        PATHS /usr/include /usr/local/include
    )

    if(NOT RAYLIB_CPP_INCLUDE_DIR)
        message(FATAL_ERROR "raylib-cpp no found.")
    endif()

    target_include_directories(StudioSummitGame PRIVATE ${RAYLIB_CPP_INCLUDE_DIR})

endif()

# ==============================
# UNIX Configuration
# ==============================

if (UNIX AND NOT APPLE)

    # Raspberry Pi / ARM need atomic
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR
        CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")

        message(STATUS "compiling for arm. add atomic")
        target_link_libraries(StudioSummitGame PRIVATE atomic)
    endif()

endif()

# ==============================
# Images copy
# ==============================

set(SOURCE_DIR_CONFIG "${CMAKE_SOURCE_DIR}/images")
set(DESTINATION_DIR_CONFIG "${CMAKE_BINARY_DIR}")

file(COPY "${SOURCE_DIR_CONFIG}" DESTINATION "${DESTINATION_DIR_CONFIG}")

message(STATUS "CMAKE Ended")