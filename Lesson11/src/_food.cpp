#include "_food.h"
#include <_player.h>
#include <string.h>
#include "_glScene.h"
#include <_glLight.h>
_food::_food()
{
    xPos= yPos =0.0;
    zPos =-1.0;

    xSize = 0.5;
    ySize = 0.5;

    rotateX=rotateY=rotateZ =0.0;
    frames =8;

    xMin=yMin=0.0;
    xMax=1.0/(float)frames;
    yMax=1.0;
    action =0;

}



void _food::drawFood()
{
    glBindTexture(GL_TEXTURE_2D,FoodTex);

    glPushMatrix();
        glTranslatef(xPos,yPos,zPos);
        glRotatef(rotateX,1.0,0.0,0.0);
        glRotatef(rotateY,0.0,1.0,0.0);
        glRotatef(rotateZ,0.0,0.0,1.0);
        glScalef(xSize,ySize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(xMax,yMin);
        glVertex3f(-1.0,1.0,0.0);
        glTexCoord2f(xMax,yMax);
        glVertex3f(-1.0, -1.0, 0.0);
        glTexCoord2f(xMin,yMax);
        glVertex3f(1.0,-1.0,0.0);
    glEnd();

    glPopMatrix();
}

void _food::placeFood(float x, float y, float z)
{
        xPos =x;
        yPos =y;
        zPos =z;
}

void _food::initFood(GLuint tex)
{
        FoodTex = tex;
        TE->start();
}

void _food::actions()
{
    switch(action){
    case 0:
       if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =0.0;
            yMax =1.0/5.0;

            rotateZ=0;
            if(xMax>=1){xMin=0;xMax=1.0/frames;}
            TE->reset();
          }
          drawFood();


    case 1:
        if(TE->getTicks()>60){
            xMin+=.33/frames;
            xMax+=1.0/frames;
            yMin =0.0;
            yMax =0.33;

            rotateZ=0;
            if(xMax>=1){xMin=0;xMax=1.0/frames;}
            TE->reset();
          }
          drawFood();
       break;

    case 2:
         if(TE->getTicks()>60){

            xMin =0.0/frames;
            xMax =1.0/frames;
            yMin =0.0;
            yMax =0.5;

           //  xSize = 1.0;
           //  ySize = 0.5;


            TE->reset();
         }
           drawFood();
        break;

    case 3:
         if(TE->getTicks()>60){

            xMin =0.0/frames;
            xMax =1.0/frames;
            yMin =0.0;
            yMax =0.5;

           //  xSize = 1.0;
           //  ySize = 0.5;
            TE->reset();
         }
           drawFood();
        break;
    case 4:
         if(TE->getTicks()>60){

            xMin =0.0/frames;
            xMax =1.0/frames;
            yMin =0.0;
            yMax =1.0;
            xPos = 8.0;
            yPos = 8.0;


           //  xSize = 1.0;
           //  ySize = 0.5;
            TE->reset();
         }
           drawFood();
    }}



_food::~_food()
{
    //dtor
}
