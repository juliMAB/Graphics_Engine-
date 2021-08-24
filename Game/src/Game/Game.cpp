#include "Game.h"
#include <time.h>
#include <iostream>

Game::Game() {

}
Game::~Game() {
	
}
void Game::Start() {
	StartEngine();
	//GetRenderer()->SetClearWindow(1, 0, 0, 1);
}
void Game::Play() {
	UpdateEngine();
}
void Game::Update() {
	GetRenderer()->ClearWindow();
	GetRenderer()->DrawTriangle(0.5f);
	GetRenderer()->SwapBuffers();	
}
void Game::End() {
	EndEngine();
}