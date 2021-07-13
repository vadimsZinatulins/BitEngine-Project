#ifndef __CLOUD_H__
#define __CLOUD_H__

#include "GameObject.h"

#include <BitEngine/Texture.h>

class Cloud final : public GameObject
{
public:
	Cloud(float x, float y, float velocity, const char *path);
	~Cloud();

	virtual void update() override;
	virtual void render() override;
private:
	float m_x{ 0.0f };
	float m_y{ 0.0f };
	float m_velocity{ 0.0f };
	float m_width{ 80.0f };
	float m_height{ 50.0f };

	BE::Texture m_texture;
};

#endif // !__CLOUD_H__
