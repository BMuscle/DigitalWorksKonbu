#include "CreateSaveData.h"

#define NAMEBOX_X (Window::ClientWidth() * 0.6)
#define NAMEBOX_Y (Window::ClientHeight() * 0.8)
#define NAMEBOX_W (Window::ClientWidth() * 0.3)
#define ITEM_INTERVAL (Window::ClientHeight() * 0.2)

#define POPUP_INTERVAL (Window::ClientWidth() * 0.07)

CreateSaveData::CreateSaveData(void) {
	isStart = false;
	//アセットへロード
	FontAsset::Register(U"createSDfont", 70);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());
	//ポップアップロード
	TextureAsset::Register(U"createSDpopup", U"resources/images/items/createsavedata/popup.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDyes", U"resources/images/items/createsavedata/yes.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDyeson", U"resources/images/items/createsavedata/yeson.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDno", U"resources/images/items/createsavedata/no.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"createSDnoon", U"resources/images/items/createsavedata/noon.png", AssetParameter::LoadAsync());

	//変数の初期化
	nameFont = Font(50);//テキストボックスのフォント
	namebox = TextBox(nameFont, Vec2(100, 100), NAMEBOX_W, 15, U"");
	namebox.setCenter(Vec2(NAMEBOX_X, NAMEBOX_Y));
	namebox.setActive(false);//初期状態でテキストボックスを非アクティブに
	popUpState = POPUP_STATE::YES;//ポップアップ選択の初期状態はYESに
}
CreateSaveData::~CreateSaveData(void) {
	FontAsset::Unregister(U"createSDfont");
	TextureAsset::Unregister(U"createSDback");
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")&&
		TextureAsset::IsReady(U"createSDpopup")&&
		TextureAsset::IsReady(U"createSDyes")&&
		TextureAsset::IsReady(U"createSDyeson")&&
		TextureAsset::IsReady(U"createSDno")&&
		TextureAsset::IsReady(U"createSDnoon")) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	isStart = true;
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
	namebox.setActive(true);//ロード終了後でテキストボックスをアクティブに
}
void CreateSaveData::update(void) {//計算処理

	if (namebox.isActive()) {//テキストボックスがアクティブの時
		namebox.update();
		//入力チェックを入れる
		if (namebox.getText().isEmpty()) {//文字列が空なら終了する
			namebox.setActive(true);
			return;
		}
	}
	else if (MyKey::getDecisionKey()) {//テキストボックスが非アクティブで決定キーが押された時
		switch (popUpState)
		{
		case CreateSaveData::POPUP_STATE::YES://モード選択へ移動
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		case CreateSaveData::POPUP_STATE::NO://セーブデータ選択へ戻る
			MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);
			break;
		}
	}
	else {//テキストボックスが非アクティブの時選択の横移動
		if (MyKey::getLeftKeyDown()) {
			popUpState = POPUP_STATE::YES;
		}
		if (MyKey::getRightKeyDown()) {
			popUpState = POPUP_STATE::NO;
		}
	}
}
void CreateSaveData::draw(void) {//描画処理
	//背景描画
	TextureAsset(U"createSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	namebox.draw();
	namebox.drawOverlay();
	FontAsset(U"createSDfont")(U"本人氏名").drawAt(NAMEBOX_X - FontAsset(U"createSDfont").fontSize() * 3 - NAMEBOX_W / 2, NAMEBOX_Y, ColorF(0, 0, 0));
	if (!namebox.isActive() && isStart) {//テキストボックスが非アクティブの時ポップアップを表示する
		popUpDraw();
	}
}

void CreateSaveData::popUpDraw() {//ポップアップの描画
	TextureAsset(U"createSDpopup").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	switch (popUpState)
	{
	case CreateSaveData::POPUP_STATE::YES://YESが選択されているとき
		TextureAsset(U"createSDno").drawAt(Window::ClientWidth() / 2 + POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		TextureAsset(U"createSDyeson").drawAt(Window::ClientWidth() / 2 - POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		break;
	case CreateSaveData::POPUP_STATE::NO://NOが選択されているとき
		TextureAsset(U"createSDnoon").drawAt(Window::ClientWidth() / 2 + POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		TextureAsset(U"createSDyes").drawAt(Window::ClientWidth() / 2 - POPUP_INTERVAL, Window::ClientHeight() * 0.6);
		break;
	}
}