#include "Explosion.h"

const std::string FILENAME = "Explosion.psd";
constexpr float RAD_FACTOR = 1.0f;
constexpr float LIFE_TIME = 0.5f;

Explosion::Explosion(Game* game, const sf::Vector2f position)
	: Entity(game, FILENAME, position, RAD_FACTOR, EntityType::EFFECT, EntityFaction::NEUTRAL)
{
}

Explosion::~Explosion()
{
}

void Explosion::Update(float deltaTime)
{
	if (mLifeTimer.getElapsedTime().asSeconds() > LIFE_TIME)
		mGame->RemoveEntity(this);
}

void Explosion::Collision()
{
}

std::string Explosion::GetTextureName()
{
	return FILENAME;
}
