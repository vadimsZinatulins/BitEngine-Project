#ifndef __BE_TASK_TRAITS_H__
#define __BE_TASK_TRAITS_H__

#include <memory>

namespace BE
{

template <typename T, typename ...Deps>
class Task;

template <typename T>
using TaskPtr = std::shared_ptr<Task<T>>;

template <typename T>
struct TaskTraits
{
	static constexpr bool isTask{ false };
	static constexpr bool isReturningTask{ false };
};

template <typename T>
struct TaskTraits<TaskPtr<TaskPtr<T>>>
{
	static constexpr bool isTask{ true };
	static constexpr bool isReturningTask{ true };
};

}

#endif // !__BE_TASK_TRAITS__
