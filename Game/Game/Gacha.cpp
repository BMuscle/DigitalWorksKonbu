#include "Gacha.h"

constexpr int GACHA_PRICE = 500;

Gacha::Gacha(void) {
	//ロードエフェクトの初期化
	simpleLoadEffect = new SimpleLoadEffect();

	//アセットへロード
	FontAsset::Register(U"gachafont", 70, AssetParameter::LoadAsync());
	FontAsset::Preload(U"gachafont");

	TextureAsset::Register(U"gachaback", U"resources/images/backs/gacha.jpg", AssetParameter::LoadAsync());

	AudioAsset::Register(U"gachahandl", U"resources/musics/items/gacha/gacha.wav", AssetParameter::LoadAsync());
	//エフェクト管理用の初期化
	effects = new MyEffects();
	toast = new MyToast(U"初期メッセージですこれが表示されれば初期化されていない");

	//ガチャエフェクトの初期化
	gachaEffects = new MyEffects();
	gachaEffect = new MyImageEffect(U"resources/images/items/gacha/gachaeffect1.png", 10, 4, (const float)0.05);
	TextureAsset::Register(U"gachaeffectback2", U"resources/images/items/gacha/gacha.png");
	//変数の初期化
	button[(int)BUTTON::GACHA] = new MyImageButton(U"resources/images/items/gacha/gachabutton", U"", 30, 1700, 600);
	button[(int)BUTTON::EXIT] = new MyImageButton(U"resources/images/items/gacha/exitbutton", U"", 30, 300, 600);
	selectedButton = BUTTON::GACHA;		//初期のボタン選択状態をガチャに
	nowGachaState = GACHA_STATE::TITLE;	//ガチャの状態を何もない状態に
}

Gacha::~Gacha(void) {//終了処理
	FontAsset::Unregister(U"gachafont");
	TextureAsset::Unregister(U"gachaback");
	AudioAsset::Unregister(U"gachahandl");
	for (int i = 0; i < (int)BUTTON::SIZE; i++) {
		delete button[i];
	}
	delete backAudio;
}

bool Gacha::isReady(void) {//同期処理
	if (FontAsset::IsReady(U"gachafont") &&
		TextureAsset::IsReady(U"gachaback") &&
		AudioAsset::IsReady(U"gachahandl")) {
		for (int i = 0; i < (int)BUTTON::SIZE; i++) {
			if (!button[i]->isReady()) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void Gacha::start(void) {
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/gacha.wav");
	backAudio->setLoop(true);
	backAudio->play();
}


void Gacha::update(void) {

	simpleLoadEffect->update();
	if (simpleLoadEffect->isLoad()) {
		if (simpleLoadEffect->isDark()) {
			changeNextGachaState();//シーン移行
		}
		else if(simpleLoadEffect->isEnd()){
			//ロード明け
			loadEndFunc();
		}
		else {//暗転中
			return;
		}
	}
	//現在のガチャの状態に応じた計算処理
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE://ボタン選択画面
		updateTitle();
		break;
	case Gacha::GACHA_STATE::EFFECT://エフェクト
		if (gachaEffects->isEmpty()) {//一旦空になっているなら次のガチャエフェクトを実行する
			setNextGachaState(GACHA_STATE::RESULT);//ガチャ状態をエフェクト１へ
		}
		break;
	case Gacha::GACHA_STATE::RESULT://リザルト画面
		Print(U"リザルト画面です");
		if (MyKey::getDecisionKey()) {
			setNextGachaState(GACHA_STATE::TITLE);//ガチャ状態をエフェクト１へ
		}
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}

void Gacha::draw(void) {
	//背景の描画
	TextureAsset(U"gachaback").draw();

	//現在の状態に応じた画面描画
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE://タイトル画面
		drawButton();
		break;
	case Gacha::GACHA_STATE::EFFECT://ガチャガチャのエフェクト
		if (gachaEffects->isEmpty()) {//空ならシーン移行中なのでガチャの画像を描画
			TextureAsset(U"gachaeffectback2").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		else {//エフェクト中
			gachaEffects->draw();
		}
		break;
	case Gacha::GACHA_STATE::RESULT:
		resultDraw();
		FontAsset(U"gachafont")(U"～Press Enter～").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 150);
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
	//汎用エフェクト
	effects->draw();
	//ロードエフェクト
	simpleLoadEffect->draw();
	//デバッグ用
	Print(U"現在のポイント" + Format(User::getUserPoint()));
}

void Gacha::selectedMove() {//現在選択されているものの更新処理
	if (MyKey::getRightKeyDown()) {
		selectedButton = BUTTON::GACHA;
	}
	if (MyKey::getLeftKeyDown()) {
		selectedButton = BUTTON::EXIT;
	}
}

void Gacha::drawButton() {//ボタンの描画
	switch (selectedButton)
	{
	case Gacha::BUTTON::GACHA:
		button[(int)BUTTON::GACHA]->drawNotWord(true);
		button[(int)BUTTON::EXIT]->drawNotWord();
		break;
	case Gacha::BUTTON::EXIT:
		button[(int)BUTTON::GACHA]->drawNotWord();
		button[(int)BUTTON::EXIT]->drawNotWord(true);
		break;
	}
}

void Gacha::setNextGachaState(GACHA_STATE nextState) {//ガチャの状態を変更要求
	nextGachaState = nextState;
	simpleLoadEffect->start();//ロードの開始
}

void Gacha::changeNextGachaState() {//ガチャの状態を変更
	nowGachaState = nextGachaState;

	//明るくなり始める時に動作する
	loadBrightingFunc();
}


//明るくなり始める時に動作する
void Gacha::loadBrightingFunc() {
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE:
		break;
	case Gacha::GACHA_STATE::EFFECT:
		//エフェクトを追加する
		gachaEffects->add(gachaEffect, Vec2(Window::ClientWidth() / 2, Window::ClientHeight() / 2));
		//効果音再生
		AudioAsset(U"gachahandl").setVolume(0.1);
		AudioAsset(U"gachahandl").play();
		break;
	case Gacha::GACHA_STATE::RESULT:
		
		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}

//ロードが終わった時に実行する(完全に明るくなった時）
void Gacha::loadEndFunc() {
	switch (nowGachaState)
	{
	case Gacha::GACHA_STATE::TITLE:

		break;
	case Gacha::GACHA_STATE::EFFECT:

		break;
	case Gacha::GACHA_STATE::RESULT:

		break;
	case Gacha::GACHA_STATE::END:
		break;
	default:
		break;
	}
}


void Gacha::updateTitle() {
	if (MyKey::getDecisionKey()) {//決定キーが押された時
		switch (selectedButton)
		{
		case Gacha::BUTTON::GACHA:	//ガチャガチャをする
			if (isPlayGacha()) {//ガチャがプレイできる状態
				setNextGachaState(GACHA_STATE::EFFECT);	//ガチャ状態をエフェクト１へ
				User::subUserPoint(GACHA_PRICE);		//ポイントを減らす
				randomGacha();							//ガチャを行う
			}
			break;
		case Gacha::BUTTON::EXIT://モード選択へ戻る
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		}
	}
	selectedMove();//選択の移動処理,
}

bool Gacha::isPlayGacha() {
	if (User::hasAllItem()) {
		//全てのアイテムを取得済みなのでガチャが出来ない。
		toast->setMessage(U"取得できるアイテムはもうありません");
		effects->add(toast, Window::ClientCenter());
		return false;
	}
	else if (User::getUserPoint() < GACHA_PRICE) {
		//ポイントが足りていない
		toast->setMessage(U"ポイントが足りません");
		effects->add(toast, Window::ClientCenter());
		return false;
	}
	return true;
}

//ガチャを行う
void Gacha::randomGacha() {
	User::getRandomGacha(itemName);
	TextureAsset::Unregister(U"gachaitem");
	TextureAsset::Register(U"gachaitem", U"resources/images/gachaitems/"+ itemName + U".png");
}

//ガチャ結果の描画
void Gacha::resultDraw() {
	TextureAsset(U"gachaitem").drawAt(Window::ClientCenter());
}