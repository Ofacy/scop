cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# to generate compile_commands.json (for clangd)

project(scop)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g3")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Add the source files (non-class source files)
set(SRC_FILES
	main
)

# Add the include files (non-class headers)
set(INC_FILES)

# Add the class source files and headers
# Note: The class names should match the filenames (e.g., GLContext.cpp, GLContext.hpp)
set(CLASS_NAMES
	GLContext
	Window
	Shader
	ShaderProgram
	Mesh
	MeshLoader
	Mat4
	Texture
	BMPLoader
)

list(INSERT SRC_FILES 0 ${CLASS_NAMES})
list(INSERT INC_FILES 0 ${CLASS_NAMES})
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM SRC_FILES APPEND .cpp)
list(TRANSFORM INC_FILES PREPEND ${INC_DIR}/)
list(TRANSFORM INC_FILES APPEND .hpp)

# no-pie
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -no-pie")

add_executable(
	scop
	${SRC_FILES}
	${INC_FILES}
)


target_include_directories(scop PRIVATE
	${INC_DIR}
)

# Find and link the OpenGL library
# Force the use of GLVND for OpenGL
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} )


# GLAD
add_subdirectory(ext/glad/)


target_link_libraries(scop ${OPENGL_LIBRARIES} glfw glad)