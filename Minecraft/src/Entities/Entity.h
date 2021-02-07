#pragma once
#include <glm/vec3.hpp>

class Entity
{
protected:
	glm::vec3 position, rotation, velocity,acceleration;
public:
	Entity();
	Entity(glm::vec3 position);
	Entity(glm::vec3 position, glm::vec3 rotation);
	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity);
	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity,glm::vec3 acceleration);

	virtual void setPosition(const glm::vec3& position);
	virtual void setRotation(const glm::vec3& rotation);
	virtual void setVelocity(const glm::vec3& velocity);
	virtual void setAcceleration(const glm::vec3& acceleration);
	const glm::vec3& getPosition() const;
	const glm::vec3& getRotation() const;
	const glm::vec3& getVelocity() const;
	const glm::vec3& getAcceleration() const;
};
