#pragma once
#include <glm/vec3.hpp>
#include "Entity.h"

class Cube : public Entity {
public:
	Cube(glm::vec3 position);
};