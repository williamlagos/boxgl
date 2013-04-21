project(BoxGL)

cmake_minimum_required(VERSION 2.8)

if(WIN32)
 set(GLUT_INCLUDE_DIR include/)
 set(GLUT_glut_LIBRARY lib/glut32)
 set(Box2D_LIBRARIES lib/Box2D)
 set(Box2D_SOURCE_DIR include/)
endif()

include_directories (${Box2D_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(GRAPHICS_LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${Box2D_LIBRARIES})
set(GRAPHICS_SOURCES physics.cpp graphic.cpp main.cpp)

set(CMAKE_EXE_LINKER_FLAGS static)

add_executable(graphics ${GRAPHICS_SOURCES})
target_link_libraries(graphics ${GRAPHICS_LIBRARIES})
