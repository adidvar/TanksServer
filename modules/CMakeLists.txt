cmake_minimum_required (VERSION 3.20.0)
project (Modules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Headers "*.h")

file(GLOB Sources "*.cpp")

find_package(Boost 1.76 REQUIRED) 

add_library(Modules SHARED ${Headers} ${Sources})
target_include_directories(Modules INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(Modules Objects ${Boost_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
target_link_libraries(Modules ws2_32 wsock32)
endif()

install(TARGETS Modules DESTINATION ${CMAKE_INSTALL_PREFIX})

