#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "GameObject.h"

#include <BitEngine/IScene.h>
#include <vector>
#include <memory>

struct Point
{
	float x{ 0.0f };
	float y{ 0.0f };
};

struct GameplayScene final : public BE::IScene
{
	virtual void initialize() override;
	virtual void update() override;
	virtual void render() override;
	virtual void shutdown() override;

	static std::vector<Point> &getExplosionPoints();

	static std::vector<std::shared_ptr<GameObject>> objects;
	static std::vector<Point> explosionPoints[2];
	static std::size_t currentExplosionSet;
};

#endif // !__GAMEPLAY_SCENE_H__
