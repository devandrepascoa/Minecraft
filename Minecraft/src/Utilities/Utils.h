#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#define ASSERT(x) if(!x) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
glm::vec3 backwardsVector(const glm::vec3& rotation);
glm::vec3 forwardsVector(const glm::vec3& rotation);
glm::vec3 rightVector(const glm::vec3& rotation);
glm::vec3 leftVector(const glm::vec3& rotation);
