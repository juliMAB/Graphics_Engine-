#include "Game.h"

Game::Game() {
}
Game::~Game() {
}

void Game::Init() {
	Awake();
	Start();
}
void Game::Play() {
	Update();
}
void Game::End() {
	
}