#include "PlayerControllerSystem.h"

#include "../Components/Grenade.h"
#include "../Components/Texture.h"
#include "../Components/Velocity.h"
#include "../Components/Dimension.h"
#include "../Components/Gravity.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/Time.h>
#include <BitEngine/KeyInputManager.h>
#include <BitEngine/ECS.h>

void PlayerControllerSystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	static bool throwGranade = false;

	BE::KeyInputManager &keyInput = BE::KeyInputManager::getInstance();

	float dt = BE::Time::getInstance().getDeltaTime();
	float speed = 55.0f * dt;

	for (auto const archetype : archtypes)
	{
		Position *positions = archetype->getComponentArray<Position>();
		Animations *animations = archetype->getComponentArray<Animations>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			if (throwGranade && animations[i].currentAnimation == 1 && animations[i].animations[1].currentFrame == 3)
			{
				throwGranade = false; 
				ecs->newEntity<Grenade, Texture, Position, Velocity, Dimension, Gravity>({}, "Res/grenade.png", { positions[i].x, positions[i].y }, { -150.0f, -520.0f }, { 4, 9 }, { -720.0f });
			}

			if (keyInput.isKeyDown(BE::Key::KEY_A) && positions[i].x > 620.0f)
			{
				positions[i].x -= speed;
			}

			if (keyInput.isKeyDown(BE::Key::KEY_D) && positions[i].x < 695.0f)
			{
				positions[i].x += speed;
			}

			if (keyInput.isKeyDown(BE::Key::KEY_SPACE) && animations[i].currentAnimation != 1)
			{
				animations[i].currentAnimation = 1;
				animations[i].animations[1].reset();

				throwGranade = true;
			}
		}
	}
}

void PlayerControllerSystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
}
