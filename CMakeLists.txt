cmake_minimum_required(VERSION 2.8)
include_directories (${Box2D_SOURCE_DIR})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(GRAPHICS_LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} Box2D)
set(GRAPHICS_SOURCES physics.cpp graphic.cpp main.cpp)

add_executable(graphics ${GRAPHICS_SOURCES})
target_link_libraries(graphics ${GRAPHICS_LIBRARIES})
