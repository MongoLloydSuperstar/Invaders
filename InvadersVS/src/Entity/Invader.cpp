#include "Invader.h"
#include "Bullet.h"

const std::string FILENAME = "Invader.psd";
constexpr float RAD_FACTOR = 1.0f;
constexpr float SPEED = 200.0f;
constexpr float COOLDOWN = 1.5f;

Invader::Invader(Game* game, const sf::Vector2f position)
	: Entity(game, FILENAME, position, RAD_FACTOR, EntityType::SHIP, EntityFaction::ENEMY)
{
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
}

void Invader::Movement(const float deltaTime)
{
	const float deltaSpeed = SPEED * deltaTime;
	mSprite.move(0.0f, deltaSpeed);
}

void Invader::Shooting()
{
	if ((mShootTimer.getElapsedTime().asSeconds() - mLastShot) > COOLDOWN)
	{
		const float spawnOffsetX = (mSprite.getPosition().x + mSprite.getTexture()->getSize().x / 2.0f) - (mGame->GetTexture("Bullet.psd").getSize().x / 2.0f); // TODO: Get Texture name from Bullet
		const float spawnOffsetY = (mSprite.getPosition().y + mSprite.getTexture()->getSize().y) - (mGame->GetTexture("Bullet.psd").getSize().y);
		const sf::Vector2f spawnPos = sf::Vector2f(spawnOffsetX, spawnOffsetY);

		mGame->AddEntity(new Bullet(mGame, spawnPos, sf::Vector2f(0, 1), mFaction));

		mLastShot = mShootTimer.getElapsedTime().asSeconds();
	}
}
