#include "ShoeKick.h"
#include <Siv3D.hpp>
#include "MyKey.h"
#include <windows.h>
#include "MySocketServer.h"


ShoeKick::ShoeKick(void) {
	//アセットへロード
	FontAsset::Register(U"shoekickfont", 70);
	FontAsset::Preload(U"shoekickfont");
	TextureAsset::Register(U"shoekickback", U"resources/images/backs/shoekick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_title", U"resources/images/items/game/shoekick/title.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_kick", U"resources/images/items/game/shoekick/kick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_fly", U"resources/images/items/game/shoekick/fry.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_fall", U"resources/images/items/game/shoekick/fall.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_sunny", U"resources/images/items/game/shoekick/sunny.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_rain", U"resources/images/items/game/shoekick/rain.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_cloudy", U"resources/images/items/game/shoekick/cloudy.png", AssetParameter::LoadAsync());

	nowScene = TITLE;//初期シーンセット
	nextScene = TITLE;

}
ShoeKick::~ShoeKick(void) {
	FontAsset::Unregister(U"shoekickfont");
	TextureAsset::Unregister(U"shoekickback");
	delete backAudio;
}
bool ShoeKick::isReady(void) {	//ロード終了してもいいかどうか
	if (TextureAsset::IsReady(U"shoekickback")) {
		return true;
	}
	return false;
}
void ShoeKick::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/shoekick.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void ShoeKick::update(void) {	//計算処理
	if (nowScene != nextScene) {
		changeScene();
	}
	switch (nowScene) { 
	case TITLE:/*タイトル*/

		if (MyKey::getDecisionKey()) { //エンター押されたらける画面に移行する
			setNextScene(KICK);
		}
		break;

	case KICK: /*足を振って速さを取ってきて飛ばすまでの画面*/
		
		
		while (countDown<0) {

			Sleep(3 * 1000);
			countDown = countDown - 1;
			

		};

		setNextScene(FLY);
		break;
	case FLY:/*出た速さから距離を取って靴を飛ばす画面*/
		//出た速さに何かしらをかけて距離を出す
		distance = 300;

		while (distance == x) {

			x++;
		}

		setNextScene(FALL);
		break;


	case FALL:/*靴を落下させる画面*/

		if (MyKey::getDecisionKey()) { //エンター押されたら天気の画面に移行する
			setNextScene (RESULT);
		}
		break;

	case RESULT:/*距離によって表示する天気を変える・もう一度ゲームをするかマップに戻るかを確認する画面*/
		//もう一度ゲームをプレイするかマップに戻るか方向キーで選択してエンターで決定 


		break;

	}

}
void ShoeKick::draw(void) {	//描画処理

	switch (nowScene) { //画面切り替えのフラグです

	case TITLE://home
		TextureAsset(U"shoekick_title").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	case KICK://keru
		TextureAsset(U"shoekick_kick").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		FontAsset(U"shoekickfont")(U"カウントダウン" + Format(countDown)).drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2, ColorF(0, 0, 0));
		break;
	case FLY://tonnderu
		TextureAsset(U"shoekick_fly").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	case FALL:
		TextureAsset(U"shoekick_fall").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	case RESULT:
		if (distance % 3 == 0) {
			TextureAsset(U"shoekick_sunny").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

		}
		else if (distance % 3 == 1) {
			TextureAsset(U"shoekick_rain").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

		}
		else{
			TextureAsset(U"shoekick_cloudy").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		break;
	}
}
void ShoeKick::outputResult(void) {//結果をDBへ出力する

}

void ShoeKick::stopGame() {	//ゲームを一時中断する

}
void ShoeKick::changeScene() {
	switch (nowScene)//終了処理
	{
	case ShoeKick::TITLE:
		break;
	case ShoeKick::KICK:
		break;
	case ShoeKick::FLY:
		break;
	case ShoeKick::FALL:
		break;
	case ShoeKick::RESULT:
		break;
	}
	switch (nextScene)//初期化処理
	{
	case ShoeKick::TITLE:
		break;
	case ShoeKick::KICK:
		countDown = 3;
		break;
	case ShoeKick::FLY:
		distance = 0;
		x = 0;
		break;
	case ShoeKick::FALL:
		break;
	case ShoeKick::RESULT:
		break;
	}
	nowScene = nextScene;
}
void ShoeKick::setNextScene(SCENE next) {
	nextScene = next;
}





