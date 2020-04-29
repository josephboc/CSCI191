#ifndef _NPC_H
#define _NPC_H

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>
#include <_checkCollision.h>
#include <stdlib.h>

class _npc
{
    public:
        _npc();
        virtual ~_npc();

        void drawNPC();                  //Draw objects
        void initNPC(GLuint);
        void actions();                    //Movements and actions

        GLuint NPCTex;                   //handle Texture

        float xPos, yPos, zPos;            // Placements
        float xSize,ySize;                 // Scaling Factor

        float rotateX, rotateY,rotateZ;    // rotations

        int frames;                        //number of frames
        float xMove;                        // moving speed on x axis
        float yMove;
        int action;                         // to make an action for enemy
        _timer *TE = new _timer();

    protected:

    private:
        float xMin, yMin,xMax,yMax;
};

#endif // _NPC_H
