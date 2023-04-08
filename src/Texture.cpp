#include "Texture.h"

 Texture::Texture()
{
	//Initialize
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* Font, SDL_Renderer* m_Renderer )
{
    free();
    SDL_Surface* text_surface=TTF_RenderText_Solid(Font,textureText.c_str(),textColor);
    if(text_surface)
    {
        m_Texture=SDL_CreateTextureFromSurface(m_Renderer,text_surface);
        m_Width=text_surface->w;
        m_Height=text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return m_Texture!=NULL;
}

bool Texture::loadFromFile( std::string path,SDL_Renderer* m_Renderer )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( m_Renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	m_Texture = newTexture;
	return m_Texture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if( m_Texture != NULL )
	{
		SDL_DestroyTexture( m_Texture );
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void Texture::render( int x, int y,SDL_Renderer* m_Renderer )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };
	SDL_RenderCopy( m_Renderer, m_Texture, NULL, &renderQuad );
}

void Texture::renderText(SDL_Renderer* m_Renderer ,int x, int y, SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip  )
{
	//Set rendering space and render to screen
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( m_Renderer, m_Texture, clip, &renderQuad, angle, center, flip );
}

//get the width/height of the texture
int Texture::getWidth()
{
	return m_Width;
}

int Texture::getHeight()
{
	return m_Height;
}
