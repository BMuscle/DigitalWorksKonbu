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

	isStop = false;
	TextureAsset::Register(U"stopback", U"resources/images/items/game/stopback.png");
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
	if (MySocketServer::isConnection()) {//�R���g���[���[�R�l�N�V�����m����
		if (isStop) {
			isStop = false;//���Q�[���X�g�b�v����
		}
		else {
			minigame->update();//�Q�[���i�s
		}
	}
	else if(!isStop){//�R�l�N�V�����ؒf�@���@�܂��Q�[������~����Ă��Ȃ�
		minigame->stopGame();//��~����
		isStop = true;
	}
}
void Game::draw(void) {
	minigame->draw();
	if (isStop) {
		TextureAsset(U"stopback").drawAt(Window::ClientCenter());
	}
}