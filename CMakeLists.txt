cmake_minimum_required(VERSION 3.11)

project(HelloAsync CXX)
set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

find_package(Boost 1.78.0 REQUIRED log)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

configure_file(config.json ${CMAKE_BUILD_RPATH} config.json COPYONLY)

add_executable(hello_async
  main.cpp
  src/sdk.h)
target_link_libraries(hello_async PRIVATE Threads::Threads Boost::log)
