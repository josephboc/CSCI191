#ifndef _TIMER_H
#define _TIMER_H
#include<time.h>

class _timer
{
    public:
        _timer();
        virtual ~_timer();

        clock_t startAt;
        clock_t pauseAt;

        bool started;
        bool paused;

        bool isStarted();
        bool isStoped();
        bool isSpaused();

        void pause();
        void resume();
        void start();
        void stop();
        void reset();

        clock_t getTicks();


    protected:

    private:
};

#endif // _TIMER_H
