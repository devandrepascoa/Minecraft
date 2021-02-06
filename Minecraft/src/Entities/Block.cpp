#include "Block.h"



Block::Block():type(BlockType::AIR),focus(false){
}

Block::Block(glm::vec3 position, BlockType type) :type(type), Entity(position),focus(false) {
}

BlockType Block::getType() const
{
	return type;
}

bool Block::getFocus() const
{
	return focus;
}

void Block::setFocus(bool focus)
{
 	this->focus = focus;
}

void Block::setType(BlockType type)
{
	this->type = type;
}
