#include "Player.h"
#include "Bullet.h"

const std::string FILENAME = "Ship.psd";
constexpr float RAD_FACTOR = 1.0f;
constexpr float SPEED = 300.0f;
constexpr float COOLDOWN = 1.5f;


Player::Player(Game* game, const sf::Vector2f position)
	: Entity(game, FILENAME, position, RAD_FACTOR, EntityType::SHIP, EntityFaction::FRIEND), mLastShot()
{
}

Player::~Player()
{
}

void Player::Update(const float deltaTime)
{
	Movement(deltaTime);
	Shooting();
}

void Player::Collision()
{

}

void Player::Movement(const float deltaTime)
{
	const float xPos = mSprite.getPosition().x;
	const float yPos = mSprite.getPosition().y;

	const float xSize = mSprite.getLocalBounds().width;
	const float ySize = mSprite.getLocalBounds().height;

	const float xMax = mGame->GetRenderWindow().getSize().x - xSize;
	const float yMax = mGame->GetRenderWindow().getSize().y - ySize;

	const float deltaSpeed = SPEED * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && xPos > 0.0f)
	{
		mSprite.move(-deltaSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && xPos < xMax)
	{
		mSprite.move(deltaSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && yPos > 0.0f)
	{
		mSprite.move(0.0f, -deltaSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && yPos < yMax)
	{
		mSprite.move(0.0f, deltaSpeed);
	}

	// Test boundary
	if (xPos < 0)
	{
		mSprite.setPosition(0.0f, yPos);
	}
	if (xPos > xMax)
	{
		mSprite.setPosition(xMax, yPos);
	}
	if (yPos < 0)
	{
		mSprite.setPosition(xPos, 0.0f);
	}
	if (yPos > yMax)
	{
		mSprite.setPosition(xPos, yMax);
	}

}

void Player::Shooting()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (mShootTimer.getElapsedTime().asSeconds() - mLastShot) > COOLDOWN)
	{
		const float spawnOffset = (mSprite.getPosition().x + mSprite.getTexture()->getSize().x / 2.0f) - (mGame->GetTexture("Bullet.psd").getSize().x / 2.0f);
		const sf::Vector2f spawnPos = sf::Vector2f(spawnOffset, mSprite.getPosition().y);
		
		mGame->AddEntity(new Bullet(mGame, spawnPos, sf::Vector2f(0, -1), mFaction));
		mGame->AddEntity(new Bullet(mGame, spawnPos, sf::Vector2f(1, -1), mFaction));
		mGame->AddEntity(new Bullet(mGame, spawnPos, sf::Vector2f(-1, -1), mFaction));

		mLastShot = mShootTimer.getElapsedTime().asSeconds();
	}
}
