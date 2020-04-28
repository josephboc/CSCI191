#include "_model.h"
#include<_textureLoader.h>

_textureLoader *tex = new _textureLoader();

_Model::_Model()
{
    //ctor

    rotateX=0.0;
    rotateY=0.0;
    rotateZ=0.0;

    posX=2.5;
    posY=2.0;
    posZ=0.0;

    scale=0.5;


}

void _Model::initModel()
{
   // tex->TextureBinder();
    tex->loadTexture("images/2.jpg");
}


_Model::~_Model()
{
    //dtor
}
void _Model::drawModel()
{
    tex->TextureBinder();
    glColor3f(1.0,0.5,0.2);
    glPushMatrix();
    glScaled(scale,scale,scale);
    glTranslated(posX,posY,posZ);
    glRotated(rotateX,1,0,0);
    glRotated(rotateY,0,1,0);
    glRotated(rotateZ,0,0,1);

    glutSolidTeapot(1.5);

   // glutSolidTorus(0.5,1.5,40,40);

    glPopMatrix();
}
