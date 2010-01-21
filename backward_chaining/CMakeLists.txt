cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(ExpertSystem)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

set(CXXFLAGS -03)

#Inclusion de Boost
include_directories(/usr/local/boost headers)
link_directories(/usr/local/boost/libs)

#Configuration de l'exécutable
file(
    GLOB_RECURSE
    source_files
    src/*.cpp
    headers/*.h
    headers/*.hpp
)

add_executable(
    backward_chaining
    ${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
    backward_chaining
#    boost_signals-mt
)
