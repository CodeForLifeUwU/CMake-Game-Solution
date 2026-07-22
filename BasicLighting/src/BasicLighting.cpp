#include "engine.hpp"

// globals

struct State {
	Engine::Camera* pCamera;
	Engine::Window* pWindow;
};
// Event Callbacks
void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	if (h > w) {
		glViewport(0, h / 4, w, w);
	}
	else
	{
		glViewport(0, 0, w, h);
	}

	State* pState = static_cast<State*>(glfwGetWindowUserPointer(window));

	pState->pCamera->changeAspectRatio((float)w / h);
	pState->pCamera->update();
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	State* pState = static_cast<State*>(glfwGetWindowUserPointer(window));

	float deltaFOV = yoffset;

	pState->pCamera->zoom(deltaFOV);
	pState->pCamera->update();
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	State* pState = static_cast<State*>(glfwGetWindowUserPointer(window));


	Engine::Camera* pCamera = pState->pCamera;
	Engine::Window* pWindow = pState->pWindow;

	if (action == GLFW_PRESS)
	{
		glm::vec3 direction = pState->pCamera->getDirection();
		glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
		glm::vec3 forward = glm::cross(glm::vec3(0, 1, 0), right);

		if (key == GLFW_KEY_W) {
			pCamera->speed = forward;
		}
		else if (key == GLFW_KEY_A) {
			pCamera->speed = -right;
		}
		else if (key == GLFW_KEY_S) {
			pCamera->speed = -forward;
		}
		else if (key == GLFW_KEY_D) {
			pCamera->speed = right;
		}
		else if (key == GLFW_KEY_E) {
			pCamera->speed = glm::vec3(0, 1, 0);
		}
		else if (key == GLFW_KEY_Q) {
			pCamera->speed = -glm::vec3(0, 1, 0);
		}
	}

	else if (action == GLFW_RELEASE) {
		GLFWwindow* activeWindow = pWindow->getWindowPointer();

		if (glfwGetKey(activeWindow, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(activeWindow, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(activeWindow, GLFW_KEY_S) == GLFW_RELEASE && glfwGetKey(activeWindow, GLFW_KEY_D) == GLFW_RELEASE) {
			pCamera->speed = glm::vec3(0, 0, 0);
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	//std::cout << mouseEnteredFirst << std::endl;
	static double lastX = xpos;
	static double lastY = ypos;


	double dx = xpos - lastX;
	double dy = ypos - lastY;

	//std::cout << "relative: (" << dx << ", " << dy << ")\r";
	//std::cout << "motion" << xpos << ' ' << ypos << "\n";
	
	State* pState = static_cast<State*>(glfwGetWindowUserPointer(window));

	float sensitivity = 0.05f;
	pState->pCamera->rotate(-(float)dx * sensitivity, -(float)dy * sensitivity);

	lastX = xpos;
	lastY = ypos;
}

struct Vertex{
	glm::vec3 position;
	glm::vec2 color;
	glm::vec3 normal;
};


// THE MAIN FUNCTION
int main() {

	for (int i = 0; i<10;++i){
		for (int j = 0; j<=i;++j){
			std::cout << "*";
		}
		std::cout << "\n";
	}

	std::cout << sizeof(Vertex) << std::endl;

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	std::cout << "GLFW initialized successfully" << std::endl;


	// Set GLFW window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "GLFW window hints set successfully" << std::endl;

	int WINDOW_W = 800;
	int WINDOW_H = 600;
	Engine::Window window;

	if(!window.createWindow(WINDOW_W, WINDOW_H, "PhysX")) {
		glfwTerminate();
		return -1;
	}
	std::cout << "Window created successfully" << std::endl;

	window.makeCurrentContext();

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
		std::cerr << "Failed to load openGL functions" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, WINDOW_W, WINDOW_H);


	
	// Compiling Shaders
	Engine::Shader colorShader = Engine::Shader("color", "./shaders/color.vert", "./shaders/color.frag");

	if (not colorShader.checkSuccess()) {
		std::cerr << "color Shaders did not compile successfully." << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "color Shader compiled successfully" << std::endl;


	// Engine::Shader floorShader = Engine::Shader("Floor", "./floor.vert", "./floor.frag");

	// if (not floorShader.checkSuccess()) {
	// 	std::cerr << "Shaders did not compile successfully." << std::endl;
	// 	glfwTerminate();
	// 	return -1;
	// }
	// std::cout << "Floor Shader compiled successfully" << std::endl;




	// Camera
	Engine::Camera camera = Engine::Camera(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 2.0f, 0.0f));

	camera.bindShader(colorShader);
	//camera.bindShader(floorShader);



	// Cube — six faces, standard Rubik's cube colors (not turnable)
	std::vector<GLfloat> cubeVertices = {
		// Positions          // Normals          // Colors
		// Front (+Z) — green
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		// Back (-Z) — blue
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		// Top (+Y) — white
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		// Bottom (-Y) — yellow
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		// Right (+X) — red
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		// Left (-X) — orange
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.5f, 0.0f,
	};

	std::vector<GLuint> cubeIndices = {
		0,  1,  2,   0,  2,  3,   // front
		4,  5,  6,   4,  6,  7,   // back
		8,  9, 10,   8, 10, 11,   // top
		12, 13, 14,  12, 14, 15,   // bottom
		16, 17, 18,  16, 18, 19,   // right
		20, 21, 22,  20, 22, 23,   // left
	};

	Engine::Model cubeModel = Engine::Model();

	if (!cubeModel.loadModel(cubeVertices, cubeIndices)) {
		std::cerr << "Failed to load cube model" << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "Cube model loaded successfully" << std::endl;
	cubeModel.sendModelBuffer();

	cubeModel.bindShader(colorShader);

	float scale = 0.1f;
	cubeModel.scale(glm::vec3(scale, scale, scale));

	cubeModel.translate(glm::vec3(0.0f, 2.0f, 0.0f));
	cubeModel.updateModelMatrix();




	// std::vector<GLfloat> floorVertices = {
	// 	10,0,10, 1, 1,0,
	// 	10,0,-10, 1, 0,0,
	// 	-10,0,-10, 0, 0,0,
	// 	-10,0,10, 0, 1,0
	// };

	// std::vector<GLuint> floorIndices = {
	// 	0, 1, 2,
	// 	0, 2, 3
	// };

	// Engine::Model floorModel = Engine::Model();

	// if (!floorModel.loadModel(floorVertices, floorIndices)) {
	// 	std::cerr << "Failed to load floor model" << std::endl;
	// 	glfwTerminate();
	// 	return -1;
	// }
	// std::cout << "floor model loaded successfully" << std::endl;
	// floorModel.sendModelBuffer();

	// floorModel.bindShader(floorShader);

	// floorModel.updateModelMatrix();



	float t1, t2, dt;

	dt = 0.0f;


	State state;
	state.pCamera = &camera;
	state.pWindow = &window;


	// C++

	glfwSetInputMode(window.getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(window.getWindowPointer(), &state);


	// Callbacks
	glfwSetFramebufferSizeCallback(window.getWindowPointer(), framebuffer_size_callback);

	glfwSetCursorPosCallback(window.getWindowPointer(), mouse_callback);
	glfwSetScrollCallback(window.getWindowPointer(), mouse_scroll_callback);

	glfwSetKeyCallback(window.getWindowPointer(), keyboard_callback);


	camera.update();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// main loop
	while (!window.getClosingStatus()) {

		camera.translate(2.0f*camera.speed * window.getFrameTime());
		camera.update();

		// float t1 = (float)glfwGetTime();

		// float rotationAngle = 45.0f * t1;
		// colorShader.setFloat("rotation", rotationAngle);

		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(0.025f, 0.04f, 0.065f, 1.0f);
		glClearColor(0.03f, 0.055f, 0.09f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw cube
		cubeModel.draw();
		//floorModel.draw();
		//inosukeModel.draw();

		window.swapBuffers();
		glfwPollEvents();
	}

	// cleanup
	glfwTerminate();
	return 0;
}
