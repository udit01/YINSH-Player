#ifndef TIMING_H
#define TIMING_H

#include<chrono>
using namespace std;
using namespace std::chrono;

class timing
{
    int flag;
    duration<double> dur;
    void update();
    public:
    timing();
    double getPassedTime();
    void stop();
    void resume();
};

#endif