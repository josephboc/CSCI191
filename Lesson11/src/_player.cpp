#include "_player.h"

_textureLoader *T= new _textureLoader();
_timer *tmr = new _timer();


_player::_player()
{
    //ctor
    verticies[0].x=0.0; verticies[0].y=0.0;verticies[0].z=-.2;
    verticies[1].x=.2; verticies[1].y=0.0;verticies[1].z=-.2;
    verticies[2].x=.2; verticies[2].y=.2;verticies[2].z=-.2;
    verticies[3].x=0.0; verticies[3].y=.2;verticies[3].z=-.2;

    runSpeed =0;
    jumpSpeed =0;

    xPos=0.0;   //x position of the Player
    yPos=-2.0;   //y position of the Player
    zPos=-5.0;   //z position of the Player

    xSize =1.0;
    ySize =1.0;

    xRotation=0.0;
    yRotation=0.0;
    zRotation=0.0;
    skillpoints = 0.0;

    action =-1;
    health = 100;
    frames =8;
    xMin=0/frames;
    yMin=0.0;
    yMax=0.125;
    xMax=1.0/frames;
    xMove = .1; //aka speed
    hunger = 1;
    hungerrate = .01;
    strength = 0.0;
    cuteness = 0.0;

}

_player::~_player()
{
    //dtor
}

void _player::placePlayer()
{

}

void _player::drawPlayer()
{
    glColor3f(1.0,0.0,0.0);
   // glPushMatrix();  //ouping the Quad
    T->TextureBinder();

    glTranslatef(xPos,yPos,zPos);
    glRotatef(xRotation,1.0,0.0,0.0);
    glRotatef(yRotation,0.0,1.0,0.0);
    glRotatef(zRotation,0.0,0.0,1.0);
    glScalef(xSize,ySize,1);

    glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(verticies[0].x, verticies[0].y,verticies[0].z);
      glTexCoord2f(xMax,yMax);
      glVertex3f(verticies[1].x, verticies[1].y,verticies[1].z);
      glTexCoord2f(xMax,yMin);
      glVertex3f(verticies[2].x, verticies[2].y,verticies[2].z);
      glTexCoord2f(xMin, yMin);
      glVertex3f(verticies[3].x, verticies[3].y,verticies[3].z);
    glEnd();
  //  glPopMatrix();

}

void _player::initPlayer(char *fileName)
{
   // T->TextureBinder();


   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    T->loadTexture(fileName);
    tmr->start();
}

void _player::hungerlower(){
if(tmr->getTicks()>60)
                {
hunger = hunger - hungerrate;
if(hunger <= 0){
//cout << "Dead" << endl;
}
if(health <= 0)
//    cout << "No Health" << endl;
                tmr->reset();
                }
}


void _player::actions()
{
    switch(action)
    {

        case 0:
                frames= 8.0;
                if(tmr->getTicks()>60)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.125;
                yMax= 0.25;
                xPos = xPos -xMove;
                if(xMax>=1){xMin=0.0; xMax=1/frames;}

                tmr->reset();
                }

         break;

        case 1:
               frames= 8.0;
                if(tmr->getTicks()>60)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.0;
                yMax= 0.125;
                xPos = xPos +xMove;

                if(xMax>=1){xMin=0.0; xMax=1.0/frames;}

                tmr->reset();
                }

            break;

        case 3:
            if(tmr->getTicks()>60)
                {
             frames= 9.0;
             xMin=8/frames;
             yMin=0.5;
             yMax=0.666;
             xMax=1.0;
             yPos = yPos + xMove/2;
             tmr->reset();
                }
            break;
        case 2:
            if(tmr->getTicks()>60)
                {
             frames= 9.0;
             xMin=8/frames;
             yMin=0.5;
             yMax=0.666;
             xMax=1.0;
             yPos = yPos - xMove/2;
             tmr->reset();
                }
            break;
        case 4:

                if(tmr->getTicks()>60)
                {
                    frames= 8.0;
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.125;
                yMax= 0.25;
                xPos = xPos -xMove/2;
                if(xMax>=1){xMin=0.0; xMax=1/frames;}

             tmr->reset();
                }
                break;
        case 5:
               frames= 8.0;
                if(tmr->getTicks()>60)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.0;
                yMax= 0.125;
                xPos = xPos +xMove/2;

                if(xMax>=1){xMin=0.0; xMax=1.0/frames;}

                tmr->reset();
                }
                break;
        case 6:
               frames= 8.0;
                if(tmr->getTicks()>20)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.0;
                yMax= 0.125;
                //xPos = xPos +xMove;

                if(xMax>=1){xMin=0.0; xMax=1.0/frames;}

                tmr->reset();
                }
                if(skillpoints > 1 && xMove < .2){
                xMove = xMove + .01;
                //skillpoints = skillpoints - 1;
                }

            break;
        case 7:
               frames= 8.0;
                if(tmr->getTicks()>20)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.0;
                yMax= 0.125;
                //xPos = xPos +xMove;

                if(xMax>=1){xMin=0.0; xMax=1.0/frames;}

                tmr->reset();
                }
                if(skillpoints > 1){
                strength = strength + 5;
                //skillpoints = skillpoints - 1;
                }

            break;
        case 8:
               frames= 8.0;
                if(tmr->getTicks()>20)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.0;
                yMax= 0.125;
                //xPos = xPos +xMove;

                if(xMax>=1){xMin=0.0; xMax=1.0/frames;}

                tmr->reset();
                }
                if(skillpoints > 1){
                cuteness = cuteness + .1;
                //skillpoints = skillpoints - 1;
                }

            break;

        case 9:
               frames= 8.0;
                if(tmr->getTicks()>20)
                {
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMin= 0.0;
                yMax= 0.125;
                //xPos = xPos +xMove;

                if(xMax>=1){xMin=0.0; xMax=1.0/frames;}

                tmr->reset();
                }
                //if(skillpoints > 1){
                skillpoints = skillpoints + 100;
                //skillpoints = skillpoints - 1;
              //  }

            break;


    }

}
