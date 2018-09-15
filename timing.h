#ifndef TIMING_H
#define TIMING_H

#include<chrono>
using namespace std;
using namespace std::chrono;

class timing
{
    int flag;
    time_point<system_clock> start,curr;
    duration<double> dur,loc_dur;
    void update();
    public:
    timing();
    double getPassedTime();
    void stop();
    void resume();
};

#endif