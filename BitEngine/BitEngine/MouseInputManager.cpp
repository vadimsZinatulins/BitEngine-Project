#include "MouseInputManager.h"

namespace BE
{

MouseInputManager MouseInputManager::m_instance;

MouseInputManager &MouseInputManager::getInstance()
{
	return m_instance;
}

void MouseInputManager::update()
{
	m_oldFrameButtons = m_currFrameButtons;
	m_mouseRelCoords = { 0, 0 };
	m_mouseWheel = MouseWheel::None;
}

MouseCoords MouseInputManager::getMouseCoords() const
{
	return m_mouseCoords;
}

MouseCoords MouseInputManager::getMouseRelCoords() const
{
	return m_mouseRelCoords;
}

bool MouseInputManager::isButtonPressed(MouseButton btn) const
{
	return m_currFrameButtons.contains(btn) && !m_oldFrameButtons.contains(btn);
}

bool MouseInputManager::isButtonDown(MouseButton btn) const
{
	return m_currFrameButtons.contains(btn);
}

bool MouseInputManager::isButtonReleased(MouseButton btn) const
{
	return !m_currFrameButtons.contains(btn) && m_oldFrameButtons.contains(btn);
}

MouseWheel MouseInputManager::getWheelMovement() const
{
	return MouseWheel();
}

void MouseInputManager::setMouseCoords(MouseCoords newCoords)
{
	m_mouseCoords = { newCoords.x, newCoords.y };
}

void MouseInputManager::setMouseRelCoords(MouseCoords newRelCoords)
{
	m_mouseRelCoords = { newRelCoords.x, newRelCoords.y };
}

void MouseInputManager::buttonPressed(MouseButton btn)
{
	m_currFrameButtons.insert(btn);
}

void MouseInputManager::buttonReleased(MouseButton btn)
{
	m_currFrameButtons.remove(btn);
}

void MouseInputManager::setWheelMotion(MouseWheel wheel)
{
	m_mouseWheel = wheel;
}

}