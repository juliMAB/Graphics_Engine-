#include "Game.h"
#include <time.h>
#include <iostream>


	Game::Game()
	{

	}
	Game::~Game() 
	{
		
	}
	void Game::Start() 
	{
		StartEngine();
	}
	void Game::Play() 
	{
		UpdateEngine();
	}

	void Game::Update() 
	{
		GetWindow()->ClearWindow(0.0f, 0.0f, 1.0f, 1.0f);
		GetWindow()->SwapBuffers();
	}
	void Game::End() 
	{
		EndEngine();
	}
