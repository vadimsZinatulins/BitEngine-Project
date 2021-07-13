#include "TaskQueue.h"

namespace BE
{

void TaskQueue::push(std::shared_ptr<ITask> task)
{
	// Lock this function
	std::unique_lock<std::mutex> lock(m_mutex);

	// Place new task into the queue
	m_queue.push(task);

	// Notify one thread that new task is available
	m_newTaskAvailable.notify_one();
}

void TaskQueue::pop(std::shared_ptr<ITask> &task)
{
	// Lock this function
	std::unique_lock<std::mutex> lock(m_mutex);

	// Wait until new task is available. When new task is available make sure it is not
	// empty, if so wait until next notification
	m_newTaskAvailable.wait(lock, [this] { return !m_queue.empty(); });

	// Set the task
	task = m_queue.front();

	// Remove task from queue
	m_queue.pop();
}

}