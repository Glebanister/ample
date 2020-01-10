#pragma once

#include <iostream>
#include <chrono>
#include <vector>

namespace os
{
typedef std::chrono::_V2::system_clock::time_point time_point;
typedef std::chrono::milliseconds milliseconds;

class Timer;

class Clock
{
public:
    Clock();

    static milliseconds globalTime();
    static int globalTimeMs();
    static double globalTimeSec();
    static milliseconds deltaTime();
    static void update();
    static void addTimer(Timer *timer);

private:
    static time_point creationTime;
    static time_point curTime;
    static std::vector<Timer *> timers;
    static milliseconds delta;
    static milliseconds liveTime;
};

class Timer
{
public:
    Timer();
    Timer(milliseconds);
    Timer(int);
    bool check();

    virtual void onEnd() = 0;
    void start();
    void stop();
    milliseconds timeLeft();
    int timeLeftMs();
    double timeLeftSec();
    void updateCurTime(const milliseconds &time);

private:
    milliseconds startTime;
    milliseconds curTime;
    milliseconds delta;

    bool stopped = false;
};
} // namespace os
