cmake_minimum_required(VERSION 3.12)

find_package(OpenGL REQUIRED)


add_subdirectory(external/glfw-3.4)

file(GLOB SOURCES "src/*.cpp")
add_executable (BasicLighting
${SOURCES}
"external/glad/src/gl.c"
)

# Define the shader files
set(SHADER_FILES
	"shaders/color.vert"
	"shaders/color.frag"
	"shaders/floor.vert"
	"shaders/floor.frag"
)

# Copy shaders to the build output directory whenever they change
foreach(SHADER IN LISTS SHADER_FILES)
    get_filename_component(SHADER_DIR "${SHADER}" DIRECTORY)

    add_custom_command(TARGET BasicLighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:BasicLighting>/${SHADER_DIR}"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER}"
            "$<TARGET_FILE_DIR:BasicLighting>/${SHADER}"
    )
endforeach()



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
