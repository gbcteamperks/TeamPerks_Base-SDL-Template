#pragma once
#include<SDL_image.h>
#include<memory>

class SpriteManager;

class Sprite
{
private:

public:
	std::shared_ptr<SDL_Texture*> m_pSpriteTexture = nullptr;		//Sprite Texture
	//base constructor, destructor
	Sprite();
	~Sprite();

	//overloaded
	Sprite(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, int width, int height, int num_frames);

	//members-
	SDL_Rect m_dst;													//dst rect
	SDL_Rect m_src;													//src rect
	bool m_flag = false;											//basic flag
	int m_frames;													//frames
	SpriteManager* m_pSpriteManager = nullptr;						//SpriteManager
	SDL_Renderer* m_pRenderer = nullptr;							//Sprite Renderer
	

	//methods-
	//getters for position and size
	SDL_Rect m_getPosition();
	SDL_Rect m_getSize();

	//setters for position and size
	void setPosition(int x, int y);
	void setSize(int x, int y);

	//draw function
	void draw();

	//update function
	virtual void update(float deltaTime);

	//clean
	void cleanup();		//just in case
};

