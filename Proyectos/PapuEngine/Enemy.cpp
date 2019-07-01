#include "Enemy.h"
#include <SDL\SDL.h>

Enemy::Enemy(float agent_width, float agent_height, glm::vec2 position, std::string texture) :
	Agent(agent_width, agent_height, position, texture)
{
}

void Enemy::update()
{
	_position.y -= 8.0f;
}

std::string Enemy::getTexture()
{
	return _texturePath;
}

Enemy::~Enemy()
{
}



