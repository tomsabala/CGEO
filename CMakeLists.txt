cmake_minimum_required(VERSION 3.18)
project(CGEO CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE CGEO_CORE_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/2D/shapes_2D/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/2D/algorithms_2D/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/3D/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures/*.cpp")

add_library(cgeo_core STATIC ${CGEO_CORE_SOURCES})
target_include_directories(cgeo_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

option(CGEO_BUILD_PYTHON "Build the pybind11 extension module" ON)

if(CGEO_BUILD_PYTHON)
    find_package(Python 3.10 COMPONENTS Interpreter Development.Module REQUIRED)
    find_package(pybind11 CONFIG QUIET)
    if(NOT pybind11_FOUND)
        include(FetchContent)
        FetchContent_Declare(pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v3.1.0)
        FetchContent_MakeAvailable(pybind11)
    endif()

    pybind11_add_module(_cgeo src/2D/2D_bindings.cpp)
    target_link_libraries(_cgeo PRIVATE cgeo_core)
    target_compile_definitions(_cgeo PRIVATE EXTENSION_NAME=_cgeo)
endif()
