#ifndef _GLSCENE_H
#define _GLSCENE_H

#include <windows.h>
#include<GL/glut.h>


#include<iostream>
#include <_Model.h>
#include <_inputs.h>
#include <_parallax.h>
#include <_player.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <_sound.h>
#include <iostream>
#include <_food.h>
#include<_timer.h>
#include<iostream>

using namespace std;

class _glScene
{
    public:
        _glScene();               // constructor
        virtual ~_glScene();      // Deconstructor
        GLint initGL();           // initialize OpenGL
        GLint drawScene();        // Renderer
        GLvoid reSizeScene(GLsizei, GLsizei); // screen size changes
        int winMsg(HWND, UINT, WPARAM, LPARAM);	// Callback of inputs
        int counter;

        //WPARAM wParm;
        _timer *SeasonTimer = new _timer();
        int currentSeason;
        bool doneLoading;
        int scenechecker;
        int foodstack;
        int prev;
        bool switching;
        bool switching1;
        bool switching2;
        bool switching3;
        bool startover;

        float screenHeight, screenWidth; // to map background images
    protected:

    private:
};

#endif // _GLSCENE_H
