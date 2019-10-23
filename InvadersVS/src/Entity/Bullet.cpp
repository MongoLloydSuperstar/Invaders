#include "Bullet.h"

const std::string FILENAME = "Bullet.psd";
constexpr float RAD_FACTOR = 1.0f;
constexpr float SPEED = 600.0f;

Bullet::Bullet(Game* game, const sf::Vector2f position, const sf::Vector2f direction, const EntityFaction faction)
	: Entity(game, FILENAME, position, RAD_FACTOR, EntityType::PROJECTILE, faction)
{
	// Keep directions a value between -1 and 1
	if (direction.x > 1)
		mDirection.x = 1;
	else if (direction.x < -1)
		mDirection.x = -1;
	else
		mDirection.x = direction.x;
			
	if (direction.y > 1)
		mDirection.y = 1;
	else if (direction.y < -1)
		mDirection.y = -1;
	else
		mDirection.y = direction.y;
}

Bullet::~Bullet()
{
}

void Bullet::Update(const float deltaTime)
{
	Movement(deltaTime);
}

void Bullet::Collision()
{
}

void Bullet::Movement(const float deltaTime)
{
	mSprite.move(mDirection.x * SPEED * deltaTime, mDirection.y * SPEED * deltaTime);
}

void Bullet::Shooting()
{
}
