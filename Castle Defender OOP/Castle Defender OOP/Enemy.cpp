#include "Enemy.h"
#include "GameplayScene.h"

#include <BitEngine/Time.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Enemy::Enemy(float x, float y, float velocity) : 
	m_x(x),
	m_y(y),
	m_velocity(velocity)
{
	Animation enemyRunAnimation;
	enemyRunAnimation.frames.push_back({ 0, 0, 40, 60 });
	enemyRunAnimation.frames.push_back({ 40, 0, 40, 60 });
	enemyRunAnimation.frames.push_back({ 80, 0, 40, 60 });
	enemyRunAnimation.frames.push_back({ 120, 0, 40, 60 });
	enemyRunAnimation.nextAnimation = 0;
	enemyRunAnimation.durationPerFrame = 0.13f;

	Animation enemyAttackAnimation;
	enemyAttackAnimation.frames.push_back({ 160, 0, 40, 60 });
	enemyAttackAnimation.frames.push_back({ 200, 0, 40, 60 });
	enemyAttackAnimation.frames.push_back({ 240, 0, 40, 60 });
	enemyAttackAnimation.nextAnimation = 1;
	enemyAttackAnimation.durationPerFrame = 0.13f;

	m_animations.push_back(enemyRunAnimation);
	m_animations.push_back(enemyAttackAnimation);

	m_texture.load("Res/enemy_sprite.png");
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	float dt = BE::Time::getInstance().getDeltaTime();

	if (m_x >= 575)
	{
		m_x = 575;
		m_currentAnimation = 1;
	}
	else
	{
		m_x += m_velocity * dt;
	}

	if (m_animations[m_currentAnimation].hasEnded())
	{
		m_currentAnimation = m_animations[m_currentAnimation].nextAnimation;
		m_animations[m_currentAnimation].reset();
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

	for (auto grenadePosition : GameplayScene::getExplosionPoints())
	{
		if (m_x > grenadePosition.x - 150 && m_x < grenadePosition.x + 150)
		{
			isAlive = false;
		}
	}
}

void Enemy::render()
{
	auto frame = m_animations[m_currentAnimation].frames[m_animations[m_currentAnimation].currentFrame];
	SDL_Rect srcRect = { (int)frame.x, (int)frame.y, (int)frame.width, (int)frame.height };
	SDL_Rect dstRect = { (int)m_x, (int)m_y, (int)m_width, (int)m_height };

	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, &srcRect, &dstRect);
}
