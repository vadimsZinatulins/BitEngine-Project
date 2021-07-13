#ifndef __BE_TASK_QUEUE_H__
#define __BE_TASK_QUEUE_H__

#include <queue>
#include <mutex>
#include <memory>

namespace BE
{

struct ITask;

class TaskQueue
{
public:
	TaskQueue() = default;
	~TaskQueue() = default;

	void push(std::shared_ptr<ITask> task);
	void pop(std::shared_ptr<ITask> &task);
private:
	std::queue<std::shared_ptr<ITask>> m_queue;

	std::mutex m_mutex;
	std::condition_variable m_newTaskAvailable;
};

}

#endif // !__BE_TASK_QUEUE_H__
