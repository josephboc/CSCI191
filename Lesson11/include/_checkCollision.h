#ifndef _CHECKCOLLISION_H
#define _CHECKCOLLISION_H

#include <math.h>

class _checkCollision
{
    public:
        _checkCollision();
        virtual ~_checkCollision();

        bool isCollisionRadius(float, float,float,float,float, float);
        // position and radius of both objects
        bool isCollisioFloor(float,float,float);
        bool isLinearCollision(float, float);
        // position, radius and wall
        bool isCollisionrayCircle(float,float,float);
        // position, ray position and circle
    protected:

    private:
};

#endif // _CHECKCOLLISION_H
