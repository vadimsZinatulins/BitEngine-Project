#ifndef __BE_TASK_H__
#define __BE_TASK_H__

#include <memory>
#include <future>
#include <tuple>
#include <atomic>
#include <type_traits>

#include "ActionHolder.h"
#include "TaskTraits.h"
#include "TaskScheduler.h"

namespace BE
{

struct ITask
{
	ITask() = default;
	virtual ~ITask() = default;

	virtual void operator()() = 0;
};

template <typename T, typename ...Deps>
class Task final : public ITask, public std::enable_shared_from_this<Task<T, Deps...>>
{
public:
	// Set R to be the return type
	using R = std::invoke_result_t<T, typename Deps::element_type::R...>;

	Task(std::size_t dependenciesCount, T t, Deps ...deps) :
		m_body(t),
		m_future(m_promise.get_future()),
		m_deps(deps...),
		m_dependenciesCount(dependenciesCount)
	{
	}

	~Task()
	{

	}

	void operator()()
	{
		// Lambda function that triggers the task to run
		auto run = [this](Deps ... deps) {
			// TODO: Remove all 'void' types from 'deps'
			
			// Get the result of all dependencies, pass them to tue task body, execute task
			// and set the promise with the result of the task
			if constexpr (std::is_same<R, void>::value)
			{
				m_body(deps->result()...);
				m_promise.set_value();
			}
			else
			{
				m_promise.set_value(m_body(deps->result()...));
			}
		};

		// Execute lambda function with dependencies as arguments
		std::apply(run, m_deps);

		if constexpr (TaskTraits<R>::isTask)
		{
			auto &task = m_future.get();
			m_actionHolder.delegateInvokations(&task->getActionHolder());
		}
		else
		{
			m_actionHolder.triggerActions();
		}
	}

	void addFinishAction(std::function<void()> action)
	{
		m_actionHolder.scheduleAction(action);
	}

	R result()
	{
		return m_future.get();
	}

	ActionHolder &getActionHolder()
	{
		return m_actionHolder;
	}

	void signalDependency()
	{
		if (!--m_dependenciesCount)
		{
			TaskScheduler::getInstance().schedule(this->shared_from_this());
		}
	}
private:
	T m_body;

	std::promise<R> m_promise;
	std::shared_future<R> m_future;
	std::tuple<Deps...> m_deps;

	std::atomic<std::size_t> m_dependenciesCount;
	ActionHolder m_actionHolder;
};

}

#endif // !__BE_TASK_H__
