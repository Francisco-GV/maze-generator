cmake_minimum_required(VERSION 3.0.0)
project(
  maze-generator
  VERSION 1.1.0
  LANGUAGES CXX)

set(SOURCES src/main.cpp src/Canvas.cpp src/Cell.cpp src/Maze.cpp
    src/util/Util.cpp
    src/util/Random.cpp
    src/algorithms/Algorithm.cpp 
    src/algorithms/RecursiveBacktracker.cpp
    src/algorithms/IterativeBacktracker.cpp
    src/algorithms/KruskalAlgorithm.cpp)

add_executable(maze-generator ${SOURCES})
target_include_directories(maze-generator
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Setup SFML
set(SFML_LIBS sfml-graphics sfml-window sfml-system)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
target_link_libraries(maze-generator PRIVATE ${SFML_LIBS})
target_include_directories(maze-generator PRIVATE ${SFML_INCLUDE_DIR})

# Copy SFML DLLs to build directory
foreach(lib ${SFML_LIBS})
  get_target_property(lib_path ${lib} LOCATION)
  file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

# Copy config.txt to build directory
set(CONFIG_FILE config.txt)
set(SRC_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG_FILE}")
set(DEST_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE}")

if(EXISTS ${SRC_CONFIG_FILE})
  if(NOT EXISTS ${DEST_CONFIG_FILE})
    file(COPY ${SRC_CONFIG_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  endif()
endif()
