#include "Shader.h"
#include <glad/glad.h>
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <array>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

unsigned int compileShader(unsigned int type, const std::string& source) {

	GLCall(unsigned int id = glCreateShader(type));
	const char* c_src = source.c_str();
	GLCall(glShaderSource(id, 1, &c_src, NULL));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int message_length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &message_length));
		char* message = (char*)malloc(message_length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, message_length, &message_length, message));
		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << " shader"
			<< std::endl << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

std::array < std::string, 2> parseShader(const std::string& shaderSourceFilePath) {
	std::ifstream shaderSourceFile(shaderSourceFilePath);
	std::string line;
	ShaderType type = ShaderType::NONE;

	std::stringstream shaders[2];
	while (std::getline(shaderSourceFile, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			shaders[(int)type] << line << "\n";
		}
	}
	shaderSourceFile.close();
	return { shaders[(int)ShaderType::VERTEX].str(),shaders[(int)ShaderType::FRAGMENT].str() };
}


Shader::Shader(const std::string& sourceFilePath)
{
	std::array<std::string, 2> shaderSources = parseShader(sourceFilePath);

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, shaderSources[(int)ShaderType::VERTEX]);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderSources[(int)ShaderType::FRAGMENT]);
	GLCall(rendererId = glCreateProgram());

	GLCall(glAttachShader(rendererId, vertexShader));
	GLCall(glAttachShader(rendererId, fragmentShader));
	GLCall(glLinkProgram(rendererId));

	int result;
	GLCall(glGetProgramiv(rendererId, GL_LINK_STATUS, &result));
	if (result == GL_FALSE) {
		int message_length;
		GLCall(glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &message_length));
		char* message = (char*)malloc(message_length * sizeof(char));
		GLCall(glGetProgramInfoLog(rendererId, message_length, &message_length, message));
		std::cout << "Failed to create shader program " << std::endl << message << std::endl;
		GLCall(glDeleteProgram(rendererId));
		ASSERT(false);
	}

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(rendererId));
}

void Shader::setUniformMatrix4FV(const std::string& name, const glm::mat4 mat) const
{
	this->bind();
	GLCall(int location = glGetUniformLocation(rendererId, name.c_str()));
	GLCall(glUniformMatrix4fv(location, 1,GL_FALSE,glm::value_ptr(mat)));
}

void Shader::setUniform4F(const std::string& name, const glm::vec4 vec) const
{
	this->bind();
	GLCall(int location = glGetUniformLocation(rendererId, name.c_str()));
	GLCall(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
}
void Shader::setUniform3F(const std::string& name, const glm::vec3 vec) const
{
	this->bind();
	GLCall(int location = glGetUniformLocation(rendererId, name.c_str()));
	GLCall(glUniform3f(location, vec.x, vec.y, vec.z));
}
void Shader::setUniform2F(const std::string& name, const glm::vec2 vec) const
{
	this->bind();
	GLCall(int location = glGetUniformLocation(rendererId, name.c_str()));
	GLCall(glUniform2f(location, vec.x, vec.y));
}
void Shader::setUniform1F(const std::string& name, float x) const
{
	this->bind();
	GLCall(int location = glGetUniformLocation(rendererId, name.c_str()));
	GLCall(glUniform1f(location, x));
}


void Shader::bind() const
{
	GLCall(glUseProgram(rendererId));
}

void Shader::unBind() const
{
	GLCall(glUseProgram(0));
}
