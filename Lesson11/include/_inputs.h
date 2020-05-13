#ifndef _INPUTS_H
#define _INPUTS_H

#include<windows.h>
#include<_Model.h>
#include<_parallax.h>
#include<_player.h>
#include<_sound.h>
#include <_MenuManager.h>



class _inputs
{
    public:
        _inputs();
        virtual ~_inputs();

        void keyPressed(_Model *, _MenuManager*);   // state handling
        void keyPressed(_player *);   // model handling
        void keyPressed(_sound *);

        void keyEnv(_parallax *,float); // handles the background movement
        void keyUp();
        void keyUp(_player *);   // model handling

        void mouseEventDown(_Model *,double ,double);
        void mouseEventUp();
        void mouseWheel(_Model *,double);
        void mouseMove(_Model *,double ,double );


        double prev_Mouse_X;
        double prev_Mouse_Y;
        bool Mouse_Translate;
        bool Mouse_Rotate;

        WPARAM wParam;


    protected:

    private:
};

#endif // _INPUTS_H
