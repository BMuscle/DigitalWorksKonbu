#include "SelectMode.h"

#define SELECT_INTERVAL_COUNT (60 * 0.3)

SelectMode::SelectMode(void) {
	//アセットへロード
	FontAsset::Register(U"selectmodefont", 70);
	FontAsset::Preload(U"selectmodefont");
	TextureAsset::Register(U"selectmodeback", U"resources/images/backs/selectmode.png", AssetParameter::LoadAsync());
	//モードそれぞれ標準の画像
	textureName[(int)MODE::SOCCER] = U"soccer";
	textureName[(int)MODE::DODGE] = U"dodge";
	textureName[(int)MODE::SHOEKICK] = U"shoekick";
	textureName[(int)MODE::GACHA] = U"gacha";
	textureName[(int)MODE::MYROOM] = U"myroom";

	button[(int)MODE::SOCCER] = new MyImageButton(U"resources/images/items/selectmode/"  + textureName[(int)MODE::SOCCER],    U"", 10, 1630, 910);
	button[(int)MODE::DODGE]  = new MyImageButton(U"resources/images/items/selectmode/"   + textureName[(int)MODE::DODGE],    U"", 10, 1140, 210);
	button[(int)MODE::SHOEKICK] = new MyImageButton(U"resources/images/items/selectmode/" + textureName[(int)MODE::SHOEKICK], U"", 10, 1680, 200);
	button[(int)MODE::GACHA]  = new MyImageButton(U"resources/images/items/selectmode/" + textureName[(int)MODE::GACHA ],     U"", 10, 235, 920);
	button[(int)MODE::MYROOM] = new MyImageButton(U"resources/images/items/selectmode/" + textureName[(int)MODE::MYROOM],     U"", 10, 250, 200);

	//モードそれぞれ選択されているときの説明用画像
	TextureAsset::Register(textureName[(int)MODE::SOCCER] + U"txt", U"resources/images/items/selectmode/soccertxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::DODGE] + U"txt", U"resources/images/items/selectmode/dodgetxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::SHOEKICK] + U"txt", U"resources/images/items/selectmode/shoekicktxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::GACHA] + U"txt", U"resources/images/items/selectmode/gachatxt.png", AssetParameter::LoadAsync());
	TextureAsset::Register(textureName[(int)MODE::MYROOM] + U"txt", U"resources/images/items/selectmode/myroomtxt.png", AssetParameter::LoadAsync());
	
	//オーディオアセット
	AudioAsset::Register(U"selectmodemove", U"resources/musics/items/selectmode/move.wav");

	//変数の初期化
	selectedMode = MODE::MYROOM;//初期の選択状態をマイルームにする。

}
SelectMode::~SelectMode(void) {
	FontAsset::Unregister(U"selectmodefont");
	TextureAsset::Unregister(U"selectmodeback");
	for (int i = 0; i < (int)MODE::SIZE; i++) {
		delete button[i];
		TextureAsset::Unregister(textureName[i] + U"txt");
	}

	delete backAudio;
	AudioAsset::Unregister(U"selectmodemove");
}
bool SelectMode::isReady(void) {
	if (TextureAsset::IsReady(U"selectmodeback")) {
		for (int i = 0; i < (int)MODE::SIZE; i++) {
			if (!(TextureAsset::IsReady(textureName[i] + U"txt") &&
				button[i]->isReady())) {
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
	backAudio->setVolume(0.1);
	backAudio->play();
}
void SelectMode::update(void) {
	updateFrameCount();//フレーム数カウント更新
	if (MyKey::getReturnKey()) {
		MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);
	}else if (MyKey::getDecisionKey()) {
		if (getSelectedMode() == MODE::MYROOM) {//マイルームシーンへ移行
			MySceneManager::setNextScene(SCENE::MYROOM);
		}
		else if(getSelectedMode() == MODE::GACHA){//ガチャへ移行
			MySceneManager::setNextScene(SCENE::GACHA);
		}
		else {//ゲームへ移行
			MySceneManager::setNextScene(SCENE::GAME);
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
	else {
		moveSelectMode();//モード切替処理
	}
}
void SelectMode::draw(void) {

	//背景描画
	TextureAsset(U"selectmodeback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	//選択部分の表示
	for (int i = 0; i < (int)MODE::SIZE; i++) {
		button[i]->drawNotWord(getSelectedMode() == (MODE)i);
	}

	//現在選択されているものの内容画像を表示する
	TextureAsset(textureName[(int)getSelectedMode()] + U"txt").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.62, AlphaF(1));
}

MODE SelectMode::getSelectedMode() {//選択されているモードを返す。シーン移行時に受け渡す
	return selectedMode;
}


void SelectMode::moveSelectMode() {
	bool moveFlag = false;
	if (MyKey::getUpKeyDown()) {//上キー入力
		switch (selectedMode) {
		case MODE::SOCCER:
			selectedMode = MODE::SHOEKICK;
			break;
		case MODE::GACHA:
			selectedMode = MODE::MYROOM;
			break;
		}
		moveFlag = true;
	}
	else if (MyKey::getDownKeyDown()) {//下キー入力
		switch (selectedMode) {
		case MODE::DODGE:
			selectedMode = MODE::SOCCER;
			break;
		case MODE::MYROOM:
			selectedMode = MODE::GACHA;
			break;
		case MODE::SHOEKICK:
			selectedMode = MODE::SOCCER;
			break;
		}
		moveFlag = true;
	}
	else if (MyKey::getLeftKeyDown()) {//左キー入力
		switch (selectedMode) {
		case MODE::DODGE:
			selectedMode = MODE::MYROOM;
			break;
		case MODE::SHOEKICK:
			selectedMode = MODE::DODGE;
			break;
		case MODE::SOCCER:
			selectedMode = MODE::GACHA;
			break;
		}
		moveFlag = true;
	}
	else if (MyKey::getRightKeyDown()) {//右キー入力
		switch (selectedMode) {
		case MODE::DODGE:
			selectedMode = MODE::SHOEKICK;
			break;
		case MODE::MYROOM:
			selectedMode = MODE::DODGE;
			break;
		case MODE::GACHA:
			selectedMode = MODE::SOCCER;
			break;
		}
		moveFlag = true;
	}

	if (moveFlag) {
		moveEffect();
	}
	
}

void SelectMode::updateFrameCount(){
	frameCount++;
	if (frameCount > 60 * 3000) {//上限値チェック
		frameCount = 0;
	}
}

void SelectMode::moveEffect() {
	AudioAsset(U"selectmodemove").setPosSec(0);
	AudioAsset(U"selectmodemove").setVolume(0.1);
	AudioAsset(U"selectmodemove").play();
}