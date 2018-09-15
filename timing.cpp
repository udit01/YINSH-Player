#include "timing.h"

timing::timing()
{
    flag=1;
    time_point<system_clock> x;
    x=system_clock::now();
    dur=x-x;
    loc_dur=dur;
}

double timing::getPassedTime()
{
    return ((dur+loc_dur).count());
}

void timing::stop()
{
    flag=0;
    dur=dur+loc_dur;
}

void timing::update()
{
    while(flag)
    {
        curr=system_clock::now();
        loc_dur=curr-start;
    }
}

void timing::resume()
{
    flag=1;
    start=system_clock::now();
    loc_dur=start-start;
    this->update();
}