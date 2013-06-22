project(BoxGL)

cmake_minimum_required(VERSION 2.8)

add_subdirectory(box2d)
add_subdirectory(jsonrpc)

if(WIN32)
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/box2d/Box2D/Debug)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

set(GRAPHICS_LIBRARIES ${OPENGL_LIBRARIES} FreeGLUT Box2D json)
set(GRAPHICS_SOURCES elements.cpp physics.cpp graphics.cpp main.cpp)

add_executable(graphics ${GRAPHICS_SOURCES})
target_link_libraries(graphics ${GRAPHICS_LIBRARIES})
