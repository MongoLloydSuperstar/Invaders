#pragma once
#include "../Game.h"
#include <SFML/Graphics.hpp>

class Entity
{	
public:
	Entity(Game* game, std::string& fileName, sf::Vector3f position, float radius, EntityType type, EntityFaction faction);
	virtual ~Entity();

	virtual void Update(float deltaTime) = 0;
	virtual void Collision() = 0;
	
	virtual void SetPosition(sf::Vector2f position) final;

	virtual EntityType GetType() final;
	virtual EntityFaction GetFaction() final;
	virtual sf::Vector2f GetPosition() final;
	virtual sf::Sprite GetSprite() final;

	virtual void Kill();
	virtual bool IsAlive() final;
	
protected:
	Game* mGame;
	float mRadius;
	EntityType mType;
	EntityFaction mFaction;
	
	sf::Sprite mSprite;

	bool mIsAlive = true;
	
};
