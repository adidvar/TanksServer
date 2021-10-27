cmake_minimum_required (VERSION 3.16.0)
project (TanksServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include(${CMAKE_CURRENT_SOURCE_DIR}/conan_paths.cmake)

add_subdirectory(Core)
add_subdirectory(Objects)
add_subdirectory(Modules)

add_executable(TanksServer main.cpp)
target_link_libraries(TanksServer Modules)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
target_link_libraries(TanksServer winmm)
endif()

install(TARGETS TanksServer DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES map.txt DESTINATION ${CMAKE_INSTALL_PREFIX})
