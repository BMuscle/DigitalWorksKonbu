#include "CreateSaveData.h"

//テキストボックスの座標 幅 定義
#define NAMEBOX_X (Scene::Width() * 0.5)
#define NAMEBOX_Y (Scene::Height() * 0.55)
#define NAMEBOX_W (Scene::Width() * 0.18)
//アイテムの位置の間隔を定義
#define ITEM_INTERVAL (Scene::Height() * 0.2)
//ポップアップのボタンの離れている間隔を定義
#define POPUP_INTERVAL (Scene::Width() * 0.07)

//ボタンの画面端から離れている距離
#define BUTTON_OFFSET_X (600)

#define BUTTON_RETURN_X (BUTTON_OFFSET_X)
#define BUTTON_DECISION_X (Scene::Width() - BUTTON_OFFSET_X)

#define BUTTON_Y NAMEBOX_Y

CreateSaveData::CreateSaveData(int user_id) {
	isStart = false;
	//アセットへロード
	FontAsset::Register(U"createSDfont", 40);
	FontAsset::Preload(U"createSDfont");
	TextureAsset::Register(U"createSDback", U"resources/images/backs/createsavedata.png", AssetParameter::LoadAsync());

	//ポップアップロード
	TextureAsset::Register(U"createSDpopup", U"resources/images/items/createsavedata/popup.png", AssetParameter::LoadAsync());	//決定、戻るボタンの初期化

	//戻るボタン決定ボタン初期化
	button[(int)BUTTON::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/return", U"", 0, BUTTON_RETURN_X, BUTTON_Y, false);
	button[(int)BUTTON::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/decision", U"", 0, BUTTON_DECISION_X, BUTTON_Y, false);
	
	//ポップアップのボタン初期化
	popUpButton[(int)POPUP::DECISION] = new MyImageButton(U"resources/images/items/createsavedata/popupdeci", U"", 0, (int)(Scene::Width() / 2) + (int)POPUP_INTERVAL, (int)Scene::Height() * 0.6, true);
	popUpButton[(int)POPUP::RETURN] = new MyImageButton(U"resources/images/items/createsavedata/popupretu", U"", 0, (int)(Scene::Width() / 2) - (int)POPUP_INTERVAL, (int)Scene::Height() * 0.6, false);

	//変数の初期化
	createUser_Id = user_id;//ユーザーID

	nameFont = Font(40);//テキストボックスのフォント
	namebox = TextBox(nameFont, Vec2(100, 100), NAMEBOX_W, 8, U"");
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

	delete popUpButton[(int)POPUP::DECISION];
	delete popUpButton[(int)POPUP::RETURN];

	delete backAudio;
}
bool CreateSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"createSDback")&&
		TextureAsset::IsReady(U"createSDpopup")&&
		popUpButton[(int)POPUP::DECISION]->isReady() &&
		popUpButton[(int)POPUP::RETURN]->isReady() &&
		button[(int)BUTTON::DECISION]->isReady()&&
		button[(int)BUTTON::RETURN]->isReady()) {
		return true;
	}
	return false;
}
void CreateSaveData::start(void) {
	isStart = true;
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/createSD.wav");
	backAudio->setLoop(true);
	backAudio->setVolume(0.1);
	backAudio->play();
	namebox.setActive(true);//ロード終了後でテキストボックスをアクティブに
}
void CreateSaveData::update(void) {//計算処理
	namebox.update();
	selectUpdate();//現在の選択状態に対応する計算処理
	selectMove();//移動処理

	//入力チェックを入れる(セレクトされているものが戻るボタンの場合例外）
	if (namebox.getText().isEmpty() &&
		selectState != SELECT_STATE::RETURN &&
		!namebox.isActive()) {//文字列が空なら終了する
		namebox.setActive(true);
		selectState = SELECT_STATE::TEXT;
	}
	if (selectState != SELECT_STATE::TEXT) {
		namebox.setActive(false);
	}
	
}


void CreateSaveData::draw(void) {//描画処理
	//背景描画
	TextureAsset(U"createSDback").drawAt(Scene::Width() / 2, Scene::Height() / 2);

	//ボタンの描画
	button[(int)BUTTON::DECISION]->drawNotWord(selectState == SELECT_STATE::DECISION);
	button[(int)BUTTON::RETURN]->drawNotWord(selectState == SELECT_STATE::RETURN);

	//テキストボックスの描画
	namebox.draw();
	namebox.drawOverlay();
	//FontAsset(U"createSDfont")(U"本人氏名").drawAt(NAMEBOX_X - FontAsset(U"createSDfont").fontSize() * 3 - NAMEBOX_W / 2, NAMEBOX_Y, ColorF(0, 0, 0));
	FontAsset(U"createSDfont")(U"本人氏名").drawAt(NAMEBOX_X, NAMEBOX_Y - 70, ColorF(0, 0, 0));

	//テキストボックスが非アクティブの時ポップアップを表示する
	if (selectState == SELECT_STATE::POPUP) {
		popUpDraw();
	}
}


void CreateSaveData::selectUpdate() {//現在の移動状態に対応する計算処理
	switch (selectState)//現在の選択状態
	{
	case CreateSaveData::SELECT_STATE::DECISION:
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			selectState = SELECT_STATE::POPUP;								//現在の選択状態をポップアップへ
			popUpState = POPUP::DECISION;										//ポップアップ表示
			GeneralSoundEffects::play(SE_NAME::DECISION);
		}
		return;
	case CreateSaveData::SELECT_STATE::TEXT:
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			selectState = SELECT_STATE::DECISION;								//テキストボックスでエンター押したときYESを選択させる
			namebox.setActive(false);
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		return;
	case CreateSaveData::SELECT_STATE::RETURN:
		if (MyKey::getDecisionKey()) {//決定キーが押された時
			MySceneManager::setNextScene(SCENE::SELECT_SAVEDATA);			//セーブデータ選択画面へ戻る
		}
		return;
	case CreateSaveData::SELECT_STATE::POPUP://現在ポップアップ表示中
		popUpUpdate();
		return;
	}
}
void CreateSaveData::selectMove() {//選択状態の遷移
	if (MyKey::getRightKeyDown()) {//右キー入力
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::TEXT://テキスト→決定ボタン
			namebox.setActive(false);
			selectState = SELECT_STATE::DECISION;
			break;
		case CreateSaveData::SELECT_STATE::RETURN://戻るボタン→テキスト
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			break;
		}
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	if (MyKey::getLeftKeyDown()) {//左キー入力
		switch (selectState)
		{
		case CreateSaveData::SELECT_STATE::DECISION://決定ボタン→テキスト
			namebox.setActive(true);
			selectState = SELECT_STATE::TEXT;
			break;
		case CreateSaveData::SELECT_STATE::TEXT://テキスト→戻るボタン
			namebox.setActive(false);
			selectState = SELECT_STATE::RETURN;
			break;
		}
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

void CreateSaveData::popUpUpdate() {//ポップアップの計算処理
	if (MyKey::getDecisionKey()) {//決定キーが押された時
		switch (popUpState)
		{
		case CreateSaveData::POPUP::DECISION://モード選択へ移動
			MySceneManager::setNextScene(SCENE::SELECT_MODE);			//モード選択へシーン移行要求
			createData();												//セーブデータ作成
			TotalPlayTimeTimer::start();								//プレイ時間計測開始
			GeneralSoundEffects::play(SE_NAME::DECISION);				//決定音
			break;
		case CreateSaveData::POPUP::RETURN://テキスト選択状態へ戻る
			selectState = SELECT_STATE::TEXT;							//現在の選択状態をテキストボックスへ
			namebox.setActive(true);
			GeneralSoundEffects::play(SE_NAME::BACK);//テキストボックスをアクティブに
			break;
		}
	}

	popUpMove();//ポップアップ移動処理
}

void CreateSaveData::popUpMove() {//ポップアップの移動チェック移動処理
	if (MyKey::getLeftKeyDown()) {
		popUpState = POPUP::RETURN;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
	if (MyKey::getRightKeyDown()) {
		popUpState = POPUP::DECISION;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

void CreateSaveData::popUpDraw() {//ポップアップの描画
	//ポップアップ背景を描画
	TextureAsset(U"createSDpopup").drawAt(Scene::Width() * 0.5, Scene::Height() * 0.45);
	switch (popUpState)
	{
	case POPUP::DECISION://YESが選択されているとき 選択状態を変更
		//描画処理
		popUpButton[(int)POPUP::DECISION]->drawNotWord(true);
		popUpButton[(int)POPUP::RETURN]->drawNotWord(false);
		break;
	case POPUP::RETURN://NOが選択されているとき 選択状態を変更
		//描画処理
		popUpButton[(int)POPUP::DECISION]->drawNotWord(false);
		popUpButton[(int)POPUP::RETURN]->drawNotWord(true);
		break;
	}
}

void CreateSaveData::createData() {//セーブデータを実際に作成
	User::createSaveData(createUser_Id, namebox.getText());//セーブデータ作成
	User::saveDataAccess(createUser_Id);
}
