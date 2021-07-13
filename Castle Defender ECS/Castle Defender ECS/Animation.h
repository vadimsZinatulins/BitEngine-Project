#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Frame.h"

#include <vector>

struct Animation
{
	std::vector<Frame> frames{};
	float durationPerFrame{ 0.0f };
	float duration{ 0.0f };
	int nextAnimation{ 0 };
	int currentFrame{ 0 };

	void reset()
	{
		duration = 0.0f;
		currentFrame = 0;
	}

	bool hasEnded()
	{
		return duration > durationPerFrame * frames.size();
	}
};

#endif // !__ANIMATION_H__
