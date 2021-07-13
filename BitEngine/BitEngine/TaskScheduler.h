#ifndef __BE_TASK_SCHEDULER_H__
#define __BE_TASK_SCHEDULER_H__

#include "TaskQueue.h"

#include <vector>
#include <thread>

namespace BE
{

class TaskScheduler
{
public:
	static TaskScheduler &getInstance();

	void schedule(std::shared_ptr<ITask> task);
private:
	friend class Engine;

	TaskScheduler() = default;
	~TaskScheduler() = default;

	void initialize();
	void shutdown();

	static TaskScheduler m_instance;

	// Queue of all tasks to execute
	TaskQueue m_queue;
	// All available threads that will execute tasks
	std::vector<std::thread> m_threads;
};

}

#endif // !__BE_TASK_SCHEDULER_H__
