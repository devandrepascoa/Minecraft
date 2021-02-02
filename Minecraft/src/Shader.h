#pragma once
#include <string>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

enum class ShaderType {
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

class Shader {
private:
	unsigned int rendererId;
public:
	Shader(const std::string& sourceFilePath);
	~Shader();

	void setUniformMatrix4FV(const std::string& name, const glm::mat4 mat) const;
	void setUniform4F(const std::string& name, const glm::vec4 vec) const;
	void setUniform3F(const std::string& name, const glm::vec3 vec) const;
	void setUniform2F(const std::string& name, const glm::vec2 vec) const;
	void setUniform1F(const std::string& name, float x) const;


	void bind() const;
	void unBind() const;
};