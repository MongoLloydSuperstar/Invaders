#include "Explosion.h"

const std::string FILENAME = "Ship.psd";
constexpr float RAD_FACTOR = 1.0f;

Explosion::Explosion(Game* game, const sf::Vector2f position)
	: Entity(game, FILENAME, position, RAD_FACTOR, EntityType::SHIP, EntityFaction::FRIEND)
{
}

Explosion::~Explosion()
{
}

void Explosion::Update(float deltaTime)
{
}

void Explosion::Collision()
{
}
