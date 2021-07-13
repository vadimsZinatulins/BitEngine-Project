#ifndef __PROFILER_PROFILER_H__
#define __PROFILER_PROFILER_H__

#include <fstream>
#include <thread>

namespace Benchmark
{

struct ProfileResult
{
	std::string name;

	long long start;
	long long end;

	std::thread::id threadId;
};

struct ProfilerSession
{
	std::string name;
};

class Profiler
{
public:
	Profiler();
	~Profiler();

	void beginSession(const std::string &name, const std::string &filePath = "result.json");
	void writeProfile(const ProfileResult &result);
	void endSession();

	static Profiler &getInstance();
private:
	void writeHeader();
	void writeFooter();

	static Profiler m_instance;

	ProfilerSession *m_currentSession;

	std::ofstream m_outputStream;

	unsigned int m_profileCount;
};

}


#endif // !__PROFILER_PROFILER_H__
