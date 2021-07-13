#include "Grenade.h"
#include "GameplayScene.h"
#include "Explosion.h"

#include <BitEngine/Time.h>
#include <BitEngine/KeyInputManager.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Grenade::Grenade(float x, float y) :
	m_x(x),
	m_y(y)
{
	m_texture.load("Res/grenade.png");
}

Grenade::~Grenade()
{
}

void Grenade::update()
{
	float dt = BE::Time::getInstance().getDeltaTime();

	m_dy -= (-720.0f) * dt;

	m_x += m_dx * dt;
	m_y += m_dy * dt;

	if (m_y > 500)
	{
		GameplayScene::objects.push_back(std::make_shared<Explosion>(m_x - 100, m_y - 50));
		GameplayScene::explosionPoints[(GameplayScene::currentExplosionSet + 1) % 2].push_back({ m_x - 100, m_y - 50 });

		isAlive = false;
	}
}

void Grenade::render()
{
	SDL_Rect dstRect{ (int)m_x, (int)m_y, (int)m_width, (int)m_height };
	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, nullptr, &dstRect);
}
