cmake_minimum_required (VERSION 2.6)
project (tereZ)

add_subdirectory(../../oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_subdirectory(../../oxygine-sound/ oxygine-sound)
include_directories(${OXYGINESOUND_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB all_SRC
    "../src/*.h"
    "../src/*.cpp"
)
add_executable(tereZ ${all_SRC})

if (WIN32) #disable console mode for VC++
	set_target_properties(tereZ PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(tereZ ${OXYGINESOUND_LIBS} ${OXYGINE_CORE_LIBS})