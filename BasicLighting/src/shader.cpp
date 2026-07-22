#include "Engine.hpp"

#include <glad/gl.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <filesystem>

bool Engine::Shader::checkSuccess() {
	return success == GL_TRUE;
}

void Engine::Shader::use() {
	if (currentProgram == this->ID) {
		return;
	}
	glUseProgram(this->ID);
	currentProgram = this->ID;
}

void Engine::Shader::setBool(const std::string& name, bool value) {

	this->use();
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniform1i(location, (int)value);
}

void Engine::Shader::setInt(const std::string& name, int value) {

	this->use();
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniform1i(location, value);
}

void Engine::Shader::setFloat(const std::string& name, float value) {

	this->use();
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniform1f(location, value);
}

void Engine::Shader::setVec3(const std::string& name, const glm::vec3& value) {

	this->use();
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}


void Engine::Shader::setMat4(const std::string& name, const glm::mat4& mat) {

	this->use();
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}


void Engine::Shader::setHints(std::vector<GLuint> hints) {
	this->hints = hints;
}




Engine::Shader::Shader(std::string name, const char* vertexPath, const char* fragmentPath)
{
	this->name = name;
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		

std::cout << "Current working directory: "
          << std::filesystem::current_path() << '\n';

std::cout << "Vertex exists? "
          << std::filesystem::exists(vertexPath) << '\n';

std::cout << "Fragment exists? "
          << std::filesystem::exists(fragmentPath) << '\n';
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cout << e.what() << std::endl;
		success = GL_FALSE;
		return;
	}

	// Compiling Shaders
	//Compiling vertex shader
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << infolog << std::endl;
		return;
	}

	// Compiling fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << infolog << std::endl;
		return;
	}

	// Linking both shaders to a program
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << infolog << std::endl;
		return;
	}

	this->ID = shaderProgram;


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return;
}

Engine::Shader::~Shader() {
	if (this->checkSuccess()) {

		glDeleteProgram(this->ID);
	}
}