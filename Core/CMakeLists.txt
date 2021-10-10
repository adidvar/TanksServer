cmake_minimum_required (VERSION 3.20.0)
project (Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Headers "*.h")

file(GLOB Sources "*.cpp")

add_library(Core SHARED ${Headers} ${Sources})
target_include_directories(Core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS Core DESTINATION ${CMAKE_INSTALL_PREFIX})
