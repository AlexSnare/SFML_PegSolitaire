project(EXP7)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(SFML_DIR "SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.9.9\\5.9.9\\msvc2017_64\\")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB_RECURSE src_cpp main.cpp Holst.cpp)
file(GLOB_RECURSE src_h Holst.h)

set(sources
    ${src_cpp}
    ${src_h}
)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets sfml-system sfml-window sfml-graphics)