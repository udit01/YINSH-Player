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
    thread *updater;
    time_point<system_clock> start,curr;
    duration<double> dur,loc_dur;
   
    public:
    timing();
    timing(int totalTime);
    void update();
    double getRemTime();
    void stop();
    void resume();
};

#endif