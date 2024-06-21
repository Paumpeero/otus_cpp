cmake_minimum_required(VERSION 3.11)

project(HelloAsync CXX)
set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/Public/Libraries/boost_1_84_0")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Users/Public/Libraries/boost_1_84_0/stage/lib")

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

find_package(Boost 1.78.0 REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(hello_async
  main.cpp
  src/sdk.h)
target_link_libraries(hello_async PRIVATE Threads::Threads)
