#ifndef __BE_ACTION_HOLDER_H__
#define __BE_ACTION_HOLDER_H__

#include <mutex>
#include <vector>
#include <functional>

namespace BE
{

class ActionHolder
{
public:
	void scheduleAction(std::function<void()> action);
	void triggerActions();
	void delegateInvokations(ActionHolder *other);
private:
	std::vector<std::function<void()>> m_actions;
	ActionHolder *m_other{ nullptr };
	bool m_isTriggered{ false };

	std::mutex m_mutex;
};

}

#endif // !__BE_ACTION_HOLDER_H__
