#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"
#include "Animation.h"

#include <BitEngine/Texture.h>
#include <vector>

class Player final : public GameObject
{
public:
	Player();
	~Player();

	virtual void update() override;
	virtual void render() override;
private:
	float m_x{ 695.0f };
	float m_y{ 327.0 };
	float m_width{ 60.0f };
	float m_height{ 40.0f };

	BE::Texture m_texture;

	std::vector<Animation> m_animations{};
	int m_currentAnimation{ 0 };
};


#endif // !__PLAYER_H__

