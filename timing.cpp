#include "timing.h"

timing::timing()
{
    flag=1;
    time_point<system_clock> x;
    x=system_clock::now();
    dur=x-x;
    loc_dur=dur;
    // cerr<<dur.count()<<endl;
    // cerr<<loc_dur.count()<<endl;
}

timing::timing(int totalTime)
{
    flag=1;
    start=system_clock::now();
    dur=start-start;
    loc_dur=dur;
    this->totalTime=totalTime;
    // cerr<<"time const"<<endl;
    // cerr<<dur.count()<<endl;
    // cerr<<loc_dur.count()<<endl;
    updater=new thread(&timing::update,this);
}
double timing::getRemTime()
{
    // cerr<<"gettime"<<endl;
    // cerr<<(dur+loc_dur).count()<<endl;
    return((double)totalTime-(dur.count()+loc_dur.count()) );
}

void timing::stop()
{
    flag=0;
    // cerr<<"stop"<<endl;
    if(updater->joinable())
    updater->join();
    dur=dur+loc_dur;
    // cerr<<dur.count()<<endl;
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
    // cerr<<"time resume"<<endl;
    // cerr<<dur.count()<<endl;
    // cerr<<loc_dur.count()<<endl;
    updater=new thread(&timing::update,this);
}