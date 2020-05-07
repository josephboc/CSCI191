#include "_npc.h"

_npc::_npc()
{
    //ctor
    xPos=1.0;
    yPos=0.0;
    zPos=-2.5;

    xSize = 1.0;
    ySize = 0.5;

    rotateX=rotateY=rotateZ =0.0;
    frames =8;

    xMin=yMin=0.0;
    xMax=1.0/frames;
    yMax=1.0;
    action =0;

    xMove= 0.01;
}

_npc::~_npc()
{
    //dtor
}

void _npc::drawNPC()
{
    glBindTexture(GL_TEXTURE_2D,NPCTex);

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

void _npc::initNPC(GLuint tex)
{
        NPCTex = tex;
        TE->start();
}

void _npc::actions()
{
    switch(action){
    case 0:
          if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =0.0;
            yMax =1.0;

            rotateZ=0;
            if(xMax>=1){xMin=0;xMax=1.0/frames;}
            TE->reset();
          }
          drawNPC();
        break;
    }

}
