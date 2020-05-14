#include "_parallax.h"



_parallax::_parallax()
{
    //ctor
    //initialize the texture coordinates
    xMax =0.0;
    yMax =0.0;
    xMin =1;
    yMin =1;
}

_parallax::~_parallax()
{
    //dtor
}
void _parallax::drawSquare(float width, float height)
{

    glColor3f(1.0,1.0,1.0);
    bTex->TextureBinder();
    glBegin(GL_POLYGON);
    glTexCoord2f(xMin,yMin);
    glVertex3f(-width/height, -1, -10.0);
    glTexCoord2f(xMax,yMin);
    glVertex3f(width/height, -1, -10.0);
    glTexCoord2f(xMax,yMax);
    glVertex3f(width/height, 1, -10.0);
    glTexCoord2f(xMin,yMax);
    glVertex3f(-width/height, 1, -10.0);

    glEnd();


}

void _parallax::parallaxInit(char* fileName)
{
    bTex->loadTexture(fileName);
}

void _parallax::scroll(bool Auto, string dir, float speed)
{
   if(Auto)     // To Address Automatic movement of the background
   {
       if(dir=="up")  // keyword "up"
       {
           yMin -=speed;
           yMax -=speed;
       }

        if(dir=="down")  // keyword "down"
       {
           yMin +=speed;
           yMax +=speed;
       }
        if(dir=="left")  // keyword "left"
       {
           xMin -=speed;
           xMax -=speed;
       }
        if(dir=="right")  // keyword "right"
       {
           xMin +=speed;
           xMax +=speed;
       }
   }
}
