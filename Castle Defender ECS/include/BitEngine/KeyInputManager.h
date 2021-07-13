#ifndef __BE_KEY_INPUT_MANAGER_H__
#define __BE_KEY_INPUT_MANAGER_H__

#include "utils/CacheSet.h"
#include "Keys.h"

namespace BE
{

class KeyInputManager
{
public:
	static KeyInputManager &getInstance();

	bool isKeyPressed(Key key);
	bool isKeyDown(Key key);
	bool isKeyReleased(Key key);
private:
	friend class Engine;

	using Keys = Utils::CacheSet<Key, Utils::CacheUtilization::Half>;

	KeyInputManager() = default;
	~KeyInputManager() = default;

	void keyPressed(Key key);
	void keyReleased(Key key);

	void update();

	static KeyInputManager m_instance;

	Keys m_currFrameKeys;
	Keys m_oldFrameKeys;
};

}

#endif // !__BE_KEY_INPUT_MANAGER_H__
