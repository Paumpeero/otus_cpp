cmake_minimum_required(VERSION 3.11)

project(HelloAsync CXX)
set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.78.0 REQUIRED COMPONENTS log)
if (Boost_FOUND)
  message(Boost_INCLUDE_DIRS)
  include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(otus_cpp
  main.cpp
  src/sdk.h)
target_link_libraries(otus_cpp PRIVATE Threads::Threads Boost::log)
