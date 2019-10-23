#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class Entity;
enum class EntityType { PROJECTILE, SHIP, EFFECT };
enum class EntityFaction { NEUTRAL, FRIEND, ENEMY };

class TextureResource {
public:
	TextureResource(std::string fileName, sf::Texture& texture);
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

	sf::Texture& GetTexture(const std::string& fileName);
	sf::RenderWindow& GetRenderWindow();

	void AddEntity(Entity* entity);

private:
	typedef std::vector<TextureResource*> TextureResources;
	typedef std::vector<Entity*> Entities;
// Functions
	void UpdateEntities(float deltaTime);
	void DrawEntities(EntityType type);	
	void DestroyOldEntities();

	void SpawnEnemies();

	
// Fields	
	sf::RenderWindow mRenderWindow;
	
	TextureResources mTextureResources;
	Entities mEntities;
	Entities mNewEntities;
	Entities mOldEntities;

	bool mSpawnInvader = false;
	float mLastSpawn;
	sf::Clock mInvaderTimer;

};

