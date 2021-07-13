#ifndef __GRENADE_H__
#define __GRENADE_H__

#include "GameObject.h"

#include <BitEngine/Texture.h>

class Grenade final : public GameObject
{
public:
	Grenade(float x, float y);
	~Grenade();

	virtual void update() override;
	virtual void render() override;
private:
	float m_x{ 0.0f };
	float m_y{ 0.0f };
	float m_dx{ -150.0f };
	float m_dy{ -520.0f };
	float m_width{ 4.0f };
	float m_height{ 9.0f };

	BE::Texture m_texture;
};

#endif // !__GRENADE_H__
