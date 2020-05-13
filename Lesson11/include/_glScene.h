#ifndef _GLSCENE_H
#define _GLSCENE_H

#include <windows.h>
#include<GL/glut.h>
#include <_MenuManager.h>

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
        MenuStates sendScreen();


        int winMsg(HWND, UINT, WPARAM, LPARAM);	// Callback of inputs

        //WPARAM wParm;

        float screenHeight, screenWidth; // to map background images
    protected:

    private:
};

#endif // _GLSCENE_H
