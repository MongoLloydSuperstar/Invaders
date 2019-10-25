#include "Entity.h"

Entity::Entity(Game* game, const std::string& fileName, const sf::Vector2f position, const float radFactor, const EntityType type, const EntityFaction faction)
	: mGame(game), mRadFactor(radFactor), mType(type), mFaction(faction)
{
	mSprite = sf::Sprite(game->GetTexture(fileName));
	mRadius = mSprite.getTexture()->getSize().x / 2.0f;
	mSprite.setPosition(position.x, position.y);

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

float Entity::GetRadius()
{
	return mRadius;
}

sf::Sprite Entity::GetSprite()
{
	return mSprite;
}

const sf::Texture* Entity::GetTexture()
{
	return mSprite.getTexture();
}

sf::Vector2f Entity::GetSpriteCenterPos()
{
	float y = GetPosition().y + (mSprite.getTexture()->getSize().y / 2);
	float x = GetPosition().x + (mSprite.getTexture()->getSize().x / 2);
	return sf::Vector2f(x, y);
}

void Entity::Kill()
{
	mIsAlive = false;
}

bool Entity::IsAlive()
{
	return mIsAlive;
}
