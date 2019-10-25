#pragma once
#include "Entity.h"

class Bullet final : public Entity
{
public:
	Bullet(Game* game, sf::Vector2f position, sf::Vector2f direction, EntityFaction faction);
	~Bullet();

	void Update(float deltaTime) override;
	void Collision() override;
	static std::string GetTextureName();

private:
	// Functions	
	void Movement(float deltaTime);
	void Shooting();

	// Fields
	sf::Vector2f mDirection;

};

