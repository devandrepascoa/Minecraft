#pragma once
#include <glm/vec3.hpp>

class Entity
{
private:
	glm::vec3 position, rotation, velocity;
public:
	Entity();
	Entity(glm::vec3 position);
	Entity(glm::vec3 position, glm::vec3 rotation);
	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getVelocity();
};
