#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(Game* game, std::string& fileName, sf::Vector3f position, float radius, EntityType type, EntityFaction faction);
	~Player();

	void Update(float deltaTime) override;
	void Collision() override;

private:
// Functions	
	void Movement();
	void Shooting();

// Fields
	
	
};

