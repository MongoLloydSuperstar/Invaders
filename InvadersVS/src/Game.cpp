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
static const sf::Vector2i SPAWN_COOLDOWN(1000,2000);
constexpr float RES_X = 768, RES_Y = 1024;
constexpr float SPAWN_START_TIME = 3.0f;


Game::Game()
	: mRenderWindow(sf::VideoMode(RES_X, RES_Y), HEADER), mLastSpawn()
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
	srand((unsigned int)time(nullptr));
	AddEntity(new Player(this, sf::Vector2f(mRenderWindow.getSize().x / 2.0f - GetTexture(Player::GetTextureName()).getSize().x / 2.0f, 800.0f)));	
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

		DrawEntities(EntityType::EFFECT);
		DrawEntities(EntityType::SHIP);
		DrawEntities(EntityType::PROJECTILE);

		mRenderWindow.display();

		TestGameOver();
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

bool Game::IsVisible(Entity* e)
{
	sf::Vector2f ePos = e->GetPosition();
	sf::Vector2u wMax = mRenderWindow.getSize();
	sf::Vector2f wMin = -(sf::Vector2f) e->GetSprite().getTexture()->getSize();

	sf::Vector2f offscreenBuffer(100.0f, 100.0f);
	
	if (ePos.x < wMin.x - offscreenBuffer.x || ePos.x > wMax.x + offscreenBuffer.x)	return false;
	if (ePos.y < wMin.y - offscreenBuffer.y || ePos.y > wMax.y + offscreenBuffer.y)	return false;
	return true;
}

void Game::AddEntity(Entity* entity)
{
	mNewEntities.push_back(entity);
}

void Game::RemoveEntity(Entity* entity)
{
	mOldEntities.push_back(entity);
}

void Game::SetGameOver()
{
	mGameOver = true;
}

void Game::UpdateEntities(const float deltaTime)
{	
	for (Entity* entity : mEntities)
	{
		entity->Update(deltaTime);
		Collisions();
		
		if (!IsVisible(entity)) 
			mOldEntities.push_back(entity);
	}
	
	for (Entity* entity : mNewEntities)
	{
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

bool Game::IsOld(Entity* e)
{
	for (Entity* oldEntity : mOldEntities)
		if (e == oldEntity)	return true;

	return false;
}

void Game::DestroyOldEntities()
{
	Entities remainingEntities;
	
	for (Entity* entity : mEntities)
	{
		if (IsOld(entity))
			delete entity;			
		else
			remainingEntities.push_back(entity);
	}
	mOldEntities.clear();
	mEntities = remainingEntities;	
}

void Game::TestGameOver()
{
	if (mGameOver)
		mRenderWindow.close();
}


bool Game::HasCollided(Entity* e, Entity* o)
{
	float xDist = e->GetSpriteCenterPos().x - o->GetSpriteCenterPos().x;
	float yDist = e->GetSpriteCenterPos().y - o->GetSpriteCenterPos().y;
	float eRad = e->GetRadius();
	float oRad = o->GetRadius();
	
	float distance = sqrt(pow(xDist, 2) + pow(yDist, 2));

	return distance < eRad + oRad ? true : false;
}

void Game::Collisions()
{
	for (Entity* e : mEntities)
	{
		if (e->GetType() == EntityType::EFFECT) continue;
		
		for (Entity* o : mEntities)
		{
			if (!(e->GetFaction() == o->GetFaction() || o->GetType() == EntityType::EFFECT)) {

				if (e->GetType() == EntityType::SHIP && o->GetFaction() == EntityFaction::ENEMY)
				{
					if (HasCollided(e, o))
					{
						e->Collision(); // Always FRIEND Type
						o->Collision(); // Always ENEMY Type
					}
				}
				else if (e->GetType() == EntityType::PROJECTILE && o->GetFaction() == EntityFaction::ENEMY && o->GetType() != EntityType::PROJECTILE)
				{
					if (HasCollided(e, o))
					{
						e->Collision(); // Always FRIEND Type
						o->Collision(); // Always ENEMY Type
					}
				}
			}
		}
	}
}

void Game::SpawnEnemies()
{
	if (mSpawnInvader && (mInvaderTimer.getElapsedTime().asMilliseconds()) > mCooldown)
	{
		sf::Vector2i invaderSize = (sf::Vector2i)GetTexture(Invader::GetTextureName()).getSize();
		unsigned int xRndSpawn = rand() % (mRenderWindow.getSize().x - invaderSize.x);
		int direction = rand() % 2 * 2 - 1;
		
		AddEntity(new Invader(this, sf::Vector2f(xRndSpawn, -(float)invaderSize.y), direction));

		mCooldown = rand() % SPAWN_COOLDOWN.y + SPAWN_COOLDOWN.x;
		mInvaderTimer.restart();
	}
	else if (!mSpawnInvader && mInvaderTimer.getElapsedTime().asMilliseconds() > SPAWN_START_TIME)
	{
		mSpawnInvader = true;
		mInvaderTimer.restart();

		mCooldown = (rand() % SPAWN_COOLDOWN.y) + SPAWN_COOLDOWN.x;
	}
}
