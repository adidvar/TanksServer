cmake_minimum_required (VERSION 3.16.0)
project (Objects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Headers "*.h")

file(GLOB Sources "*.cpp")

add_library(Objects ${Headers} ${Sources})
target_link_libraries(Objects Core)
target_include_directories(Objects INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS Objects DESTINATION ${CMAKE_INSTALL_PREFIX})
