#pragma once
#include "../Entities/Entity.h"
#include "../Camera.h"
#include "../Chunk/ChunkManager.h"

const static glm::vec3 dimensions = { 0.3f, 1.5f, 0.3f };
enum class PlayerAction {
	DESTROY, PLACE, NONE
};
class Player :public Entity
{
private:
	Camera camera;
	bool grounded;
	bool flying;
	PlayerAction action;

public:
	Player();
	Player(const glm::vec3 position);
	void update(const ChunkManager& chunkManager, float deltaTime);
	void collide(const ChunkManager& chunkManager, const glm::vec3& velocity);
	bool isGrounded();
	bool isFlying();
	PlayerAction getPlayerAction();
	void setPlayerAction(const PlayerAction& action);
	void setFlying(bool flying);
	Camera& getCamera();
};

