cmake_minimum_required (VERSION 3.1)
project (TanksServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(Core game.h game.cpp main.cpp)
target_link_libraries(Core ${CONAN_LIBS})

add_library(Module modules/module.h modules/module.cpp modules/gamesignal.h)

add_library(Object objects/objectinterface.h objects/objectinterface.cpp objects/object.h)

add_library(MathTools math/mvector.h math/mvector.cpp math/shapes.h math/shapes.cpp)

add_library(Collisions collisions/collision.h collisions/collision.cpp collisions/collision_visualizer.h collisions/collision_visualizer.cpp collisions/container.h collisions/container.cpp)

add_library(PlayerModule modules/playermodule.h modules/playermodule.cpp objects/tank.h objects/tank.cpp net/player_controller.h net/player_controller.cpp)

add_library(MapModule modules/map.h modules/map.cpp)

add_library(BulletModule modules/bulletmodule.h modules/bulletmodule.cpp objects/bullet.h objects/bullet.cpp)

#target_link_libraries(Core sfml-system sfml-window sfml-graphics)
#target_include_directories(Core PRIVATE ./SFML/include/)
#target_link_directories(Core ./SFML/lib/)

add_executable(Server main.cpp)
target_link_libraries(Server Core Module Object MathTools Collisions PlayerModule BulletModule MapModule)


 