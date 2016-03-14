cmake_minimum_required (VERSION 2.6)
project (tereZ)

add_subdirectory(../../oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(tereZ ../src/example.cpp ../src/main.cpp  ../src/example.h )

if (WIN32) #disable console mode for VC++
	set_target_properties(tereZ PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

target_link_libraries(tereZ ${OXYGINE_CORE_LIBS})