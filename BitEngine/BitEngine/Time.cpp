#include "Time.h"

namespace BE
{

Time Time::m_instance;

Time &Time::getInstance()
{
	return m_instance;
}

float Time::getTime()
{
	return m_time;
}

float Time::getDeltaTime()
{
	return m_deltaTime;
}

}
