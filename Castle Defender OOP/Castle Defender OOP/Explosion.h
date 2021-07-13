#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "GameObject.h"
#include "Animation.h"

#include <BitEngine/Texture.h>
#include <vector>

class Explosion final : public GameObject
{
public:
	Explosion(float x, float y);
	~Explosion();

	virtual void update() override;
	virtual void render() override;

private:
	float m_x{ 0.0f };
	float m_y{ 0.0f };
	float m_width{ 200.0f };
	float m_height{ 100.0f };

	BE::Texture m_texture;

	std::vector<Animation> m_animations{};
	int m_currentAnimation{ 0 };
};

#endif // !__EXPLOSION_H__
