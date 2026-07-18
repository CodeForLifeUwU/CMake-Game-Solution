#include "Engine.hpp"


bool Engine::Window::createWindow(int width, int height, const char* title) {

	mName = title;

	mWindow = glfwCreateWindow(width, height, "PhysX", NULL, NULL);

	if (!mWindow) {
		std::cerr << "Failed to create window with name " << mName << std::endl;
		return false; // Return false on failure
	}
	return true; // Return true on success
}


void Engine::Window::swapBuffers() {
	glfwSwapBuffers(mWindow);
	static bool firstTime = true;
	if (firstTime) {
		firstTime = false;
		previous = glfwGetTime();
	}
	now = glfwGetTime();

	frametime = now - previous;

	previous = now;

}

bool Engine::Window::makeCurrentContext() {
	if (!mWindow) {
		std::cerr << "Invalid window object." << std::endl;
		return false;
	}
	glfwMakeContextCurrent(mWindow);
	return true;
}

void Engine::Window::destroyWindow() {
	if (!mWindow) {
		std::cerr << "Invalid window object." << std::endl;
		return;
	}
	glfwDestroyWindow(mWindow);
	mWindow = nullptr;
}

void Engine::Window::shouldClose() {
	if (!mWindow) {
		std::cerr << "Invalid window object." << std::endl;
		return;
	}
	glfwSetWindowShouldClose(mWindow, GL_TRUE);
}


Engine::Window::~Window() {
	if(mWindow != nullptr)this->destroyWindow();
}