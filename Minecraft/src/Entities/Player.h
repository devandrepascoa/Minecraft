#pragma once
#include "../Entities/Entity.h"
#include "../Camera.h"

class Player:public Entity
{
private:
	Camera camera;
public:
	Player();
	void update(float deltaTime);
	void setVelocity(const glm::vec3& velocityRelativeCamera) override;
	 Camera& getCamera();
};

