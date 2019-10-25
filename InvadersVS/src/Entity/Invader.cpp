#include "Invader.h"
#include "Bullet.h"
#include <iostream>
#include "Explosion.h"

static const sf::Vector2i SHOT_COOLDOWN(500, 1500);
const std::string FILENAME = "Invader.psd";
constexpr float RAD_FACTOR = 1.0f;
constexpr float SPEED = 200.0f;


Invader::Invader(Game* game, const sf::Vector2f position, const int direction)
	: Entity(game, FILENAME, position, RAD_FACTOR, EntityType::SHIP, EntityFaction::ENEMY)
{
	// Keep directions a value between -1 and 1
	if (direction > 1)
		mDirection = 1;
	else if (direction < -1)
		mDirection = -1;
	else
		mDirection = direction;
}

Invader::~Invader()
{
}

void Invader::Update(const float deltaTime)
{
	Movement(deltaTime);
	Shooting();
}

void Invader::Collision()
{
	mGame->AddEntity(new Explosion(mGame, GetPosition()));
	mGame->RemoveEntity(this);
}

std::string Invader::GetTextureName()
{
	return FILENAME;
}

void Invader::Movement(const float deltaTime)
{
	const float deltaSpeed = SPEED * deltaTime;
	mSprite.move(deltaSpeed * mDirection, deltaSpeed);

	const float xPos = mSprite.getPosition().x;
	const float yPos = mSprite.getPosition().y;

	const float xSize = mSprite.getLocalBounds().width;
	const float xMax = mGame->GetRenderWindow().getSize().x - xSize;
	
	if (xPos < 0)
	{
		mSprite.setPosition(0.0f, yPos);
		mDirection = -mDirection;
	}
	if (xPos > xMax)
	{
		mSprite.setPosition(xMax, yPos);
		mDirection = -mDirection;
	}
}

void Invader::Shooting()
{
	if ((mShootTimer.getElapsedTime().asMilliseconds() - mLastShot) > mShotCooldown)
	{
		const float spawnOffsetX = (mSprite.getPosition().x + mSprite.getTexture()->getSize().x / 2.0f) - (mGame->GetTexture(Bullet::GetTextureName()).getSize().y / 2.0f);
		const float spawnOffsetY = (mSprite.getPosition().y + mSprite.getTexture()->getSize().y) - (mGame->GetTexture(Bullet::GetTextureName()).getSize().y);
		const sf::Vector2f spawnPos = sf::Vector2f(spawnOffsetX, spawnOffsetY);

		mGame->AddEntity(new Bullet(mGame, spawnPos, sf::Vector2f(0, 1), mFaction));

		mShotCooldown = (rand() % SHOT_COOLDOWN.y) + SHOT_COOLDOWN.x;
		mLastShot = mShootTimer.getElapsedTime().asMilliseconds();
	}
}
