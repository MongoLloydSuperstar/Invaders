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
	
	bool IsVisible(Entity* e);
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	void SetGameOver();

private:
	typedef std::vector<TextureResource*> TextureResources;
	typedef std::vector<Entity*> Entities;
	
// Functions
	void UpdateEntities(float deltaTime);
	void DrawEntities(EntityType type);
	bool HasCollided(Entity* e, Entity* o);
	void Collisions();

	void SpawnEnemies();

	bool IsOld(Entity* e);
	void DestroyOldEntities();

	void TestGameOver();

	
// Fields	
	sf::RenderWindow mRenderWindow;
	
	TextureResources mTextureResources;
	Entities mEntities;
	Entities mNewEntities;
	Entities mOldEntities;

	bool mSpawnInvader = false;
	float mLastSpawn;
	sf::Clock mInvaderTimer;
	float mCooldown;

	bool mGameOver = false;
};

