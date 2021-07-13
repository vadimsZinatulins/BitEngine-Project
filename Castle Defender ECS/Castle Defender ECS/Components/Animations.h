#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include "../Animation.h"

#include <vector>

struct Animations
{
	std::vector<Animation> animations{};
	int currentAnimation{ 0 };

	void nextAnimation()
	{
		currentAnimation = animations[currentAnimation].nextAnimation;
		animations[currentAnimation].reset();
	}
};

#endif // !__ANIMATIONS_H__
