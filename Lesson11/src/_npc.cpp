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
    frames =12;

    xMin=yMin=0.0;
    xMax=1.0/frames;
    yMax=0.125;
    action =1;

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
    case 1: //down
          frames=12;
          if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =0.0;
            yMax =0.125;

            rotateZ=0;
            yPos-=xMove;
            if(xMax>=1.0/3.0){xMin=0.0;xMax=1.0/12.0;action=5;}
            TE->reset();
          }
        break;

    case 2: //left
          frames=12;
          if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =0.25;
            yMax =0.375;

            rotateZ=0;
            xPos-=xMove;
            if(xMax>=1.0/3.0){xMin=0.0;xMax=1.0/12.0;action=5;}
            TE->reset();
          }
        break;

    case 3: //right
          frames=12;
          if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =0.125;
            yMax =0.250;


            rotateZ=0;
            xPos+=xMove;
            if(xMax>=1.0/3.0){xMin=0.0;xMax=1.0/12.0;action=5;}
            TE->reset();
          }
        break;

    case 4: //up
          frames=12;
          if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =0.375;
            yMax =0.5;

            rotateZ=0;
            yPos+=xMove;
            if(xMax>=1.0/3.0){xMin=0.0;xMax=1.0/12.0;action=5;}
            TE->reset();
          }
        break;

        case 5: //stand
          frames=12;
          for(int i=0;i<10;i++){
          if(TE->getTicks()>60){
            xMin=0.0;
            xMax=1.0/frames;
            yMin =0.0;
            yMax =0.125;

            rotateZ=0;
            TE->reset();
          }}
          action = rand() % 4+1;
        break;
    }

}
