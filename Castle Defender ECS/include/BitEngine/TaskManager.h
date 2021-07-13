#ifndef __BE_TASK_MANAGER_H__
#define __BE_TASK_MANAGER_H__

#include "Task.h"
#include "TaskTraits.h"
#include "TaskScheduler.h"

namespace BE
{

template <typename T, typename ...Deps>
auto make_task(T t, Deps ...deps)
{
	const auto dependenciesCount = sizeof...(deps);

	auto task = std::make_shared<Task<T, Deps...>>(dependenciesCount, t, deps...);

	if constexpr (dependenciesCount == 0)
	{
		TaskScheduler::getInstance().schedule(task);
	}
	else
	{
		(..., deps->addFinishAction([=] { task->signalDependency(); }));
	}

	if constexpr (TaskTraits<TaskPtr<Task<T, Deps...>::R>>::isReturningTask)
	{
		return make_task([](auto x) { return x->result(); }, task);
	}
	else
	{
		return task;
	}
}

}

#endif // !__BE_TASK_MANAGER_H__
