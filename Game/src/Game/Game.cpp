#include "Game.h"

Game::Game() { 
	
}
Game::~Game() {

}
void Game::Init() {
	BaseGame::Init(wt, ht, "In Lovyng");
	std::cout << "+Game";
}

void Game::Deinit() {
	BaseGame::Deinit();
	std::cout << "-Game";
}
void Game::Update()
{	
	BaseGame::EndUpdate();
}
void Game::Draw() {
	BaseGame::EndDraw();
}
