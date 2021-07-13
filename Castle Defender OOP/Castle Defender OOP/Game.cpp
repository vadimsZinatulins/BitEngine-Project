#include "Game.h"
#include "GameplayScene.h"

#include <BitEngine/SceneManager.h>
#include <BitEngine/Window.h>

void Game::initialize()
{
	BE::Window::getInstance().setFrameLimit(60);
	BE::Window::getInstance().setTitle("Castle Defender OOP");

	BE::SceneManager::getInstance().changeScene<GameplayScene>();
}

void Game::shutdown()
{
}
