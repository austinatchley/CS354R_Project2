cmake_minimum_required (VERSION 3.3.0)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_PREFIX_PATH "/lusr/opt/bullet-2.86/;${CMAKE_PREFIX_PATH}")

# When in debug mode, we run Address Sanitizer to find memory errors
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -fsanitize=address")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_TRDPARTY_DIR 3rdparty/)
include(cmake/clang-format.cmake)

set(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Ball.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Paddle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SoundManager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/PlayState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/MenuState.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/ECSManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/System.cpp
)

set(HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Ball.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Paddle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SoundManager.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/PlayState.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/MenuState.h
)

project(Project2)

find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)

# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Project2 ${HDRS} ${SRCS})

find_package(SDL2 REQUIRED) 
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES) # remove the whitespace in the path on the lab machines

find_package(SDL2_mixer QUIET) 
if (NOT SDL2MIXER_FOUND) # this is for the lab machines, where find_package doesn't work for sdl_mixer
    set(SDL2MIXER_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_mixer-2.0.so.0")
endif (NOT SDL2MIXER_FOUND)

find_package(Bullet 2.86)
#set (BULLET_INCLUDE_DIR "/lusr/opt/bullet-2.79/include")
#set (BULLET_LIBRARIES "/lusr/opt/bullet-2.79/lib")

# Everything in the include directory can be #include'd from cpp and h files
# without using relative paths
target_include_directories(
    Project2 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    #${BULLET_INCLUDE_DIR}
    /usr/include/bullet
)

target_link_libraries(Project2
    ${OGRE_LIBRARIES}
    ${OIS_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    ${BULLET_LIBRARIES}
)
