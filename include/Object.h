#ifndef OBJECT_H
#define OBJECT_H
#include "Texture.h"

class Object
{
    public:
        Object();
        void load( int width, int height, std::string textureID);
        void draw(SDL_Renderer* m_Renderer);

        void clean();

        float m_PosX;
        float m_PosY;


    protected:

        int m_width;
		int m_height;
        string m_textureID;
};

#endif // OBJECT_H
