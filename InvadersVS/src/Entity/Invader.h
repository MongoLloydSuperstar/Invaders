#pragma once
#include "Entity.h"

class Invader final : public Entity
{
public:
	Invader(Game* game, sf::Vector2f position, int direction);
	~Invader();

	void Update(float deltaTime) override;
	void Collision() override;
	static std::string GetTextureName();

private:
	// Functions	
	void Movement(float deltaTime);
	void Shooting();

	// Fields
	int mDirection;
	float mLastShot;
	sf::Clock mShootTimer;
	float mShotCooldown;
};

