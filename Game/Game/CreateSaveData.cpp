#include "CreateSaveData.h"

#define NAMEBOX_Y (Window::ClientHeight() * 0.3)
#define ITEM_INTERVAL (Window::ClientHeight() * 0.2)


CreateSaveData::CreateSaveData(void) {
	//アセットへロード
	FontAsset::Register(U"createSDfont", 70);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());

	//変数の初期化
	nameFont = Font(60);
	namebox = TextBox(nameFont, Vec2(100, 100), Window::ClientWidth() * 0.6, 15, U"名前を入力してください");
	namebox.setCenter(Vec2(Window::ClientWidth() / 2, NAMEBOX_Y));
	namebox.setActive(true);//初期状態でテキストボックスをアクティブに
}
CreateSaveData::~CreateSaveData(void) {
	FontAsset::Unregister(U"createSDfont");
	TextureAsset::Unregister(U"createSDback");
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void CreateSaveData::update(void) {//計算処理
	if (MyKey::getDecisionKey() &&  !namebox.isActive()) {//テキストボックスのエンターをはじく

		//入力チェックを入れる

		MySceneManager::setNextScene(SCENE::SELECT_MODE);
	}
	if (namebox.isActive()) {
		const auto result = namebox.update();
		if (result == TextBox::State::Enter || result == TextBox::State::Tab) {//TabかEnterが押されているなら次へ移動する
			//後で上下移動で初期アバター選択などをできるように？←あるならって感じ性別とか
			namebox.setActive(false);//非アクティブ化
		}

	}
}
void CreateSaveData::draw(void) {//描画処理
	//背景描画
	TextureAsset(U"createSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	FontAsset(U"createSDfont")(U"名前").drawAt((Window::ClientWidth() / 2) - (namebox.getRect().w / 2) + FontAsset(U"createSDfont").fontSize(), NAMEBOX_Y - namebox.getRect().h);
	namebox.draw();
	namebox.drawOverlay();
}