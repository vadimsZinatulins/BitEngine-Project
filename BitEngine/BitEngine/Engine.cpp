#include "Engine.h"
#include "Window.h"
#include "Renderer.h"
#include "KeyInputManager.h"
#include "Time.h"
#include "TextureManager.h"
#include "TaskScheduler.h"
#include "MouseInputManager.h"
#include "SceneManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Profiler/Profiler.h>
#include <Profiler/Timer.h>

namespace BE
{

void Engine::run()
{
	init();
	loop();
	quit();
}

void Engine::init()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	// Initialize SDL_image
	IMG_Init(IMG_INIT_PNG);

	// Open the window
	Window::getInstance().open();

	TaskScheduler::getInstance().initialize();
}

void Engine::loop()
{
	Benchmark::Profiler::getInstance().beginSession("Measurements");

	Time &time = Time::getInstance();
	Window &window = Window::getInstance();
	Renderer &renderer = Renderer::getInstance();
	KeyInputManager &keyInput = KeyInputManager::getInstance();
	MouseInputManager &mouse = MouseInputManager::getInstance();
	SceneManager &sceneManager = SceneManager::getInstance();

	// These two are used to calculate the delta time between frames
	Uint32 currentFrame = SDL_GetTicks();
	Uint32 previousFrame = currentFrame;

	// The accumulated delta times
	float accumulated = 0.0f;

	// Initializer defined by child class
	initialize();

	SDL_Event e;
	sceneManager.updateSceneState();

	while (sceneManager.isRunning())
	{
		Benchmark::Timer timer("Frame");

		// Calculate the delta time and add it to the accumulated value
		currentFrame = SDL_GetTicks();
		accumulated += (float)(currentFrame - previousFrame) / 1000.0f;
		previousFrame = currentFrame;

		// Update keys input
		keyInput.update();

		// Update cursor
		mouse.update();

		// Process all SDL events
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				sceneManager.quit();
				break;
			case SDL_KEYDOWN:
				keyInput.keyPressed(static_cast<Key>(e.key.keysym.scancode));
				break;
			case SDL_KEYUP:
				keyInput.keyReleased(static_cast<Key>(e.key.keysym.scancode));
				break;
			case SDL_MOUSEMOTION:
				mouse.setMouseCoords({ e.motion.x ,e.motion.y });
				mouse.setMouseRelCoords({ e.motion.xrel , e.motion.yrel });
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.buttonPressed(static_cast<MouseButton>(e.button.button));
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.buttonReleased(static_cast<MouseButton>(e.button.button));
				break;
			case SDL_MOUSEWHEEL:
				mouse.setWheelMotion(static_cast<MouseWheel>(e.wheel.y));
			}
		}

		auto scene = sceneManager.getCurrentScene();

		// Semi-fixed time step
		while (accumulated >= time.m_deltaTime)
		{
			scene->ecs.update();
			accumulated -= time.m_deltaTime;
			time.m_time += time.m_deltaTime;
		}

		// Clear the renderer
		SDL_RenderClear(renderer);

		scene->ecs.render();

		// Render the renderer
		SDL_RenderPresent(renderer);

		sceneManager.updateSceneState();

		// Calculate frame ticks
		Uint32 frameTicks = SDL_GetTicks() - currentFrame;
		// If frame ticks are less than minimum frame ticks then wait some time
		if (frameTicks < window.m_minTicksPerFrame)
		{
			SDL_Delay(window.m_minTicksPerFrame - frameTicks);
		}
	}

	// Shutdown defined by child class
	shutdown();

	TextureManager::getInstance().clear();

	Benchmark::Profiler::getInstance().endSession();
}

void Engine::quit()
{
	TaskScheduler::getInstance().shutdown();

	// Close the window
	Window::getInstance().close();

	// Shutdown SDL_image
	IMG_Quit();

	// Shutdown SDL
	SDL_Quit();
}

}