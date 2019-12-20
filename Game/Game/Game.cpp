#include "Game.h"

Game::Game(MODE gamemode) {
	switch (gamemode) {//�n���ꂽ�Q�[���̎�ނɂ���ĕύX����
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
		//�G���[
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