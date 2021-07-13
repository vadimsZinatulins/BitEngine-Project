#ifndef __BE_TEXTURE_H__
#define __BE_TEXTURE_H__

#include <string>

struct SDL_Texture;

namespace BE
{

class Texture
{
public:
	Texture() = default;
	~Texture() = default;

	void load(const std::string &path);

	operator SDL_Texture *() const;
private:
	SDL_Texture *m_texture{ nullptr };
};

}

#endif // !__BE_TEXTURE_H__
