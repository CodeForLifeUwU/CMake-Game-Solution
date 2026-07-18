#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/gl.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Engine::Shader
{
private:
	inline static GLuint currentProgram = 0;
public:
	
	// constructor reads and builds the shader
	Shader(std::string name, const char* vertexPath, const char* fragmentPath);//
	~Shader();//

	bool checkSuccess();//

	const char* getName() { return this->name.c_str(); }
	
	void use();//
	
	void setBool(const std::string& name, bool value);//
	void setInt(const std::string& name, int value);//
	void setFloat(const std::string& name, float value);//
	void setVec3(const std::string& name, const glm::vec3& value);//
	void setMat4(const std::string& name, const glm::mat4& mat);//

	void setHints(std::vector<GLuint> hints);
	std::vector<GLuint> getHints() const { return hints; }

private:
	std::string name;
	// the program ID
	GLuint ID;
	char infolog[512];

	// Compilation status
	GLint success = 0;

	// Spacing hints
	std::vector<GLuint> hints = {};
};
#endif