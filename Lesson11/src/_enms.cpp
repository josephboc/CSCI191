#include "_enms.h"

_enms::_enms()
{
    //ctor
    xPos= yPos =0.0;
    zPos =-4.0;

    xSize = 1.0;
    ySize = 0.5;

    rotateX=rotateY=rotateZ =0.0;
    frames =4;

    xMin=yMin=0.0;
    xMax=1.0/(float)frames;
    yMax=1.0/6;
    action =0;
    theta =30*(3.141592/180);

    g=9.81;
    v=35.0;
    t=0.0;

    xMove= 0.01;
}

_enms::~_enms()
{
    //dtor
}
void _enms::drawEnemy()
{
    glBindTexture(GL_TEXTURE_2D,EnemyTex);

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

void _enms::placeEnemy(float x, float y, float z)
{
        xPos =x;
        yPos =y;
        zPos =z;
}

void _enms::initEnemy(GLuint tex)
{
        EnemyTex = tex;
        TE->start();
}

void _enms::actions()
{
    switch(action){
    case 0:
          if(TE->getTicks()>120){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =1.0/4.0;
            yMax =2.0/4.0;

            rotateZ=0;
            if(xMax>=1){xMin=0;xMax=1.0/frames;}
            TE->reset();
          }
          drawEnemy();
        break;


    case 1:
        if(TE->getTicks()>60){
            xMin+=1.0/frames;
            xMax+=1.0/frames;
            yMin =2.0/4.0;
            yMax =3.0/4.0;

            rotateZ=0;
            if(xMax>=1){xMin=0;xMax=1.0/frames;}
            TE->reset();
          }
          drawEnemy();
       break;

    case 2:
         if(TE->getTicks()>60){

            xMin =0.0/frames;
            xMax =1.0/frames;
            yMin =0.0;
            yMax =1.0/13;

           //  xSize = 1.0;
           //  ySize = 0.5;

            rotateZ +=(float)(rand()/float(RAND_MAX))*100;
            xMove =-(float)(rand()/float(RAND_MAX))/1000;

            xPos -= (v*t*cos(theta))/1500;
            yPos += (v*t*sin(theta)-0.5*g*t*t)/600;

          //
            if(yPos>-0.25)t +=0.3;
            else {t=0;yPos =-0.2;}

            TE->reset();
         }
           drawEnemy();
        break;

    case 3:
         if(TE->getTicks()>60){

            xMin =0.0/frames;
            xMax =1.0/frames;
            yMin =0.0;
            yMax =1.0/13;

           //  xSize = 1.0;
           //  ySize = 0.5;

            rotateZ -=(float)(rand()/float(RAND_MAX))*100;
            xMove =(float)(rand()/float(RAND_MAX))/50;
            TE->reset();
         }
           drawEnemy();
        break;

    }

}
