#ifndef TIMING_H
#define TIMING_H

#include<chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

class timing
{
    int flag;
    int totalTime;
    time_point<system_clock> start,curr;
    duration<double> dur,loc_dur;
    void update();
    public:
    timing();
    timing(int totalTime);
    double getRemTime();
    void stop();
    void resume();
};

#endif