#include "Explosion.h"

#include <BitEngine/Time.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Explosion::Explosion(float x, float y) :
	m_x(x),
	m_y(y)
{
	Animation mainAnimation;
	mainAnimation.frames.push_back({ 0, 0, 200, 100 });
	mainAnimation.frames.push_back({ 200, 0, 200, 100 });
	mainAnimation.frames.push_back({ 400, 0, 200, 100 });
	mainAnimation.frames.push_back({ 600, 0, 200, 100 });
	mainAnimation.frames.push_back({ 800, 0, 200, 100 });
	mainAnimation.frames.push_back({ 1000, 0, 200, 100 });
	mainAnimation.durationPerFrame = 0.05f;

	m_animations.push_back(mainAnimation);

	m_texture.load("Res/explosion_sprite.png");
}

Explosion::~Explosion()
{
}

void Explosion::update()
{
	float dt = BE::Time::getInstance().getDeltaTime();

	if (m_animations[m_currentAnimation].hasEnded())
	{
		isAlive = false;
	}
	else
	{
		m_animations[m_currentAnimation].duration += dt;
		m_animations[m_currentAnimation].currentFrame = (int)(m_animations[m_currentAnimation].duration / m_animations[m_currentAnimation].durationPerFrame);
		if (m_animations[m_currentAnimation].currentFrame > m_animations[m_currentAnimation].frames.size() - 1)
		{
			m_animations[m_currentAnimation].currentFrame = 0;
		}
	}
}

void Explosion::render()
{
	auto frame = m_animations[m_currentAnimation].frames[m_animations[m_currentAnimation].currentFrame];
	SDL_Rect srcRect = { (int)frame.x, (int)frame.y, (int)frame.width, (int)frame.height };
	SDL_Rect dstRect = { (int)m_x, (int)m_y, (int)m_width, (int)m_height };

	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, &srcRect, &dstRect);
}
