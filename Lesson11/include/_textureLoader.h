#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include<SOIL.h>
#include<GL/gl.h>
#include<iostream>
using namespace std;

class _textureLoader
{
    public:
        _textureLoader();
        virtual ~_textureLoader();

        void loadTexture(char *);
        void TextureBinder();
        int width,height;
        unsigned char *image;
        GLuint tex;

    protected:

    private:
};

#endif // _TEXTURELOADER_H
