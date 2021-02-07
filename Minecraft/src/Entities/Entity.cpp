#include "Entity.h"
Entity::Entity() :position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f) {}
Entity::Entity(glm::vec3 position) : position(position), rotation(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f) {}
Entity::Entity(glm::vec3 position, glm::vec3 rotation) : position(position), rotation(rotation), velocity(0.0f, 0.0f, 0.0f) {}
Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity) : position(position), rotation(rotation), velocity(velocity) {}
Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity, glm::vec3 acceleration) : position(position), rotation(rotation), velocity(velocity), acceleration(acceleration) {}

void Entity::setPosition(const glm::vec3& position)
{
	this->position = position;
}

void Entity::setRotation(const glm::vec3& rotation)
{
	this->rotation = rotation;
}

void Entity::setVelocity(const glm::vec3& velocity)
{
	this->velocity = velocity;
}

void Entity::setAcceleration(const glm::vec3& acceleration)
{
	this->acceleration = acceleration;
}


const glm::vec3& Entity::getPosition() const
{
	return position;
}
const glm::vec3& Entity::getRotation() const
{
	return rotation;
}
const glm::vec3& Entity::getVelocity() const
{
	return velocity;
}

const glm::vec3& Entity::getAcceleration() const
{
	return acceleration;
}