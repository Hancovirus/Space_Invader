#include "Object.h"

Texture m_Object;

Object::Object() {


}

 void Object::load( int width, int height, std::string textureID)
{

    m_width = width;
    m_height = height;
    m_textureID = textureID;
}

void Object::draw(SDL_Renderer* m_Renderer) {

    m_Object.loadFromFile(m_textureID, m_Renderer);
    m_Object.render(m_PosX, m_PosY, m_Renderer);

}


void Object::clean()
{
    m_Object.free();
}
