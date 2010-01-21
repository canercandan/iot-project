cmake_minimum_required(VERSION 2.6)
include(FindBoost)

project(expert_system)

if (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -g3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3")
  endif()
endif()


find_package(
  Boost
  1.41.0
  COMPONENTS system thread filesystem REQUIRED
)


include_directories(includes)
include_directories(${Boost_INCLUDE_DIRS})

file(
  GLOB_RECURSE
  src/*.cpp
  includes/*.h
  includes/*.hpp
)

add_executable(backward_chaining)
