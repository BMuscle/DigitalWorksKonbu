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
	if (MySocketServer::isConnection()) {//コントローラーコネクション確立時
		if (isStop) {
			isStop = false;//一回ゲームストップ解除
		}
		else {
			minigame->update();//ゲーム進行
		}
	}
	else if(!isStop){//コネクション切断　＆　まだゲームが停止されていない
		minigame->stopGame();//停止処理
		isStop = true;
	}
}
void Game::draw(void) {
	minigame->draw();
	if (isStop) {
		TextureAsset(U"stopback").drawAt(Window::ClientCenter());
	}
}