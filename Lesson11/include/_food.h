#ifndef _FOOD_H
#define _FOOD_H

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>
#include <_checkCollision.h>
#include <stdlib.h>


class _food
{
    public:
        _food();
        virtual ~_food();
        void drawFood();                  //Draw objects
        void placeFood(float,float,float);//Place Enemy
        void initFood(GLuint);
        void actions();
                   //Movements and actions
        void output(int x, int y, float r, float g, float b, int font, char *string);

        bool isFoodAlive;                  //Status of the Enemy
        GLuint FoodTex;                   //handle Texture

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
};

#endif // _FOOD_H
