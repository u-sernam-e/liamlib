#include "timer.h"

void Timer::init()
{
    m_timeSinceInit = 0;
}

void Timer::update()
{
    m_timeSinceInit += lowerLimitFrameTime();
}