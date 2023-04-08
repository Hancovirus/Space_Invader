#ifndef TEXTURE_H
#define TEXTURE_H


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "SDL_ttf.h"

using namespace std;

static const int SCREEN_WIDTH = 732;
static const int SCREEN_HEIGHT = 720;

class Texture
{
	public:
		//Initializes variables
		Texture();

		//Deallocates memory (giai phong bo nho)
		~Texture();

		//Loads image from file (load anh tu file)
		bool loadFromFile( std::string path,SDL_Renderer* m_Renderer );

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* Font, SDL_Renderer* m_Renderer );

        //Deallocates texture (giai phong anh)
		void free();

		//Renders texture at given point (toa do anh)
		void render( int x, int y,SDL_Renderer* m_Renderer );

		void renderText(SDL_Renderer* m_Renderer, int x, int y, SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip  );

		//Gets image dimensions (lay kick thuoc anh)
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* m_Texture;

		//Image dimensions
		int m_Width;
		int m_Height;
};

#endif // TEXTURE_H
