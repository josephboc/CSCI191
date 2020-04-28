#ifndef _MODEL_H
#define _MODEL_H

#include <windows.h>
#include<GL/glut.h>

#include<iostream>

using namespace std;

class _Model
{
    public:
        _Model();
        virtual ~_Model();

        double rotateX;
        double rotateY;
        double rotateZ;

        double posX;
        double posY;
        double posZ;

        double scale;

        void initModel();

        void drawModel();


    protected:

    private:
};

#endif // _MODEL_H
