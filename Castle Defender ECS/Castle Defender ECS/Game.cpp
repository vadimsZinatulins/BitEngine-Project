#include "Game.h"
#include "Scenes/GameplayScene.h"

#include <BitEngine/Window.h>
#include <BitEngine/SceneManager.h>
#include <SDL2/SDL.h>

void Game::initialize()
{
	BE::Window::getInstance().setTitle("Castle Defender ECS");
	BE::Window::getInstance().setFrameLimit(60);

	BE::SceneManager::getInstance().changeScene<GameplayScene>();
}

void Game::shutdown()
{
}
