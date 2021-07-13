#include "GameplayScene.h"
#include "BackgroundSky.h"
#include "Ground.h"
#include "Castle.h"
#include "Cloud.h"
#include "Player.h"
#include "Enemy.h"

#include <random>
#include <algorithm>

std::vector<std::shared_ptr<GameObject>> GameplayScene::objects;
std::vector<Point> GameplayScene::explosionPoints[2];
std::size_t GameplayScene::currentExplosionSet{ 0 };


std::vector<Point> &GameplayScene::getExplosionPoints()
{
	return explosionPoints[currentExplosionSet];
}

void GameplayScene::initialize()
{
	objects.push_back(std::make_shared<BackgroundSky>());
	objects.push_back(std::make_shared<Ground>());
	objects.push_back(std::make_shared<Castle>());

	{
		std::mt19937 generator;
		std::uniform_int_distribution<int> distX(-4800, 780);
		std::uniform_int_distribution<int> distY(10, 250);
		std::uniform_int_distribution<int> velocity(15, 30);
		std::uniform_int_distribution<int> cloudTex(0, 2);
		const char *textures[] = { "Res/cloud_1.png", "Res/cloud_2.png", "Res/cloud_3.png" };

		for (int i = 0; i < 50; i++)
			objects.push_back(std::make_shared<Cloud>((float)distX(generator), (float)distY(generator), (float)velocity(generator), textures[cloudTex(generator)]));
	}

	objects.push_back(std::make_shared<Player>());

	{
		std::mt19937 generator;
		std::uniform_int_distribution<int> distX(-1024, 0);
		std::uniform_int_distribution<int> distY(490, 535);
		std::uniform_int_distribution<int> velocity(30, 50);

		for (int i = 0; i < 1024 * 128; i++)
		{
			objects.push_back(std::make_shared<Enemy>((float)distX(generator), (float)distY(generator), (float)velocity(generator)));
		}
	}
}

void GameplayScene::update()
{
	for (auto object : objects)
	{
		object->update();
	}

	objects.erase(std::remove_if(objects.begin(), objects.end(), [](std::shared_ptr<GameObject> object) { return !object->isAlive; }), objects.end());

	getExplosionPoints().clear();
	currentExplosionSet = (currentExplosionSet + 1) % 2;
}

void GameplayScene::render()
{
	for (auto object : objects)
	{
		object->render();
	}
}

void GameplayScene::shutdown()
{
	objects.clear();
}
