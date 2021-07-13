#include "GameplayScene.h"
#include "../Systems/PlayerControllerSystem.h"
#include "../Systems/SkySystem.h"
#include "../Systems/TextureRenderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/GravitySystem.h"
#include "../Systems/GrenadeSystem.h"
#include "../Systems/EnemySystem.h"

#include <random>

void GameplayScene::initialize()
{
	// Register all systems
	ecs.registerSystem<GravitySystem>();
	ecs.registerSystem<EnemySystem>();
	ecs.registerSystem<PlayerControllerSystem>();
	ecs.registerSystem<GrenadeSystem>();
	ecs.registerSystem<SkySystem>();
	ecs.registerSystem<TextureRenderSystem>();
	ecs.registerSystem<MovementSystem>();
	ecs.registerSystem<AnimationSystem>();

	// Create entity for sky
	ecs.newEntity<Sky, Position, Texture>({}, { 3200.0f, 0.0f }, "Res/background_sky.png");
	// Create entity for ground
	ecs.newEntity<Texture, Position, Dimension>("Res/ground.png", { 0.0f, 520.0f }, { 800.0f, 80.0f });
	// Create entity for castle
	ecs.newEntity<Texture, Position, Dimension>("Res/castle.png", { 592.0f, 344.0f }, { 208.0f, 256.0f });

	// Setup clouds
	{
		std::mt19937 generator;
		std::uniform_int_distribution<int> distX(-4800, 780);
		std::uniform_int_distribution<int> distY(10, 250);
		std::uniform_int_distribution<int> velocity(15, 30);
		std::uniform_int_distribution<int> cloudTex(0, 2);
		const char *textures[] = { "Res/cloud_1.png", "Res/cloud_2.png", "Res/cloud_3.png" };

		for (int i = 0; i < 50; i++)
		{
			Position p = { (float)distX(generator), (float)distY(generator) };
			Velocity v = { (float)velocity(generator), 0.0f };
			int index = cloudTex(generator);

			ecs.newEntity<Position, Velocity, Dimension, Texture>(p, v, { 80.0f, 50.0f }, textures[index]);
		}
	}

	// Setup enemies
	{
		std::mt19937 generator;
		std::uniform_int_distribution<int> distX(-1024, 0);
		std::uniform_int_distribution<int> distY(490, 535);
		std::uniform_int_distribution<int> velocity(30, 50);

		Animations enemyAnimations;

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

		enemyAnimations.animations.push_back(enemyRunAnimation);
		enemyAnimations.animations.push_back(enemyAttackAnimation);
		enemyAnimations.currentAnimation = 0;

		for (int i = 0; i < 1024 * 128; i++)
		{
			Position p = { (float)distX(generator), (float)distY(generator) };
			Velocity v = { (float)velocity(generator), 0.0f };
			ecs.newEntity<Enemy, Position, Velocity, Texture, Animations, AnimationDimension>({}, p, v, "Res/enemy_sprite.png", enemyAnimations, { 40, 60 });
		}
	}

	// Setup player
	{
		Animations playerAnimations;
		playerAnimations.currentAnimation = 0;

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

		playerAnimations.animations.push_back(playerIdleAnimation);
		playerAnimations.animations.push_back(playerThrowAnimation);
		ecs.newEntity<Player, Texture, Animations, Position, AnimationDimension>({}, "Res/player_sprite.png", playerAnimations, { 695, 327 }, { 60, 40 });
	}

	// explosion: 200:100
	// enemy: 40:60
}

void GameplayScene::shutdown()
{

}
