#include "_sound.h"
#include "_glScene.h"
_sound::_sound()
{
    //ctor
}

_sound::~_sound()
{
    //dtor
    engine->drop();
}
void _sound::playMusic(char* File)
{
    engine->play2D(File,true);
}

void _sound::pauseMusic(char* File)
{
    engine->play2D(File,false);
}

void _sound::playSound(char* File)
{
    if(!engine->isCurrentlyPlaying(File))
    engine->play2D(File,false,false);
}

void _sound::pauseSound(char* File)
{
    engine->play2D(File,true,false);
}


int _sound::initSounds()
{
    if(!engine){cout<< "The Sound Engine did not startup\n";
       return 0;
    }
    return 1;
}
