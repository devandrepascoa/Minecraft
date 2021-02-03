#include "Block.h"

Block::Block() : type(BlockType::AIR) {}

Block::Block(BlockType type) : type(type){}

BlockType Block::getType() const
{
	return type;
}
