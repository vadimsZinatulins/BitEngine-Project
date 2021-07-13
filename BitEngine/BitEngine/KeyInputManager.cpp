#include "KeyInputManager.h"

namespace BE
{

KeyInputManager KeyInputManager::m_instance;

KeyInputManager &KeyInputManager::getInstance()
{
	return m_instance;
}

bool KeyInputManager::isKeyPressed(Key key)
{
	// If the 'current frame' contains the key and the 'last frame' does not then the key was pressed in current frame
	return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key);
}

bool KeyInputManager::isKeyDown(Key key)
{
	// If the 'current frame' contains the key it means that the key is down
	return m_currFrameKeys.contains(key);
}

bool KeyInputManager::isKeyReleased(Key key)
{
	// If the 'current frame' does not contain the key but the 'last frame' does then the key was released in current frame
	return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key);
}

void KeyInputManager::keyPressed(Key key)
{
	// Insert key in 'current frame' cache set
	m_currFrameKeys.insert(key);
}

void KeyInputManager::keyReleased(Key key)
{
	// Remove key from 'current frame' cache set
	m_currFrameKeys.remove(key);
}

void KeyInputManager::update()
{
	// Copy 'current frame' keys to 'last frame' set
	m_oldFrameKeys = m_currFrameKeys;
}

}