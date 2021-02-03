#include "Player.h"
#include "glm/gtc/matrix_transform.hpp"

Player::Player() :camera(100.0f, 1000.0f, 90.0f) {
}

void Player::update(float deltaTime)
{
	position += velocity * deltaTime;
	camera.setPosition(position);
	camera.setRotation(rotation);
	camera.setVelocity(velocity);
}

void Player::setVelocity(const glm::vec3& velocityRelativeCamera)
{
	glm::vec3 velocity(0.0f);
	float yaw = rotation.y;
	float pitch = rotation.x;
	glm::vec3 front(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw)));
	glm::vec3 cameraFront = glm::normalize(front);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	if (velocityRelativeCamera.z != 0)
		velocity += glm::normalize(glm::cross(cameraFront, cameraUp)) * (velocityRelativeCamera.z);
	if (velocityRelativeCamera.x != 0)
		velocity += cameraFront * (velocityRelativeCamera.x);
	if (velocityRelativeCamera.y != 0)
		velocity += cameraUp * (velocityRelativeCamera.y);

	this->velocity = velocity;
}



Camera& Player::getCamera()
{
	return camera;
}
