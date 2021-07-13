#ifndef __BE_TIME_H__
#define __BE_TIME_H__

namespace BE
{

class Time
{
public:
	static Time &getInstance();

	float getTime();
	float getDeltaTime();

private:
	friend class Engine;
	friend class Window;

	Time() = default;
	~Time() = default;

	static Time m_instance;

	float m_deltaTime{ 0.0f };
	float m_time{ 0.0f };
};

}

#endif // !__BE_TIME_H__
