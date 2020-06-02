#include "SpriteManager.h"
#include <algorithm>
#include <iostream>

SpriteManager::SpriteManager()
{
	//default constructor
}

SpriteManager::~SpriteManager()
{
	//default destructor
}


//clean all sprites - as in remove
void SpriteManager::clean()
{
	for (int i = 0; i < m_pSprites.size(); i++)
	{
		m_pSprites[i]->cleanup();
		delete m_pSprites[i];
	}
}

//update all sprites
void SpriteManager::updateAll(float deltaTime)
{
	for (int i = 0; i < m_pSprites.size(); i++)
	{
		if (m_pSprites[i] != nullptr)
		{
			m_pSprites[i]->update(deltaTime);
		}
	}
}

//draw all the sprites
void SpriteManager::drawAll()
{
	for (int i = 0; i < m_pSprites.size(); i++)
	{
		m_pSprites[i]->draw();
	}
}

//push sprite into sprite manager vector
void SpriteManager::add(Sprite* spriteToAdd)
{
	m_pSprites.push_back(spriteToAdd);
	spriteToAdd->m_pSpriteManager = this;
}