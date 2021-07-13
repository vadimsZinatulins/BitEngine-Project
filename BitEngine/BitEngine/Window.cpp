#include "Window.h"
#include "Renderer.h"
#include "Time.h"

#include <SDL2/SDL.h>

namespace BE
{

SDL_Window *g_window{ nullptr };

Window Window::m_instance;

Window &Window::getInstance()
{
	return m_instance;
}

void Window::setMode(WindowMode mode)
{
	// Set the mode
	m_mode = mode;

	// If the window is already open, change it too
	if (g_window)
	{
		switch (mode)
		{
		case BE::WindowMode::FullScreen:
			SDL_SetWindowFullscreen(g_window, SDL_WINDOW_FULLSCREEN);
			break;
		case BE::WindowMode::Desktop:
			SDL_SetWindowFullscreen(g_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			break;
		default:
			SDL_SetWindowFullscreen(g_window, 0);
			break;
		}

		SDL_SetWindowBordered(g_window, (SDL_bool)(mode != WindowMode::Borderless));
	}
}

void Window::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;

	if (g_window)
	{
		SDL_SetWindowSize(g_window, width, height);
	}
}

void Window::setTitle(std::string title)
{
	m_title = title;

	if (g_window)
	{
		SDL_SetWindowTitle(g_window, title.c_str());
	}
}

void Window::setFrameLimit(unsigned int limit)
{
	Time::getInstance().m_deltaTime = 1.0f / (float)limit;
	m_minTicksPerFrame = 1000 / limit;
}

void Window::open()
{
	// Set flags
	Uint32 windowFlags = SDL_WINDOW_SHOWN;
	switch (m_mode)
	{
	case BE::WindowMode::Borderless:
		windowFlags |= SDL_WINDOW_BORDERLESS;
		break;
	case BE::WindowMode::FullScreen:
		windowFlags |= SDL_WINDOW_FULLSCREEN;
		break;
	case BE::WindowMode::Desktop:
		windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		break;
	}

	// Open the window
	g_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, windowFlags);

	// Initialize Renderer
	Renderer::getInstance().init(g_window);
}

void Window::close()
{
	// Shutdown Renderer
	Renderer::getInstance().quit();

	// Close window if it is open
	if (g_window)
	{
		SDL_DestroyWindow(g_window);
		g_window = nullptr;
	}
}

}
