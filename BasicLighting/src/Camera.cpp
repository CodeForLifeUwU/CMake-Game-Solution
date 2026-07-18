#include "Engine.hpp"


void Engine::Camera::bindShader(Engine::Shader& shaderProgram) {
	pBoundPrograms.push_back(&shaderProgram);
}


void Engine::Camera::update() {
	for(auto* shader : pBoundPrograms){
		if (shader) {
			shader->setMat4("view", view);
			shader->setMat4("projection", projection);
		}
	}
}



void Engine::Camera::translate(const glm::vec3& translationVector) {
	cameraPos += translationVector;
	view = glm::lookAt(cameraPos, cameraPos+cameraDirection, glm::vec3(0.0, 1.0, 0.0));
}

void Engine::Camera::rotate(float deltaYaw, float deltaPitch) {
	yaw += deltaYaw;
	pitch += deltaPitch;

	if (pitch > 85.0f) {
		pitch = 85.0f;
	}

	else if (pitch < -85.0f) {
		pitch = -85.0f;
	}
	
	float yawRadians = glm::radians(yaw);

	cameraDirection[0] = glm::sin(yawRadians);
	cameraDirection[2] = glm::cos(yawRadians);

	float pitchRadians = glm::radians(pitch);

	cameraDirection[1] = glm::sin(pitchRadians);
	cameraDirection[0] *= glm::cos(pitchRadians);
	cameraDirection[2] *= glm::cos(pitchRadians);

	// The above lines might look complicated but they rotate the direction vector appropriately.
	// The vector is assumed to be originally at (0, 0, 1).
	
	view = glm::lookAt(cameraPos, cameraPos+cameraDirection, glm::vec3(0.0, 1.0, 0.0));
}


void Engine::Camera::zoom(float deltaFOV) {
	fov += deltaFOV;

	if (fov > 150.0f) {
		fov = 150.0f;
	}

	else if (fov < 10.0f) {
		fov = 10.0f;
	}

	projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}


void Engine::Camera::changeAspectRatio(float ratio) {
	if (ratio < 1.0f) {
		ratio = 1.0f;
	}

	aspectRatio = ratio;

	projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

Engine::Camera::Camera(glm::vec3 position, glm::vec3 target) {

	cameraPos = position;
	cameraDirection = glm::normalize(target - position);

	view = glm::lookAt(cameraPos, target, glm::vec3(0.0, 1.0, 0.0));

	projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}
