#ifndef __CASTLE_H__
#define __CASTLE_H__

#include "GameObject.h"

#include <BitEngine/Texture.h>

class Castle final : public GameObject
{
public:
	Castle();
	~Castle();

	virtual void update() override;
	virtual void render() override;

private:
	float m_x{ 592.0f };
	float m_y{ 344.0f };
	float m_width{ 208.0f };
	float m_height{ 256.0f };

	BE::Texture m_texture;
};

#endif // !__CASTLE_H__
