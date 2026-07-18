#ifndef CAMERA_HPP

#define CAMERA_HPP

class Engine::Camera {
public:
	glm::vec3 speed = { 0, 0, 0 };

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
public:
	Camera(glm::vec3 position, glm::vec3 target);
	~Camera() = default;

	glm::vec3 getDirection() { return this->cameraDirection; };
	glm::vec3 getPos() { return this->cameraPos; };

	void update();

	void bindShader(Engine::Shader& shaderProgram);


	void translate(const glm::vec3& translationVector);
	void rotate(float deltaYaw, float deltaPitch);
	void zoom(float deltaFOV);
	void changeAspectRatio(float ratio);

private:
	float fov = 45.0f;

	int width = 800;
	int height = 600;

	float aspectRatio = 800.0/600.0;
	float yaw = 180.0f;
	float pitch = 0;

	std::vector<Engine::Shader*> pBoundPrograms;

	glm::mat4 view;
	glm::mat4 projection;
};

#endif // !CAMERA_HPP
