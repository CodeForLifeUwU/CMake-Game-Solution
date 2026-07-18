#ifndef WINDOW_HPP

#define WINDOW_HPP

class Engine::Window {
public:
	Window() = default;
	~Window();

	inline GLFWwindow* getWindowPointer() { return mWindow; }
	inline float getFrameTime() { return frametime; }
	bool getClosingStatus() {return glfwWindowShouldClose(mWindow)==GL_TRUE ; }

	bool createWindow(int width, int height, const char* title);
	void destroyWindow();

	bool makeCurrentContext();

	void shouldClose();
	void swapBuffers();

private:
	float previous, now;
	float frametime = 0;

	GLFWwindow* mWindow = nullptr;
	const char* mName = "";
};

#endif // !WINDOW_HPP
