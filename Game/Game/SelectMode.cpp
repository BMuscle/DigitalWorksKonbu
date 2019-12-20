#include "SelectMode.h"

#define SELECT_INTERVAL_COUNT (60 * 0.3)

SelectMode::SelectMode(void) {
	//アセットへロード
	FontAsset::Register(U"selectmodefont", 70);
	FontAsset::Preload(U"selectmodefont");
	TextureAsset::Register(U"selectmodeback", U"resources/images/backs/selectmode.png", AssetParameter::LoadAsync());
	//モードそれぞれ標準の画像
	textureName[(int)MODE::SOCCER] = U"selectmodesoccer";
	textureName[(int)MODE::DODGE] = U"selectmodedodge";
	textureName[(int)MODE::SHOEKICK] = U"selectmodeshoekick";
	textureName[(int)MODE::GACHA] = U"selectmodegacha";
	textureName[(int)MODE::MYROOM] = U"selectmodemyroom";
	TextureAsset::Register(textureName[(int)MODE::SOCCER], U"resources/images/items/selectmode/soccer.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE], U"resources/images/items/selectmode/dodge.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK], U"resources/images/items/selectmode/shoekick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA], U"resources/images/items/selectmode/gacha.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM], U"resources/images/items/selectmode/myroom.png", AssetParameter::LoadAsync());
	//モードそれぞれ選択されているときの画像
	TextureAsset::Register(textureName[(int)MODE::SOCCER] + U"on", U"resources/images/items/selectmode/socceron.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE] + U"on", U"resources/images/items/selectmode/dodgeon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK] + U"on", U"resources/images/items/selectmode/shoekickon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA] + U"on", U"resources/images/items/selectmode/gachaon.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM] + U"on", U"resources/images/items/selectmode/myroomon.png", AssetParameter::LoadAsync());

	//モードそれぞれ選択されているときの説明用画像
	TextureAsset::Register(textureName[(int)MODE::SOCCER] + U"txt", U"resources/images/items/selectmode/soccertxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE] + U"txt", U"resources/images/items/selectmode/dodgetxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK] + U"txt", U"resources/images/items/selectmode/shoekicktxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA] + U"txt", U"resources/images/items/selectmode/gachatxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM] + U"txt", U"resources/images/items/selectmode/myroomtxt.png", AssetParameter::LoadAsync());
	
	//変数の初期化
	selectedMode = MODE::SOCCER;//初期の選択状態をサッカーにする。

}
SelectMode::~SelectMode(void) {
	FontAsset::Unregister(U"selectmodefont");
	TextureAsset::Unregister(U"selectmodeback");
	delete backAudio;
	for (int i = 0; i < (int)MODE::SIZE; i++) {
		TextureAsset::Unregister(textureName[i]);
		TextureAsset::Unregister(textureName[i] + U"on");
		TextureAsset::Unregister(textureName[i] + U"txt");
	}

}
bool SelectMode::isReady(void) {
	if (TextureAsset::IsReady(U"selectmodeback")) {
		for (int i = 0; i < (int)MODE::SIZE; i++) {
			if (!(TextureAsset::IsReady(textureName[i]) &&
				TextureAsset::IsReady(textureName[i] + U"on") &&
				TextureAsset::IsReady(textureName[i] + U"txt"))) {
				return false;
			}
		}
		return true;
	}
		
	return false;
}
void SelectMode::start(void) {
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/selectmode.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void SelectMode::update(void) {
	updateFrameCount();//フレーム数カウント更新
	if (MyKey::getDecisionKey()) {
		if (getSelectedMode() == MODE::MYROOM) {//マイルームシーンへ移行
			MySceneManager::setNextScene(SCENE::MYROOM);
		}
		else if(getSelectedMode() == MODE::GACHA){//ガチャへ移行
			MySceneManager::setNextScene(SCENE::GACHA);
		}
		else {//ゲームへ移行
			MySceneManager::setNextScene(SCENE::GAME);
		}
	}
	moveSelectMode();//モード切替処理
}
void SelectMode::draw(void) {
	constexpr Vec2 modeVec[5]{ //モードの画像の座標
				   Vec2(200, 200),//サッカー
				   Vec2(400,800),//ドッジボール
				   Vec2(1920/2,200),//靴飛ばし
				   Vec2(1400,800),//ガチャ
				   Vec2(1600,200) };//自分の部屋

	//背景描画
	TextureAsset(U"selectmodeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	//選択部分の表示
	TextureAsset(textureName[(int)MODE::SOCCER]).drawAt(modeVec[(int)MODE::SOCCER]);
	TextureAsset(textureName[(int)MODE::DODGE]).drawAt(modeVec[(int)MODE::DODGE]);
	TextureAsset(textureName[(int)MODE::SHOEKICK]).drawAt(modeVec[(int)MODE::SHOEKICK]);
	TextureAsset(textureName[(int)MODE::GACHA]).drawAt(modeVec[(int)MODE::GACHA]);
	TextureAsset(textureName[(int)MODE::MYROOM]).drawAt(modeVec[(int)MODE::MYROOM]);
	//現在選択されている画像を強調表示する
	TextureAsset(textureName[(int)getSelectedMode()] + U"on").drawAt(modeVec[(int)getSelectedMode()]);
	//現在選択されているものの内容画像を表示する
	TextureAsset(textureName[(int)getSelectedMode()] + U"txt").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
}

MODE SelectMode::getSelectedMode() {//選択されているモードを返す。シーン移行時に受け渡す
	return selectedMode;
}


void SelectMode::moveSelectMode() {
	if (MyKey::getUpKeyDown()) {//上キー入力
		switch (selectedMode) {
		case MODE::DODGE:
			selectedMode = MODE::SOCCER;
			break;
		case MODE::GACHA:
			selectedMode = MODE::MYROOM;
			break;
		}
	}
	else if (MyKey::getDownKeyDown()) {//下キー入力
		switch (selectedMode) {
		case MODE::SOCCER:
			selectedMode = MODE::DODGE;
			break;
		case MODE::SHOEKICK:
			selectedMode = MODE::GACHA;
			break;
		case MODE::MYROOM:
			selectedMode = MODE::GACHA;
			break;
		}
	}
	else if (MyKey::getLeftKeyDown()) {//左キー入力
		switch (selectedMode) {
		case MODE::SHOEKICK:
			selectedMode = MODE::SOCCER;
			break;
		case MODE::MYROOM:
			selectedMode = MODE::SHOEKICK;
			break;
		case MODE::GACHA:
			selectedMode = MODE::DODGE;
			break;
		}
	}
	else if (MyKey::getRightKeyDown()) {//右キー入力
		switch (selectedMode) {
		case MODE::SOCCER:
			selectedMode = MODE::SHOEKICK;
			break;
		case MODE::DODGE:
			selectedMode = MODE::GACHA;
			break;
		case MODE::SHOEKICK:
			selectedMode = MODE::MYROOM;
			break;
		}
	}
	
}

void SelectMode::updateFrameCount(){
	frameCount++;
	if (frameCount > 60 * 3000) {//上限値チェック
		frameCount = 0;
	}
}