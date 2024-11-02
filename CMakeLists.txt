cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENV{CC} 'clang')
set(ENV{CXX} 'clang++')

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    message(FATAL_ERROR "Please install submodules: git submodule update --init --recursive")
endif ()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(carlos)

find_package(cxxopts CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)

include_directories(${cxxopts_INCLUDE_DIRS})
include_directories(${glog_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/src/grammar)
include_directories(${CMAKE_SOURCE_DIR}/src/includes)

file(GLOB_RECURSE CXX_CODES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE CXX_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.hpp ${CMAKE_SOURCE_DIR}/src/*.h)


add_executable(carlos)


target_sources(carlos PRIVATE ${CXX_CODES})
target_sources(carlos PRIVATE ${CXX_HEADERS})

target_link_libraries(carlos PRIVATE cxxopts::cxxopts)
target_link_libraries(carlos PRIVATE glog::glog)


