#define MAX_NUM_COMPONENTS 16
//#include <BitEngine/Engine.h>
//#include <BitEngine/Window.h>
//#include <BitEngine/IScene.h>
//#include <BitEngine/SceneManager.h>
//#include <BitEngine/System.h>
//#include <BitEngine/Archetype.h>
//#include <BitEngine/Time.h>
//#include <BitEngine/Texture.h>
//#include <BitEngine/Renderer.h>
//#include <SDL2/SDL.h>

//struct Position
//{
//	float x{ 0.0f };
//	float y{ 0.0f };
//};
//
//struct Scroll
//{
//	float speed{ 0.0f };
//};
//
//struct BackgroundTexture
//{
//	static BE::Texture texture;
//};
//
//BE::Texture BackgroundTexture::texture;
//
//struct ScrollSystem final : public BE::System<Position, Scroll, BackgroundTexture>
//{
//	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes)
//	{
//		for (auto const archetype : archtypes)
//		{
//			Position *positions = archetype->getComponentArray<Position>();
//			Scroll *scrolls = archetype->getComponentArray<Scroll>();
//			for (std::size_t i = 0; i < archetype->count(); i++)
//			{
//				if (positions[i].x > 0)
//				{
//					positions[i].x -= scrolls[i].speed * BE::Time::getInstance().getDeltaTime();
//				}
//			}
//		}
//	}
//
//	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes)
//	{
//		for (auto const archetype : archtypes)
//		{
//			Position *positions = archetype->getComponentArray<Position>();
//			for (std::size_t i = 0; i < archetype->count(); i++)
//			{
//				SDL_Rect srcRect{ (int)positions[i].x, (int)positions[i].y, 800, 600 };
//				SDL_Rect dstRect{ 0, 0, 800, 600 };
//				SDL_RenderCopy(BE::Renderer::getInstance(), BackgroundTexture::texture, &srcRect, &dstRect);
//			}
//		}
//	}
//};

//class Game final : public BE::Engine
//{
//	virtual void initialize() override
//	{
//		BE::Window::getInstance().setTitle("Castle Defender ECS");
//		BE::Window::getInstance().setFrameLimit(60);
//
//		//BE::SceneManager::getInstance().changeScene<GameplayScene>();
//
//		//BackgroundTexture::texture.load("Res/background_sky.png");
//	}
//
//	virtual void shutdown() override
//	{
//	}
//};

#include "Game.h"

int main(int argc, char *argv[])
{
	Game game;
	game.run();

	return 0;
}