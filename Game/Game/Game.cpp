#include "Game.h"

Game::Game(MODE gamemode) {
	switch (gamemode) {//“n‚³‚ê‚½ƒQ[ƒ€‚Ìí—Ş‚É‚æ‚Á‚Ä•ÏX‚·‚é
	case MODE::SOCCER:
		minigame = new Soccer();
		break;
	case MODE::DODGE:
		minigame = new Dodge();
		break;
	case MODE::SHOEKICK:
		minigame = new ShoeKick();
		break;
	default:
		//ƒGƒ‰[
		break;
	}
}
Game::~Game(void) {
	delete minigame;
}
bool Game::isReady(void) {
	if (minigame->isReady()) {
		return true;
	}
	return false;
}
void Game::start(void) {
	minigame->start();
}
void Game::update(void) {
	minigame->update();
}
void Game::draw(void) {
	minigame->draw();
}