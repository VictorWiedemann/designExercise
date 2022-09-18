cmake_minimum_required(VERSION 3.14)

project(simpleGame LANGUAGES CXX)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_BUILD_TYPE Debug) ##Add logic to choose debug vs release build if needed later
set(CMAKE_CXX_STANDARD 17)
add_executable(simpleGame src/main.cpp )


target_sources(simpleGame 
                PUBLIC ${CMAKE_SOURCE_DIR}/src/buttons.cpp
                PUBLIC ${CMAKE_SOURCE_DIR}/src/led.cpp
                PUBLIC ${CMAKE_SOURCE_DIR}/src/game.cpp
                ) 




target_link_libraries(simpleGame
    -lncurses #TODO delete this when moving to hardware
)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include(CPack)


