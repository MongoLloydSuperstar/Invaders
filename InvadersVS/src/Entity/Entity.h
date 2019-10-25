#pragma once
#include "../Game.h"
#include <SFML/Graphics.hpp>

class Entity
{	
public:
	Entity(Game* game, const std::string& fileName, sf::Vector2f position, float radFactor, EntityType type, EntityFaction faction);
	virtual ~Entity();

	virtual void Update(float deltaTime) = 0;
	virtual void Collision() = 0;
	
	virtual void SetPosition(sf::Vector2f position) final;

	virtual EntityType GetType() final;
	virtual EntityFaction GetFaction() final;
	virtual sf::Vector2f GetPosition() final;
	virtual float GetRadius() final;
	virtual sf::Sprite GetSprite() final;
	virtual const sf::Texture* GetTexture() final;
	virtual sf::Vector2f GetSpriteCenterPos() final;

	virtual void Kill() final;
	virtual bool IsAlive() final;
	
protected:
	Game* mGame;
	float mRadius;
	float mRadFactor;

	EntityType mType;
	EntityFaction mFaction;
	
	sf::Sprite mSprite;

	bool mIsAlive = true;
	
};

