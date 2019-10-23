#include "Game.h"
#include <utility>
#include "Entity/Entity.h"
#include "Entity/Player.h"
#include "Entity/Invader.h"
#include "Entity/Bullet.h"

TextureResource::TextureResource(std::string fileName, sf::Texture& texture)
	: mFileName(std::move(fileName)), mTexture(texture)
{
}

TextureResource::~TextureResource()
{
}

std::string& TextureResource::GetFileName()
{
	return mFileName;
}

sf::Texture& TextureResource::GetTexture()
{
	return mTexture;
}

// -----------------------------------------------------------------

static const std::string HEADER = "Invaders";
constexpr float RES_X = 600, RES_Y = 900;
constexpr float SPAWN_START_TIME = 3.0f;
constexpr float SPAWN_COOLDOWN = 1.0f;


Game::Game()
	: mRenderWindow(sf::VideoMode(RES_X,RES_Y), HEADER)
{	
}

Game::~Game()
{
	for (Entity* entity : mEntities)
	{
		delete entity;
	}
	mEntities.clear();
	
	for (Entity* entity : mNewEntities)
	{
		delete entity;
	}
	mNewEntities.clear();

	for (Entity* entity : mOldEntities)
	{
		delete entity;
	}
	mOldEntities.clear();
}

void Game::Run()
{
	AddEntity(new Player(this, sf::Vector2f(100, 500)));	
	sf::Clock updateTimer;
	
	while (mRenderWindow.isOpen())
	{
		sf::Event event{};
		
		while (mRenderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mRenderWindow.close();
			}
		}


		mRenderWindow.clear(sf::Color::Black);

		const float deltaTime = updateTimer.restart().asSeconds();

		SpawnEnemies();
		UpdateEntities(deltaTime);

		DrawEntities(EntityType::PROJECTILE);
		DrawEntities(EntityType::SHIP);
		DrawEntities(EntityType::EFFECT);

		mRenderWindow.display();
	}
}

sf::Texture& Game::GetTexture(const std::string& fileName)
{
	for (TextureResource* textureResource : mTextureResources)
		if (fileName == textureResource->GetFileName())
			return textureResource->GetTexture();

	
	sf::Texture t;	
	t.loadFromFile(fileName);
	TextureResource* tr = new TextureResource(fileName, t);
	mTextureResources.push_back(tr);
	
	return tr->GetTexture();
}

sf::RenderWindow& Game::GetRenderWindow()
{
	return mRenderWindow;
}

void Game::AddEntity(Entity* entity)
{
	mNewEntities.push_back(entity);
}

void Game::UpdateEntities(const float deltaTime)
{
	
	for (Entity* entity : mEntities)
		entity->Update(deltaTime);
		
	for (Entity* entity : mNewEntities)
	{
		//entity->Update(deltaTime);
		mEntities.push_back(entity);
	}
	mNewEntities.clear();
	
	DestroyOldEntities();
}

void Game::DrawEntities(const EntityType type)
{
	for (Entity* entity : mEntities)
	{
		if (entity->GetType() == type)
		mRenderWindow.draw(entity->GetSprite());
	}
}

void Game::DestroyOldEntities()
{
	Entities alive;
	
	for (Entity* entity : mEntities)
	{
		if (entity->IsAlive())
			alive.push_back(entity);
		else
			delete entity;
	}

	mEntities = alive;	
}

void Game::SpawnEnemies()
{
	
	if (mSpawnInvader && (mInvaderTimer.getElapsedTime().asSeconds())> SPAWN_COOLDOWN)
	{
		AddEntity(new Invader(this, sf::Vector2f(100, 100)));
		mInvaderTimer.restart();
	}
	else if (!mSpawnInvader && mInvaderTimer.getElapsedTime().asSeconds() > SPAWN_START_TIME)
	{
		mSpawnInvader = true;
		mInvaderTimer.restart();
	}
}
