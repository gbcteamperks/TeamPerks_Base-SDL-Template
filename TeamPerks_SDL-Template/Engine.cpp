#include "Engine.h"
#include <iostream>
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
using namespace std;

Engine::Engine() :m_Running(false) { cout << "Engine class constructed!" << endl; }
Engine::~Engine() {}

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				cout << "!renderer created"<<endl;
			}
			else
			{
				return false; // Renderer init fail.
			}
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_Keystates = SDL_GetKeyboardState(nullptr);

	m_Running = true; // Everything is okay, start the engine.
	cout << "Init success!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::waitForTheNextFrame()		//check for next frame
{
	Uint32 gameTimeMs = SDL_GetTicks();
	m_timeSinceLastFrame = gameTimeMs - m_lastFrameStartTimeMs;

	if (m_timeSinceLastFrame < m_frameDelayMs)
	{
		SDL_Delay(m_frameDelayMs - m_timeSinceLastFrame);
	}

	m_frameEndTimeMs = SDL_GetTicks();
	m_deltaTime = (m_frameEndTimeMs - m_lastFrameStartTimeMs) / 1000.f;
	m_gameTime = m_frameEndTimeMs / 1000.f;
	m_lastFrameStartTimeMs = m_frameEndTimeMs;
}

void Engine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_Running = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			switch (event.key.keysym.sym)
			{
				case SDLK_a:
				case SDLK_LEFT:
					m_pSprite1->m_dst.x -= (m_movementSpeed * m_deltaTime);
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					m_pSprite1->m_dst.x += (m_movementSpeed * m_deltaTime);
					break;

				case SDLK_w:
				case SDLK_UP:
					m_pSprite1->m_dst.y -= (m_movementSpeed * m_deltaTime);
					break;

				case SDLK_s:
				case SDLK_DOWN:
					m_pSprite1->m_dst.y += (m_movementSpeed * m_deltaTime);
					break;

				case SDLK_ESCAPE:
					m_Running = false;
					break;
			}
			break;
		}
	}
}

// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_Keystates != nullptr)
	{
		if (m_Keystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Engine::Update()
{

}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	// Render stuff.
	m_spriteManager.drawAll();
	// Draw anew.
	SDL_RenderPresent(m_pRenderer);
}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

int Engine::Run()
{
	if (m_Running) // What does this do and what can it prevent?
		return -1;
	if (Init("Team Perks - Base Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;

	m_pSprite1 = new Sprite(m_pRenderer, "Resources/Visual/pizza.png", 500, 489, 500, 489, 1);
	m_pSprite1->setSize(200, 200);
	m_pSprite1->setPosition(410, 285);
	m_spriteManager.add(m_pSprite1);
	while (m_Running) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		waitForTheNextFrame();
		if (m_Running)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instance()
{
	static Engine instance; // C++11 will prevent this line from running more than once. Magic statics.
	return instance;
}

SDL_Renderer* Engine::GetRenderer() { return m_pRenderer; }
