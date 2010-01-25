cmake_minimum_required(VERSION 2.6)

project(ZiaParser)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(headers)
include_directories(/usr/local/include/boost_1_39_0)

link_directories(/usr/lib)

file(
  GLOB_RECURSE
  sample
  src/*
  headers/*
)

file(
  GLOB_RECURSE
  unit_testing
  unitTesting/*
)

add_executable(ZiaSample ${sample})
add_executable(UnitTesting ${unit_testing})

target_link_libraries(
  ZiaSample
  boost_system-gcc43-mt-1_39
  boost_thread-gcc43-mt-1_39
)
