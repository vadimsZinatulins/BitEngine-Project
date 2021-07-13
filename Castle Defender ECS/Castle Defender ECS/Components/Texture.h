#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <BitEngine/Texture.h>

struct Texture
{
	Texture() {}
	Texture(const char *path) { texture.load(path); }
	~Texture() {}

	BE::Texture texture;
};

#endif // !__TEXTURE_H__
