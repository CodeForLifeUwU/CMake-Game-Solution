cmake_minimum_required(VERSION 3.12)

find_package(OpenGL REQUIRED)


add_subdirectory(external/glfw-3.4)

file(GLOB SOURCES "src/*.cpp")
add_executable (BasicLighting
	${SOURCES}
	"external/glad/src/gl.c"
)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BasicLighting PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(BasicLighting PRIVATE
	OpenGL::GL
	glfw
	C:/Libraries/Assimp/lib/assimp-vc145-mt.lib
)
target_include_directories(BasicLighting PRIVATE
	"C:/Libraries/Assimp/include"
	"include"
	"external/glad/include"
	"external/glm-master"
)
