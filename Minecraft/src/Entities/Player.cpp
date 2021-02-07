#include "Player.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Player::Player() :camera(0.1f, 10000.0f, 90.0f), grounded(false), action(PlayerAction::NONE), flying(true) {
}

Player::Player(const glm::vec3 position) : camera(0.1f, 10000.0f, 90.0f), Entity(position), grounded(false), flying(true)
{
}

void Player::update(const ChunkManager& manager, float deltaTime)
{
	velocity += acceleration;

	acceleration = { 0,0,0 };
	if (!grounded && !flying)
		velocity.y -= 20.f * deltaTime;
	grounded = false;
	position.x += velocity.x * deltaTime;
	if (!flying)
		collide(manager, { velocity.x * deltaTime,0,0 });
	position.y += velocity.y * deltaTime;
	if (!flying)
		collide(manager, { 0,velocity.y * deltaTime,0 });
	position.z += velocity.z * deltaTime;
	if (!flying)
		collide(manager, { 0,0,velocity.z * deltaTime });

	if (flying)
		velocity.y *= 0.9f;
	velocity.x *= 0.90f;
	velocity.z *= 0.90f;

	camera.setPosition(glm::vec3(position.x, position.y + dimensions.y / 2, position.z));
	camera.setRotation(rotation);
	camera.setVelocity(velocity * deltaTime);
	camera.setAcceleration(acceleration);
}

void Player::collide(const ChunkManager& chunkManager, const glm::vec3& velocity)
{
	for (int x = position.x - dimensions.x; x < position.x + dimensions.x; x++) {
		for (int y = position.y - dimensions.y; y < position.y + dimensions.y; y++) {
			for (int z = position.z - dimensions.z; z < position.z + dimensions.z;
				z++) {
				auto block = chunkManager.getBlock(glm::vec3(x, y, z));

				if (block != nullptr && block->getType() != BlockType::AIR) {

					if (velocity.y > 0) {
						position.y = y - dimensions.y;
						this->velocity.y = 0;
					}
					else if (velocity.y < 0) {
						grounded = true;
						position.y = y + dimensions.y + 1;
						this->velocity.y = 0;
					}

					if (velocity.x > 0) {
						position.x = x - dimensions.x;
					}
					else if (velocity.x < 0) {
						position.x = x + dimensions.x + 1;
					}

					if (velocity.z > 0) {
						position.z = z - dimensions.z;
					}
					else if (velocity.z < 0) {
						position.z = z + dimensions.z + 1;
					}
				}
			}
		}
	}
}

bool Player::isGrounded()
{
	return grounded;
}

bool Player::isFlying()
{
	return flying;
}

PlayerAction Player::getPlayerAction()
{
	return action;
}

void Player::setPlayerAction(const PlayerAction& action)
{
	this->action = action;
}

void Player::setFlying(bool flying)
{
	this->flying = flying;
}





Camera& Player::getCamera()
{
	return camera;
}
