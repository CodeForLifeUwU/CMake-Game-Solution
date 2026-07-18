#ifndef ENGINE_HPP

#define ENGINE_HPP

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {

	class Shader;
	class Window;
	class Camera;
	class Model;

	class lighting;
};

#include "Lighting.hpp"

#include "Shader.hpp"

#include "model.hpp"
#include "Window.hpp"
#include "Camera.hpp"

#endif // !ENGINE_HPP
