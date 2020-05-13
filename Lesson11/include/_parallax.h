#ifndef _PARALLAX_H
#define _PARALLAX_H

#include<iostream>
#include<string>
#include<gl/gl.h>
#include<windows.h>
#include<_textureLoader.h>

using namespace std;

class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        void drawSquare(float, float); // to draw a quad for the background
        void drawBacking(float, float); //splish splash, the above line is trash. //load para as background.
        void parallaxInit(char *);     // Load images to the background
        void scroll(bool,string,float);// bool for Auto, string for direction
                                       // speed of the movement
       _textureLoader *bTex = new _textureLoader();

        float xMax,yMax,xMin,yMin;     //  For texture coordinates

    protected:

    private:
};

#endif // _PARALLAX_H
