#include "Entity.h"
Entity::Entity() :position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f) {}
Entity::Entity(glm::vec3 position) : position(position), rotation(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f) {}
Entity::Entity(glm::vec3 position, glm::vec3 rotation) : position(position), rotation(rotation), velocity(0.0f, 0.0f, 0.0f) {}
Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity) : position(position), rotation(rotation), velocity(velocity) {}

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


glm::vec3 Entity::getPosition()
{
	return position;
}
glm::vec3 Entity::getRotation()
{
	return rotation;
}
glm::vec3 Entity::getVelocity()
{
	return velocity;
}

