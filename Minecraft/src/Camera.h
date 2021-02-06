#pragma once
#include "Entities/Entity.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera :public Entity
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
public:
	float near, far, fov;
	Camera(float near, float far, float fov);
	void updateViewMatrix();
	void updateProjectionMatrix(int windowWidth, int windowHeight);
	void setPosition(const glm::vec3& position) override;
	void setRotation(const glm::vec3& rotation) override;
	
	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrixRotation() const;
	glm::mat4 getViewMatrix() const;
};

