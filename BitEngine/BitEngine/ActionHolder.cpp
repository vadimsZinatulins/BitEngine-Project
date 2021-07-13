#include "ActionHolder.h"

namespace BE
{

void ActionHolder::scheduleAction(std::function<void()> action)
{
	std::scoped_lock lock(m_mutex);

	if (m_other)
	{
		m_other->scheduleAction(action);
	}
	else if (m_isTriggered)
	{
		action();
	}
	else
	{
		m_actions.push_back(action);
	}
}

void ActionHolder::triggerActions()
{
	{
		std::scoped_lock lock(m_mutex);
		m_isTriggered = true;
	}

	for (auto &action : m_actions)
	{
		action();
	}
}

void ActionHolder::delegateInvokations(ActionHolder *other)
{
	std::scoped_lock lock(m_mutex);
	m_other = other;
	for (auto action : m_actions)
	{
		m_other->scheduleAction(action);
	}

	m_actions.clear();
}

}