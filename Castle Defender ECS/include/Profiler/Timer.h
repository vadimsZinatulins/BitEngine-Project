#ifndef __PROFILER_TIMER_H__
#define __PROFILER_TIMER_H__

#include <chrono>

#ifdef PPROFILE
#define PPROFILE_SCOPE(name) Benchmark::Timer timer##__LINE__(name)
#define PPROFILE_FUNCTION() PPROFILE_SCOPE(__FUNCSIG__)
#else
#define PPROFILE_SCOPE(name)
#define PPROFILE_FUNCTION()
#endif // PPROFILE

namespace Benchmark
{
class Timer
{
public:
	Timer(const char *name);
	~Timer();

	void stop();
private:
	const char *m_name;

	std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint;

	bool m_stopped;
};
}

#endif // !__PROFILER_TIMER_H__
