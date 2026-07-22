#ifndef MODEL_HPP

#define MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace Engine {

	class Model {

	public:
		Model() = default;//
		~Model();//

		void bindShader(Shader& shaderProgram){ pBoundProgram = &shaderProgram; }

		bool loadModel(const std::string& filePath);//
		bool loadModel(const std::vector<GLfloat>& vertices);//
		bool loadModel(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);//

		bool sendModelBuffer();

		bool freeModel();//

		glm::mat4 getModelMatrix() const { return this->model; }

		bool getLoadingStatus() const { return this->loaded; }


		void setIndices(const std::vector<GLuint>& indices) {
			this->indices = indices;
			this->useIndices = true;
		}
		void translate(const glm::vec3& translationVector) {
			translation = glm::translate(translation, translationVector);
		}
		void scale(const glm::vec3& scaleVector) {
			scalation = glm::scale(scalation, scaleVector);
		}
		void rotate(float angle, const glm::vec3& axis) {
			rotation = glm::rotate(rotation, glm::radians(angle), axis);
		}
		void updateModelMatrix() {
			model = translation * rotation * scalation;
			if(pBoundProgram) pBoundProgram->setMat4("model", model);
		}
		void draw();

	private:
		GLuint modelVAO, modelVBO, modelEBO;

		Shader* pBoundProgram = nullptr;

		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;

		glm::mat4 translation = glm::mat4(1.0f);
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 scalation = glm::mat4(1.0f);

		glm::mat4 model = glm::mat4(1.0f);

		bool loaded = false;
		bool uploaded = false;

		bool useIndices = false;
	};

};

#endif // !MODEL_HPP