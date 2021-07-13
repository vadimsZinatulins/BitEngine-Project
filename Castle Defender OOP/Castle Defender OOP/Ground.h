#ifndef __GROUND_H__
#define __GROUND_H__

#include "GameObject.h"

#include <BitEngine/Texture.h>

class Ground final : public GameObject
{
public:
	Ground();
	~Ground();

	virtual void update() override;
	virtual void render() override;
private:
	float m_x{ 0.0f };
	float m_y{ 520.0f };
	float m_width{ 800.0f };
	float m_height{ 80.0f };

	BE::Texture m_texture;
};

#endif // !__GROUND_H__
