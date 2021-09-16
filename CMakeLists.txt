cmake_minimum_required (VERSION 3.1)
project (TanksServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(.)
include_directories(./SFML/include/)
link_directories(./SFML/lib/)

add_library(Core object.h debug_tools/collision_visualizer.h debug_tools/collision_visualizer.cpp net/player_controller.cpp net/player_controller.h math_tools/collision.cpp math_tools/collision.h math_tools/mvector.cpp math_tools/mvector.h math_tools/shapes.cpp math_tools/shapes.h objectinterface.cpp objectinterface.h module.cpp module.h bullet.cpp bullet.h bulletmodule.cpp bulletmodule.h container.cpp container.h game.cpp game.h tank.cpp tank.h map.cpp map.h playermodule.cpp playermodule.h)
target_link_libraries(Core sfml-system sfml-window sfml-graphics)

add_executable(Server main.cpp)
target_link_libraries(Server Core)


 