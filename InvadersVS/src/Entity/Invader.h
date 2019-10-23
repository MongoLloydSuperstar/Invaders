#pragma once
#include "Entity.h"

class Invader final : public Entity
{
public:
	Invader(Game* game, sf::Vector2f position);
	~Invader();

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

