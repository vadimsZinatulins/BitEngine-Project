#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"
#include "Animation.h"

#include <BitEngine/Texture.h>
#include <vector>

class Enemy final : public GameObject
{
public:
	Enemy(float x, float y, float velocity);
	~Enemy();

	virtual void update() override;
	virtual void render() override;
private:
	float m_x{ 0.0f };
	float m_y{ 0.0f };
	float m_velocity{ 0.0f };
	float m_width{ 40.0f };
	float m_height{ 60.0f };

	BE::Texture m_texture;

	std::vector<Animation> m_animations{};
	int m_currentAnimation{ 0 };
};

#endif // !__ENEMY_H__



