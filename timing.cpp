#include "timing.h"

timing::timing()
{
    flag=1;
    time_point<system_clock> x;
    x=system_clock::now();
    dur=x-x;
    loc_dur=dur;
}

timing::timing(int totalTime)
{
    flag=1;
    start=system_clock::now();
    dur=start-start;
    loc_dur=dur;
    this->totalTime=totalTime;
    updater=new thread(this->update);
}
double timing::getRemTime()
{
    return(totalTime- ((dur+loc_dur).count()));
}

void timing::stop()
{
    flag=0;
    dur=dur+loc_dur;
    if(updater->joinable())
    updater->join();
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
    updater=new thread(this->update);
}