#ifndef _TEXTS_H
#define _TEXTS_H
#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>
#include <_checkCollision.h>
#include <stdlib.h>


class _texts
{
    public:
        _texts();
        virtual ~_texts();
        void drawtexts();                  //Draw objects
        void placetext(float,float,float);//Place Enemy
        void inittext(GLuint);
        void actions();
                   //Movements and actions
        void output(int x, int y, float r, float g, float b, int font, char *string);

                //Status of the Enemy
        GLuint textTex;                   //handle Texture
        GLuint textTex2;
        float xPos, yPos, zPos;            // Placements
        float xSize,ySize;                 // Scaling Factor

        float rotateX, rotateY,rotateZ;    // rotations

        int frames;                        //number of frames                        // moving speed on x axis
        int action;                         // to make an action for enemy
        _timer *TE = new _timer();
        float g;
        float v;
        float t;
    protected:

    private:
        float xMin, yMin,xMax,yMax;
    protected:

    private:
    protected:

    private:
};

#endif // _TEXTS_H
