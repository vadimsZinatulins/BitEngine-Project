#include "TaskScheduler.h"
#include "Task.h"

namespace BE
{

TaskScheduler TaskScheduler::m_instance;

TaskScheduler &TaskScheduler::getInstance()
{
	return m_instance;
}

void TaskScheduler::schedule(std::shared_ptr<ITask> task)
{
	// Push new task to the queue
	m_queue.push(task);
}

void TaskScheduler::initialize()
{
	// Lambda function that each thread will execute
	auto body = [this] {
		while (true)
		{
			// Retrieve task from queue. If queue is empty then
			// this thread will wait here until new task is available
			std::shared_ptr<ITask> task;
			m_queue.pop(task);

			// If task is empty then it means this thread
			// must be shutdown
			if (!task)
			{
				return;
			}

			// Execute task
			(*task)();
		}
	};

	// Accommodate enough space for all threads in the thread vector
	m_threads.resize(std::thread::hardware_concurrency());

	// Initialize each thread
	for (auto &thread : m_threads)
	{
		thread = std::thread(body);
	}
}

void TaskScheduler::shutdown()
{
	// For each thread, give them empty function to execute. This will signal them
	// to shutdown
	for (std::size_t i = 0; i < m_threads.size(); i++)
	{
		m_queue.push({});
	}


	// Make sure each thread shutsdown before moving on
	for (auto &thread : m_threads)
	{
		thread.join();
	}
}

}