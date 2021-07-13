#ifndef __BE_MOUSE_INPUT_MANAGER_H__
#define __BE_MOUSE_INPUT_MANAGER_H__

#include "utils/CacheSet.h"
#include "Keys.h"

namespace BE
{

struct MouseCoords
{
	int x{ 0 };
	int y{ 0 };
};

class MouseInputManager
{
public:
	static MouseInputManager &getInstance();

	void update();

	MouseCoords getMouseCoords() const;
	MouseCoords getMouseRelCoords() const;

	bool isButtonPressed(MouseButton btn) const;
	bool isButtonDown(MouseButton btn) const;
	bool isButtonReleased(MouseButton btn) const;

	MouseWheel getWheelMovement() const;
private:
	friend class Engine;

	using MouseButtons = Utils::CacheSet<MouseButton, Utils::CacheUtilization::Quarter>;

	MouseInputManager() = default;
	~MouseInputManager() = default;

	void setMouseCoords(MouseCoords newCoords);
	void setMouseRelCoords(MouseCoords newRelCoords);

	void buttonPressed(MouseButton btn);
	void buttonReleased(MouseButton btn);

	void setWheelMotion(MouseWheel wheel);

	static MouseInputManager m_instance;

	MouseButtons m_currFrameButtons;
	MouseButtons m_oldFrameButtons;

	MouseCoords m_mouseCoords;
	MouseCoords m_mouseRelCoords;

	MouseWheel m_mouseWheel{ MouseWheel::None };
};

constexpr auto Mouse = MouseInputManager::getInstance;

}

#endif // !__MOUSE_INPUT_MANAGER_H__
