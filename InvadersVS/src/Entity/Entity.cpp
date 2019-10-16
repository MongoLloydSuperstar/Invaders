#include "Entity.h"

Entity::Entity(Game* game, std::string& fileName, sf::Vector3f position, const float radius, const EntityType type,
               const EntityFaction faction)
	: mGame(game), mRadius(radius), mType(type), mFaction(faction)
{
	mSprite = sf::Sprite(game->GetTexture(fileName));
}

Entity::~Entity()
{
}

void Entity::SetPosition(const sf::Vector2f position)
{
	mSprite.setPosition(position.x, position.y);
}

EntityType Entity::GetType()
{
	return mType;
}

EntityFaction Entity::GetFaction()
{
	return mFaction;
}

sf::Vector2f Entity::GetPosition()
{
	return sf::Vector2f(mSprite.getPosition().x, mSprite.getPosition().y);	
}

sf::Sprite Entity::GetSprite()
{
	return mSprite;
}

void Entity::Kill()
{
	mIsAlive = false;
}

bool Entity::IsAlive()
{
	return mIsAlive;
}
