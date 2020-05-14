#include "_texts.h"

_texts::_texts()
{
    xPos= yPos =0.0;
    zPos =-1.0;

    xSize = 0.5;
    ySize = 0.5;

    rotateX=rotateY=rotateZ =0.0;
    frames =10;

    xMin=yMin=0.0;
    xMax=1.0/(float)frames;
    yMax=1.0;
    action =0;

}

void _texts::drawtexts()
{
    glBindTexture(GL_TEXTURE_2D,textTex);

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
void _texts::placetext(float x, float y, float z)
{
        xPos =x;
        yPos =y;
        zPos =z;
}

void _texts::inittext(GLuint tex)
{
        textTex = tex;
        textTex2 = tex;
        TE->start();

}
void _texts::actions()
{
switch(action){
    case 0:
       if(TE->getTicks()>60){
            xMin =0.0;
            yMin = 0.0;
            xMax = 1.0/frames;
            yMax =1.0;

            rotateZ=0;
            if(xMax>=1){xMin=0;xMax=1.0/frames;}
            TE->reset();
          }
          drawtexts();
    case 1:
       if(TE->getTicks()>60){
            xMin =1.0/frames;
            yMin = 0.0;
            xMax = 2.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();
          }
          drawtexts();
    case 2:
       if(TE->getTicks()>60){
            xMin =2.0/frames;
            yMin = 0.0;
            xMax = 3.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();
          }
          drawtexts();
    case 3:
       if(TE->getTicks()>60){
            xMin =3.0/frames;
            yMin = 0.0;
            xMax = 4.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();
          }
    case 4:
       if(TE->getTicks()>60){
            xMin =4.0/frames;
            yMin = 0.0;
            xMax = 5.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();

          drawtexts();
    case 5:
       if(TE->getTicks()>60){
            xMin =5.0/frames;
            yMin = 0.0;
            xMax = 6.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();

          drawtexts();
       }
           case 6:
       if(TE->getTicks()>60){
            xMin =6.0/frames;
            yMin = 0.0;
            xMax = 7.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();

          drawtexts();
       }
           case 7:
       if(TE->getTicks()>60){
            xMin =7.0/frames;
            yMin = 0.0;
            xMax = 8.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();

          drawtexts();
       }
           case 8:
       if(TE->getTicks()>60){
            xMin =8.0/frames;
            yMin = 0.0;
            xMax = 9.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();

          drawtexts();
       }
           case 9:
       if(TE->getTicks()>60){
            xMin =9.0/frames;
            yMin = 0.0;
            xMax = 10.0/frames;
            yMax =1.0;

            rotateZ=0;

            TE->reset();

          drawtexts();
       }
       }}
}
_texts::~_texts()
{
    //dtor
}
