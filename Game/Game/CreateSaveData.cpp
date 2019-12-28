#include "CreateSaveData.h"

//テキストボックスの座標 幅 定義
#define NAMEBOX_X (Window::ClientWidth() * 0.6)
#define NAMEBOX_Y (Window::ClientHeight() * 0.8)
#define NAMEBOX_W (Window::ClientWidth() * 0.3)
//アイテムの位置の間隔を定義
#define ITEM_INTERVAL (Window::ClientHeight() * 0.2)
//ポップアップのボタンの離れている間隔を定義
#define POPUP_INTERVAL (Window::ClientWidth() * 0.07)

CreateSaveData::CreateSaveData(void) {
	isStart = false;
	//アセットへロード
	FontAsset::Register(U"createSDfont", 70);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());

	//ポップアップロード
	TextureAsset::Register(U"createSDpopup", U"resources/images/items/createsavedata/popup.png", AssetParameter::LoadAsync());	//決定、戻るボタンの初期化

	//戻るボタン決定ボタン初期化
	button[(int)BUTTON::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/button", U"戻る", 50, 100, 800, false);
	button[(int)BUTTON::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/button", U"決定", 50, 1800, 800, false);
	
	//ポップアップのボタン初期化
	popUpButton[(int)POPUP::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/popup", U"本当に良い？", 50, (int)(Window::ClientWidth() / 2) + (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, true);
	popUpButton[(int)POPUP::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/popup", U"やっぱやめる", 40, (int)(Window::ClientWidth() / 2) - (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, false);

	//変数の初期化
	nameFont = Font(50);//テキストボックスのフォント
	namebox = TextBox(nameFont, Vec2(100, 100), NAMEBOX_W, 15, U"");
	namebox.setCenter(Vec2(NAMEBOX_X, NAMEBOX_Y));
	namebox.setActive(false);//初期状態でテキストボックスを非アクティブに
	selectState = SELECT_STATE::TEXT;//初期状態の選択状態はテキストボックスに
	popUpState = POPUP::NONE;//ポップアップ選択の初期状態はYESに
}
CreateSaveData::~CreateSaveData(void) {
	FontAsset::Unregister(U"createSDfont");
	TextureAsset::Unregister(U"createSDback");
	delete button[(int)BUTTON::DECISION];
	delete button[(int)BUTTON::RETURN];


	int id = User::getSaveDataSize() + 1;//現在のセーブデータ数の１つ上に新規セーブデータを作成する
	if (id > 0) {
		User::createSaveData(id, namebox.getText());//セーブデータ作成
		User::saveDataAccess(id);
	}
	else {
		//エラー
	}
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")&&
		TextureAsset::IsReady(U"createSDpopup")&&
		popUpButton[(int)BUTTON::DECISION]->isReady()&&
		popUpButton[(int)BUTTON::RETURN]->isReady() &&
		button[(int)BUTTON::DECISION]->isReady()&&
		button[(int)BUTTON::RETURN]->isReady()) {
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
	}
	
	selectUpdate();//現在の選択状態に対応する計算処理
	selectMove();//移動処理

	//入力チェックを入れる(セレクトされているものが戻るボタンの場合例外）
	if (namebox.getText().isEmpty() && selectState != SELECT_STATE::DECISION) {//文字列が空なら終了する
		namebox.setActive(true);
		selectState = SELECT_STATE::TEXT;
		button[(int)BUTTON::DECISION]->setSelect(false);
		button[(int)BUTTON::RETURN]->setSelect(false);
	}
}


void CreateSaveData::draw(void) {//描画処理
	//背景描画
	TextureAsset(U"createSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

	//ボタンの描画
	button[(int)BUTTON::DECISION]->draw();
	button[(int)BUTTON::RETURN]->draw();
	//テキストボックスの描画
	namebox.draw();
	namebox.drawOverlay();
	FontAsset(U"createSDfont")(U"本人氏名").drawAt(NAMEBOX_X - FontAsset(U"createSDfont").fontSize() * 3 - NAMEBOX_W / 2, NAMEBOX_Y, ColorF(0, 0, 0));
	if (selectState == SELECT_STATE::POPUP) {//テキストボックスが非アクティブの時ポップアップを表示する
		popUpDraw();
	}
}


void CreateSaveData::selectUpdate() {//現在の移動状態に対応する計算処理
	switch (selectState)//現在の選択状態
	{
	case CreateSaveData::SELECT_STATE::RETURN:
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			selectState = SELECT_STATE::POPUP;								//現在の選択状態をポップアップへ
			popUpState = POPUP::RETURN;										//ポップアップ表示
		}
		return;
	case CreateSaveData::SELECT_STATE::TEXT:
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			selectState = SELECT_STATE::RETURN;								//テキストボックスでエンター押したときYESを選択させる
			button[(int)BUTTON::DECISION]->setSelect(true);
			namebox.setActive(false);
		}
		return;
	case CreateSaveData::SELECT_STATE::DECISION:
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);			//セーブデータ選択画面へ戻る
		}
		return;
	case CreateSaveData::SELECT_STATE::POPUP://現在ポップアップ表示中
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			switch (popUpState)
			{
			case CreateSaveData::POPUP::RETURN://モード選択へ移動
				MySceneManager::setNextScene(SCENE::SELECT_MODE);			//モード選択へシーン移行要求
				TotalPlayTimeTimer::start();								//プレイ時間計測開始
				break;
			case CreateSaveData::POPUP::DECISION://テキスト選択状態へ戻る
				selectState = SELECT_STATE::TEXT;							//現在の選択状態をテキストボックスへ
				namebox.setActive(true);									//テキストボックスをアクティブに
				button[(int)BUTTON::DECISION]->setSelect(false);			//ボタンを両方とも非アクティブ化
				button[(int)BUTTON::RETURN]->setSelect(false);
				break;
			}
		}
		else {//左右移動
			if (MyKey::getLeftKeyDown()) {
				popUpState = POPUP::DECISION;
			}
			if (MyKey::getRightKeyDown()) {
				popUpState = POPUP::RETURN;
			}
		}
		return;
	}
}
void CreateSaveData::selectMove() {//選択状態の遷移
	if (MyKey::getRightKeyDown()) {//右キー入力
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::TEXT://テキスト→決定ボタン
			namebox.setActive(false);
			selectState = SELECT_STATE::RETURN;
			button[(int)BUTTON::DECISION]->setSelect(true);
			break;
		case CreateSaveData::SELECT_STATE::DECISION://戻るボタン→テキスト
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			button[(int)BUTTON::RETURN]->setSelect(false);
			break;
		}
	}
	if (MyKey::getLeftKeyDown()) {//左キー入力
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::RETURN://決定ボタン→テキスト
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			button[(int)BUTTON::DECISION]->setSelect(false);
			break;
		case CreateSaveData::SELECT_STATE::TEXT://テキスト→戻るボタン
			namebox.setActive(false);
			selectState = SELECT_STATE::DECISION;
			button[(int)BUTTON::RETURN]->setSelect(true);
			break;
		}
	}
}

void CreateSaveData::popUpDraw() {//ポップアップの描画
	//ポップアップ背景を描画
	TextureAsset(U"createSDpopup").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	switch (popUpState)
	{
	case CreateSaveData::POPUP::RETURN://YESが選択されているとき 選択状態を変更
		popUpButton[(int)POPUP::RETURN]->setSelect(true);
		popUpButton[(int)POPUP::DECISION]->setSelect(false);
		break;
	case CreateSaveData::POPUP::DECISION://NOが選択されているとき 選択状態を変更
		popUpButton[(int)POPUP::RETURN]->setSelect(false);
		popUpButton[(int)POPUP::DECISION]->setSelect(true);
		break;
	}
	//描画処理
	popUpButton[(int)POPUP::RETURN]->draw();
	popUpButton[(int)POPUP::DECISION]->draw();
}