cmake_minimum_required (VERSION 3.20.0)
project (TanksServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(Visual "compile graphics visualizer" ON)

#include(${CMAKE_CURRENT_SOURCE_DIR}/conan_paths.cmake)

add_subdirectory(Core)
add_subdirectory(Objects)
add_subdirectory(Modules)

add_executable(TanksServer main.cpp)
target_link_libraries(TanksServer Modules)

install(TARGETS TanksServer DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES map.txt DESTINATION ${CMAKE_INSTALL_PREFIX})