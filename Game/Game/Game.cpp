#include "Game.h"

Game::Game(MODE gamemode) {
	switch (gamemode) {//渡されたゲームの種類によって変更する
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
		//エラー
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