#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class Entity;
enum class EntityType { PROJECTILE, SHIP, EFFECT };
enum class EntityFaction { NEUTRAL, FRIEND, ENEMY };

class TextureResource {
public:
	TextureResource(std::string& fileName, sf::Texture& texture);
	~TextureResource();

	std::string& GetFileName();
	sf::Texture& GetTexture();

private:
	std::string mFileName;
	sf::Texture mTexture;
};

class Game
{
public:
	Game();
	~Game();

	void Run();

	sf::Texture& GetTexture(std::string& fileName);
	sf::RenderWindow& GetRenderWindow();

	void AddEntity(Entity* entity);

private:
	typedef std::vector<TextureResource*> TextureResources;
	typedef std::vector<Entity*> Entities;
// Functions
	void UpdateEntities();
	void DrawEntities(EntityType type);
	
	void DestroyOldEntities();
	

// Fields	
	sf::RenderWindow mRenderWindow;
	sf::Clock mClock;
	
	TextureResources mTextureResources;
	Entities mEntities;
	Entities mNewEntities;
	Entities mOldEntities;	

};

