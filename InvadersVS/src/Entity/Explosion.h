#pragma once
#include "Entity.h"

class Explosion final : public Entity
{
public:
	Explosion(Game* game, sf::Vector2f position);
	~Explosion();

	void Update(float deltaTime) override;

	void Collision() override;
private:
	// Functions	


	// Fields


};

