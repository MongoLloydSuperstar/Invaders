#pragma once
#include "Entity.h"

class Player final : public Entity
{
public:
	Player(Game* game, sf::Vector2f position);
	~Player();

	void Update(float deltaTime) override;
	void Collision() override;

private:
// Functions	
	void Movement(float deltaTime);
	void Shooting();

// Fields
	float mLastShot;
	sf::Clock mShootTimer;
	
};
