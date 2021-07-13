#ifndef __BE_RENDERER_H__
#define __BE_RENDERER_H__

struct SDL_Renderer;
struct SDL_Window;

namespace BE
{

class Renderer
{
public:
	static Renderer &getInstance();

	operator SDL_Renderer *() const;

	void init(SDL_Window *window);
	void quit();
private:
	Renderer() = default;
	~Renderer() = default;

	static Renderer m_instance;

	SDL_Renderer *m_renderer{ nullptr };
};

}

#endif // !__BE_RENDERER_H__



