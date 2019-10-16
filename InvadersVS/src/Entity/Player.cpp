#include "Player.h"

Player::Player(Game* game, std::string& fileName, const sf::Vector3f position, const float radius, const EntityType type, const EntityFaction faction)
	: Entity(game, fileName, position, radius, type, faction)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	
}

void Player::Collision()
{
	
}

void Player::Movement()
{
}

void Player::Shooting()
{
}
