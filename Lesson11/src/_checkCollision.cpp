#include "_checkCollision.h"

_checkCollision::_checkCollision()
{
    //ctor
}

_checkCollision::~_checkCollision()
{
    //dtor
}

bool _checkCollision::isCollisionRadius(float xPos, float yPos, float xPos1, float yPos1, float r, float r1)
{
  if(sqrt(pow((xPos-xPos1),2)+pow((yPos-yPos1),2))<(r+r1))return true;
  else return false;
}

bool _checkCollision::isCollisioFloor(float, float, float)
{

}

bool _checkCollision::isCollisionrayCircle(float, float, float)
{

}
