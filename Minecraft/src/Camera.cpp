#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float near, float far, float fov) :near(near), far(far), fov(fov), viewMatrix(1.0f), projectionMatrix(1.0f) {}
void Camera::updateViewMatrix()
{
	glm::mat4 viewMatrix(1.0f);
	this->viewMatrix =
		glm::rotate(viewMatrix, glm::radians(rotation.x), { 1, 0,0 }) *
		glm::rotate(viewMatrix, glm::radians(rotation.y), { 0, 1,0 }) *
		glm::rotate(viewMatrix, glm::radians(rotation.z), { 0, 0,1 }) *
		glm::translate(viewMatrix, position);
}

void Camera::updateProjectionMatrix(int windowWidth, int windowHeight)
{
	this->projectionMatrix = glm::perspective(glm::radians(fov), ((float)windowWidth) / windowHeight, near, far);
}

void Camera::setPosition(const glm::vec3& position)
{
	Entity::setPosition(position);
	updateViewMatrix();
}

void Camera::setRotation(const glm::vec3& rotation)
{
	Entity::setRotation(rotation);
	updateViewMatrix();
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() const
{
	return viewMatrix;
}
