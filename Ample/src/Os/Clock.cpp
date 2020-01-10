#include <chrono>
#include <set>

#include "Clock.h"

namespace os
{
class Timer;

time_point Clock::creationTime;
time_point Clock::curTime;
std::vector<Timer *> Clock::timers;
milliseconds Clock::liveTime;
milliseconds Clock::delta;

Clock::Clock()
{
    static bool wasInit = false;

    if (!wasInit)
    {
        creationTime = std::chrono::system_clock::now(),
        curTime = creationTime;
        wasInit = true;
        delta = std::chrono::duration_cast<milliseconds>(curTime - creationTime);
        liveTime = delta;
    }
}

milliseconds Clock::globalTime()
{
    return liveTime;
}

int Clock::globalTimeMs()
{
    return liveTime.count();
}

double Clock::globalTimeSec()
{
    return globalTimeMs() / 1000.0;
}

void Clock::update()
{
    auto oldTime = curTime;
    curTime = std::chrono::system_clock::now();
    delta = std::chrono::duration_cast<milliseconds>(curTime - oldTime);
    liveTime = std::chrono::duration_cast<milliseconds>(curTime - creationTime);
    std::vector<os::Timer *> newTimers;
    int cnt = 0;
    for (auto timer : timers)
    {
        timer->updateCurTime(liveTime);
        if (timer->check())
        {
            cnt++;
        }
        else
        {
            newTimers.push_back(timer);
        }
    }
    if (cnt != 0)
    {
        timers = newTimers;
    }
}

void Clock::addTimer(os::Timer *timer)
{
    timers.push_back(timer);
}

Timer::Timer()
    : stopped(true) {}

Timer::Timer(milliseconds delta)
    : delta(delta) {}

Timer::Timer(int delta)
    : delta(std::chrono::milliseconds(delta)) {}

void Timer::start()
{
    Clock::addTimer(this);
    this->startTime = Clock::globalTime();
    this->stopped = false;
}

void Timer::stop()
{
    this->stopped = true;
}

milliseconds Timer::timeLeft()
{
    return this->startTime + this->delta - this->curTime;
}

int Timer::timeLeftMs()
{
    return this->timeLeft().count();
}

double Timer::timeLeftSec()
{
    return this->timeLeft().count() / 1000.0;
}

void Timer::updateCurTime(const milliseconds &time)
{
    this->curTime = time;
}

bool Timer::check()
{
    if (stopped)
    {
        return false;
    }
    if (startTime + delta <= curTime)
    {
        onEnd();
        stopped = true;
        return true;
    }
    return false;
}

} // namespace os
