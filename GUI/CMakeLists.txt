cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME zappy_gui)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-gnu-unique")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g3 -fno-gnu-unique")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(
        src
        src/Game
        src/Game/Map
        src/Game/Tiles
)


add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/Game/Map/Map.cpp
        src/Game/Tiles/Tile.cpp
        src/Game/Game.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)


set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "lib")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${PROJECT_NAME}>
        ${PROJECT_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>)
