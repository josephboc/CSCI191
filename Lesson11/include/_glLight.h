#ifndef _GLLIGHT_H
#define _GLLIGHT_H

#include<_glScene.h>


class _glLight:_glScene
{
    public:
        _glLight(GLenum);
        virtual ~_glLight();


        GLfloat light_ambient[4]  = { 0.0f, 0.0f, 0.0f, 1.0f };  // Environment Light
        GLfloat light_diffuse[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };  // Shadow Light
        GLfloat light_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Shininess
        GLfloat light_position[4] = { 2.0f, 5.0f, 5.0f, 0.0f };  // Placing the light

        GLfloat mat_ambient[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };  // Material env color
        GLfloat mat_diffuse[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };  // Material Diffuse color
        GLfloat mat_specular[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };  // Material shininess
        GLfloat high_shininess[1] = { 100.0f };                  // amount of shininess


        GLvoid setLight(GLenum);                                  // Set Light Model
    protected:

    private:
};

#endif // _GLLIGHT_H
