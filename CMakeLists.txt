project(BoxGL)

cmake_minimum_required(VERSION 2.8)

add_subdirectory(box2d)
add_subdirectory(json)
add_subdirectory(glfw)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/box2d)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/json/json)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/glfw/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

set(GRAPHICS_LIBRARIES ${OPENGL_LIBRARIES} glfw Box2D json)
set(GRAPHICS_HEADERS include/elements.h include/physics.h include/graphic.h include/utils.h)
set(GRAPHICS_SOURCES elements.cpp physics.cpp graphics.cpp main.cpp)

add_executable(graphics ${GRAPHICS_SOURCES} ${GRAPHICS_HEADERS})
target_link_libraries(graphics ${GRAPHICS_LIBRARIES})
