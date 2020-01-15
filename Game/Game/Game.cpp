#include "Game.h"

//ポップアップのボタンの離れている間隔を定義
#define POPUP_INTERVAL (Window::ClientWidth() * 0.12)

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
	TextureAsset::Register(U"wordok", U"resources/images/items/game/ok.png");
	TextureAsset::Register(U"wordnot", U"resources/images/items/game/not.png");

	//ポップアップのボタン初期化
	popUpButton[(int)POPUP::RESTART] = new MyImageButton(U"resources/images/items/game/restart", U"", 0, (int)(Window::ClientWidth() / 2) + (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, true);
	popUpButton[(int)POPUP::NEXTMAP] = new MyImageButton(U"resources/images/items/game/nextmap", U"", 0, (int)(Window::ClientWidth() / 2) - (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, false);

	popUpState = POPUP::NONE;//ポップアップ選択の初期状態はNONEに
}
Game::~Game(void) {
	delete minigame;
	TextureAsset::Unregister(U"stopback");
	TextureAsset::Unregister(U"wordok");
	TextureAsset::Unregister(U"wordnot");
}
bool Game::isReady(void) {
	if (minigame->isReady() && 
		popUpButton[(int)POPUP::RESTART]->isReady() &&
		popUpButton[(int)POPUP::NEXTMAP]->isReady()) {
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
			if (MyKey::getRightKeyDown()) {
				popUpState = POPUP::RESTART;//ポップアップをマップへに
				GeneralSoundEffects::play(SE_NAME::CURSOR);
			}
			else if (MyKey::getLeftKeyDown()) {
				popUpState = POPUP::NEXTMAP;//ポップアップをマップへに
				GeneralSoundEffects::play(SE_NAME::CURSOR);
			}
		}
		else {
			minigame->update();//ゲーム進行
		}
	}
	else {//コネクション切断時
		if (isStop) {
			if (MyKey::getRightKeyDown()) {
				GeneralSoundEffects::play(SE_NAME::BACK);
			}
			else if (MyKey::getLeftKeyDown()) {
				popUpState = POPUP::NEXTMAP;//ポップアップをマップへに
				GeneralSoundEffects::play(SE_NAME::CURSOR);
			}
		}
		else {//始めて切断された時
			isStop = true;//trueに変更
			minigame->stopGame();//停止処理
			popUpState = POPUP::NEXTMAP;//ポップアップをマップへに
			GeneralSoundEffects::play(SE_NAME::CANCEL);
		}
	}

	if (isStop && MyKey::getDecisionKey()) {
		switch (popUpState)
		{
		case Game::POPUP::RESTART:
			isStop = false;//一回ゲームストップ解除
			popUpState = POPUP::NONE;//ポップアップをマップへに
		//ゲームrestart処理必須
			break;
		case Game::POPUP::NEXTMAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
}
void Game::draw(void) {
	minigame->draw();
	if (isStop) {

		//ポップアップ背景を描画
		TextureAsset(U"stopback").drawAt(Window::ClientWidth() * 0.5, Window::ClientHeight() * 0.45);

		if (MySocketServer::isConnection()) {//コントローラーコネクション確立時
			TextureAsset(U"wordok").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
		}
		else {//切断時
			TextureAsset(U"wordnot").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
		}

		switch (popUpState)
		{
		case POPUP::RESTART://YESが選択されているとき 選択状態を変更
			//描画処理
			popUpButton[(int)POPUP::RESTART]->drawNotWord(true);
			popUpButton[(int)POPUP::NEXTMAP]->drawNotWord(false);
			break;
		case POPUP::NEXTMAP://NOが選択されているとき 選択状態を変更
			//描画処理
			popUpButton[(int)POPUP::RESTART]->drawNotWord(false);
			popUpButton[(int)POPUP::NEXTMAP]->drawNotWord(true);
			break;
		}
	}
}