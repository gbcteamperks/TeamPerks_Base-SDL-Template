#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Sprite.h"
#include "SpriteManager.h"

// Do not include any macros, initialized properties or full function definitions in this header.

class Engine
{
private: // Private properties.
	bool m_Running; // Loop control flag.
	const Uint8* m_Keystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.
	Sprite* m_pSprite1;
	SpriteManager m_spriteManager;

private: // Private methods.
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
public: // Public methods.
	Engine();
	~Engine();
	int Run();
	static Engine& Instance(); // This static method creates the static instance that can be accessed 'globally'
	bool KeyDown(SDL_Scancode c);
	SDL_Renderer* GetRenderer();

	//public properties
public:
	//-------------------frame rate and delta time---------------
	int m_targetFramerate = 30;
	int m_frameDelayMs = 1000 / m_targetFramerate;
	Uint32 m_frameEndTimeMs;
	Uint32 m_lastFrameStartTimeMs;
	Uint32 m_timeSinceLastFrame;
	float m_deltaTime;
	float m_gameTime = 0;
	float m_movementSpeed = 200;
	//deltatime wait for next frame
	void waitForTheNextFrame();
};