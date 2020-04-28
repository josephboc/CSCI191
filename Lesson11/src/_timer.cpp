#include "_timer.h"

_timer::_timer()
{
    //ctor
    startAt =0;
    pauseAt =0;
    paused =false;
    started =false;
}

_timer::~_timer()
{
    //dtor
}
bool _timer::isStarted()
{
    return started;
}

bool _timer::isStoped()
{
    return !started;
}

bool _timer::isSpaused()
{
    return paused;
}

void _timer::pause()
{
    if(paused || !started)
        return;
    paused = true;
    pauseAt= clock();

}

void _timer::resume()
{
    if(!paused)return;
    paused = false;
    startAt +=clock()-pauseAt;
}

void _timer::start()
{
    if(started)return;
    started= true;
    paused = false;
    startAt= clock();

}

void _timer::stop()
{
    started = false;
}

void _timer::reset()
{
    paused = false;
    startAt = clock();
}

clock_t _timer::getTicks()
{
    if(!started)return 0;
    if(paused)return pauseAt - startAt;
    return clock()-startAt;
}
