#ifndef _ENMS_H
#define _ENMS_H

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>
#include <_checkCollision.h>
#include <stdlib.h>


class _enms
{
    public:
        _enms();
        virtual ~_enms();

        void drawEnemy();                  //Draw objects
        void placeEnemy(float,float,float);//Place Enemy
        void initEnemy(GLuint);
        void actions();                    //Movements and actions

        bool isEnemyLive;                  //Status of the Enemy
        GLuint EnemyTex;                   //handle Texture

        float xPos, yPos, zPos;            // Placements
        float xSize,ySize;                 // Scaling Factor

        float rotateX, rotateY,rotateZ;    // rotations

        int frames;                        //number of frames
        float xMove;                        // moving speed on x axis
        int action;                         // to make an action for enemy
        _timer *TE = new _timer();
        float theta;
        float g;
        float v;
        float t;
    protected:

    private:
        float xMin, yMin,xMax,yMax;
};

#endif // _ENMS_H
