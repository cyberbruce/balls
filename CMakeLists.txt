cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(game)

add_executable(
  game
  particles.cpp
)

find_package(SFML 2.5.1 COMPONENTS network audio graphics window system)
target_link_libraries(
  game
  sfml-graphics
  sfml-window
  sfml-system
  sfml-audio
)
 
#target_include_directories(game PUBLIC /usr/local/Cellar/sfml/2.5.1_1/include)
target_include_directories(game PUBLIC $SFML_INCLUDE_DIR)


