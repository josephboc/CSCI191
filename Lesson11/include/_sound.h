#ifndef _SOUND_H
#define _SOUND_H

#include<SNDS/irrKlang.h>
#include<stdlib.h>
#include<iostream>
#include<_timer.h>

using namespace std;
using namespace irrklang;


class _sound
{
    public:
        _sound();
        virtual ~_sound();
        _timer *tmr = new _timer();
        ISoundEngine *engine = createIrrKlangDevice();

        void playMusic(char *);
        void pauseMusic(char *);
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();

    protected:

    private:
};

#endif // _SOUND_H
