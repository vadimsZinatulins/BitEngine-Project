#ifndef __BE_ISCENE_H__
#define __BE_ISCENE_H__

#include "ECS.h"

namespace BE
{

struct IScene
{
	IScene() = default;
	virtual ~IScene() = default;

	virtual void initialize() = 0;
	virtual void shutdown() = 0;

	ECS ecs;
};

}

#endif // !__BE_ISCENE_H__
