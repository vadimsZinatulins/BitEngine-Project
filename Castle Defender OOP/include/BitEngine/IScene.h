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
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void shutdown() = 0;
};

}

#endif // !__BE_ISCENE_H__
