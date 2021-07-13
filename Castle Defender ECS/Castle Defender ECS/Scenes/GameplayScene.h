#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include <BitEngine/IScene.h>

struct GameplayScene final : public BE::IScene
{
	virtual void initialize() override;
	virtual void shutdown() override;
};

#endif // !__GAMEPLAY_SCENE_H__
