#ifndef __BACKGROUND_SKY_H__
#define __BACKGROUND_SKY_H__

#include "GameObject.h"

#include <BitEngine/Texture.h>

class BackgroundSky final : public GameObject
{
public:
	BackgroundSky();
	~BackgroundSky();

	virtual void update() override;
	virtual void render() override;
private:
	float m_x{ 3200.0f };
	float m_y{ 0.0f };
	float m_speed{ 50.0f };

	BE::Texture m_texture;
};

#endif // !__BACKGROUND_SKY_H__


