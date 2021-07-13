#ifndef __BE_TEXTURE_MANAGER_H__
#define __BE_TEXTURE_MANAGER_H__

#include <string>
#include <unordered_map>

namespace BE
{

class TextureManager
{
public:
	static TextureManager &getInstance();

	void *loadTexture(const std::string &path);
	void clear();
private:
	TextureManager() = default;
	~TextureManager() = default;

	static TextureManager m_instance;

	std::unordered_map<std::string, void *> m_textues{};
};

}

#endif // !__BE_TEXTURE_MANAGER_H__
