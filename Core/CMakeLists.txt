cmake_minimum_required (VERSION 3.20.0)
project (Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Headers "*.h")

file(GLOB Sources "*.cpp")

add_library(Core ${Headers} ${Sources})
target_include_directories(Core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(${Visual})
set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 2.5.1 COMPONENTS system window graphics)
if(${SFML_FOUND})
add_definitions(-DSCREEN)	
target_link_libraries(Core sfml-system sfml-window sfml-graphics)
endif()
endif()

install(TARGETS Core DESTINATION ${CMAKE_INSTALL_PREFIX})
