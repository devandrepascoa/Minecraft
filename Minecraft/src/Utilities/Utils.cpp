#include "Utils.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "Opengl Error (" << "0x" << std::hex << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
glm::vec3 leftVector(const glm::vec3& rotation)
{
	float yaw = glm::radians(rotation.y);
	float x = glm::cos(yaw);
	float y = 0;
	float z = glm::sin(yaw);

	return { -x, -y, -z };
}

glm::vec3 rightVector(const glm::vec3& rotation)
{
	return -leftVector(rotation);
}
glm::vec3 forwardsVector(const glm::vec3& rotation)
{
	float yaw = glm::radians(rotation.y + 90);
	float pitch = glm::radians(rotation.x);
	float x = glm::cos(yaw) * glm::cos(pitch);
	float y = glm::sin(pitch);
	float z = glm::cos(pitch) * glm::sin(yaw);

	return { -x, -y, -z };
}

glm::vec3 backwardsVector(const glm::vec3& rotation)
{
	return -forwardsVector(rotation);
}

