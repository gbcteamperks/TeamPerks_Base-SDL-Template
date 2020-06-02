#include "Sprite.h"
#include <iostream>


//default base constructor, destructor
Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

//overloaded - renderer file sizex/sizey width and height .. frames
Sprite::Sprite(SDL_Renderer* s_pRenderer, const char* filename, int sizeX, int sizeY, int width, int height, int num_frames)
{
	m_pRenderer = s_pRenderer;
	//*m_pSpriteTexture = IMG_LoadTexture(m_pRenderer, filename);
	m_pSpriteTexture = std::make_shared<SDL_Texture*>(IMG_LoadTexture(m_pRenderer, filename));

	SDL_QueryTexture(*m_pSpriteTexture, NULL, NULL, &m_src.w, &m_src.h);

	m_src.x = 0;
	m_src.y = 0;
	m_src.w = width;
	m_src.h = height;

	m_dst.x = 0;
	m_dst.y = 0;
	m_dst.w = sizeX;
	m_dst.h = sizeY;

	m_frames = num_frames;
}


//methods---------


//setters
void Sprite::setPosition(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;
}

//set size for our sprite
void Sprite::setSize(int x, int y)
{
	m_dst.w = x;
	m_dst.h = y;
}

//get position of Sprite
SDL_Rect Sprite::m_getPosition()
{
	return m_dst;
}

//get size of sprite
SDL_Rect Sprite::m_getSize()
{
	return m_dst;
}

//draw sprite
void Sprite::draw()
{
	SDL_RenderCopy(m_pRenderer, *m_pSpriteTexture, &m_src, &m_dst);
}

//clean sprite/destroy sprite
void Sprite::cleanup()
{
	SDL_DestroyTexture(*m_pSpriteTexture);
}

void Sprite::update(float deltaTime)
{
}