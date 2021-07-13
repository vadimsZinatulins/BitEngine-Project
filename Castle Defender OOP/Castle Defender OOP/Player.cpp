#include "Player.h"
#include "GameplayScene.h"
#include "Grenade.h"

#include <BitEngine/Time.h>
#include <BitEngine/KeyInputManager.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Player::Player()
{
	Animation playerIdleAnimation;
	playerIdleAnimation.frames.push_back({ 0, 0, 60, 40 });
	playerIdleAnimation.durationPerFrame = 1.0f;
	playerIdleAnimation.nextAnimation = 0;

	Animation playerThrowAnimation;
	playerThrowAnimation.frames.push_back({ 60, 0, 60, 40 });
	playerThrowAnimation.frames.push_back({ 120, 0, 60, 40 });
	playerThrowAnimation.frames.push_back({ 180, 0, 60, 40 });
	playerThrowAnimation.frames.push_back({ 240, 0, 60, 40 });
	playerThrowAnimation.durationPerFrame = 0.13f;
	playerThrowAnimation.nextAnimation = 0;

	m_animations.push_back(playerIdleAnimation);
	m_animations.push_back(playerThrowAnimation);

	m_texture.load("Res/player_sprite.png");
}

Player::~Player()
{
}

void Player::update()
{
	static bool throwGranade = false;

	BE::KeyInputManager &keyInput = BE::KeyInputManager::getInstance();
	float dt = BE::Time::getInstance().getDeltaTime();
	float speed = 55.0f * dt;

	if (throwGranade && m_currentAnimation == 1 && m_animations[1].currentFrame == 3)
	{
		throwGranade = false;
		GameplayScene::objects.push_back(std::make_shared<Grenade>(m_x, m_y));
	}

	if (keyInput.isKeyDown(BE::Key::KEY_A) && m_x > 620.0f)
	{
		m_x -= speed;
	}

	if (keyInput.isKeyDown(BE::Key::KEY_D) && m_x < 695.0f)
	{
		m_x += speed;
	}

	if (keyInput.isKeyDown(BE::Key::KEY_SPACE) && m_currentAnimation != 1)
	{
		m_currentAnimation = 1;
		m_animations[1].reset();

		throwGranade = true;
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
}

void Player::render()
{
	auto frame = m_animations[m_currentAnimation].frames[m_animations[m_currentAnimation].currentFrame];
	SDL_Rect srcRect = { (int)frame.x, (int)frame.y, (int)frame.width, (int)frame.height };
	SDL_Rect dstRect = { (int)m_x, (int)m_y, (int)m_width, (int)m_height };

	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, &srcRect, &dstRect);
}
