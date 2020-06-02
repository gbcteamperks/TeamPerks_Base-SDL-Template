#pragma once
#include <vector>
#include "Sprite.h"

class SpriteManager
{
	//Sprite Manager

private:

		

public:


	//constructor, destructor.
	SpriteManager();
	~SpriteManager();

	//vectors to control pointers of those sprites
	std::vector<Sprite*> m_pSprites;

	//add sprites
	void add(Sprite* spriteAdd);

	//draw sprites
	void drawAll();

	// update all method
	void updateAll(float deltaTime);
	
	// clean those sprites
	void clean();
};

