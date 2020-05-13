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

        _Model *myModel = new _Model();
        _inputs *kBMs = new _inputs();
        _parallax *Season = new _parallax();  //Season background parallax
        _parallax *SeasonEffect = new _parallax();  //Season effect parallax
        _parallax *SeasonEffect2 = new _parallax();  //Season effect parallax
        _player *ply = new _player();
        _checkCollision *hit= new _checkCollision();
        _sound *snds = new _sound();

        _timer *SeasonTimer = new _timer();
        int currentSeason;
        bool doneLoading;
        bool secondEffectOn;

        _textureLoader *enmsTex = new _textureLoader();
        _textureLoader *foodTex = new _textureLoader();

        _enms enms[20];
        _food food[20];

        //WPARAM wParm;

        float screenHeight, screenWidth; // to map background images
    protected:

    private:
};

#endif // _GLSCENE_H
