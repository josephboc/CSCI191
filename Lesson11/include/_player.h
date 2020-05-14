#ifndef _PLAYER_H
#define _PLAYER_H

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>

typedef struct
{
    float x;
    float y;
    float z;
}vec3;

class _player
{
private:


    public:
    float hunger;
    float speed;
    float strength;
    float cuteness;
    float hungerrate;
        _player();
        virtual ~_player();

        float scale[3]={1.0,1.0,1.0};
        vec3 verticies[4];

        float xPos;   //x position of the Player
        float yPos;   //y position of the Player
        float zPos;   //z position of the Player
        float skillpoints;

        float xSize;
        float ySize;

        float xRotation;
        float yRotation;
        float zRotation;
        float xMove;
        float health;
        int foodstack;

        float runSpeed;
        float jumpSpeed;

        void drawPlayer();
        void placePlayer();
        void initPlayer(char *);
        void hungerlower();

        void actions();   // may have to pass different frame numbers
        int action;          // give values for run jump etc.
        float frames;
        float xMax,xMin,yMax,yMin;

    protected:

    private:
};

#endif // _PLAYER_H
