#include "Engine.hpp"

// ==================== Model Implementation ====================

// Loading model
bool Engine::Model::loadModel(const std::vector<GLfloat>& vertices) {
	if (vertices.size() == 0) {
		std::cerr << "Invalid model. Empty array." << std::endl;
		return false;
	}
	// Load model data from the provided vertices
	this->vertices = vertices;
	this->loaded = true;
	return true;
}

bool Engine::Model::loadModel(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
	if (vertices.size() == 0) {
		std::cerr << "Invalid model. Empty vertex array." << std::endl;
		return false;
	}
	if (indices.size() == 0) {
		std::cerr << "Invalid model. Empty index array." << std::endl;
		return false;
	}
	// Load model data from the provided vertices and indices
	this->vertices = vertices;
	this->indices = indices;
	this->loaded = true;
	this->useIndices = true;
	return true;
}


bool Engine::Model::sendModelBuffer() {
	if (uploaded == true) {
		std::cerr << "Model is already present in the buffer." << std::endl;
		return false;
	}
	if (loaded == false) {
		std::cerr << "No valid model present." << std::endl;
		return false;
	}

	glGenVertexArrays(1, &modelVAO);

	glGenBuffers(1, &modelVBO);
	glGenBuffers(1, &modelEBO);

	glBindVertexArray(modelVAO);

	glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	if(useIndices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	uploaded = true;
	return true;
}


void Engine::Model::draw(){
	if (!pBoundProgram) {
		std::cerr << "No shader program bound to model" << std::endl;
		return;
	}

	pBoundProgram->use();
	// pBoundProgram->setMat4("model", model);

	// for (auto& mesh : meshes) {
	// 	mesh.draw(pBoundProgram);
	// }
	if(useIndices){
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5);
}


// Removing model
bool Engine::Model::freeModel() {
	if (uploaded) {
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &modelVAO);

		glDeleteBuffers(1, &modelVBO);

		if(this->useIndices) {
			glDeleteBuffers(1, &modelEBO);
		}
		this->uploaded = false;
	}
	if(loaded)
	{
		this->vertices.clear();
		this->vertices.shrink_to_fit();

		if (this->useIndices) {
			this->indices.clear();
			this->indices.shrink_to_fit();
		}
		this->useIndices = false;
		this->loaded = false;

		std::cout << "Model removed successfully" << std::endl;
		return true;
	}
	else {
		std::cerr << "No model is loaded yet." << std::endl;
		return false;
	}
}

Engine::Model::~Model() {
	this->freeModel();
}
