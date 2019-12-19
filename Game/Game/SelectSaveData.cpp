#include "SelectSaveData.h"

#define FRAME_CENTER_X (Window::ClientWidth() / 2)		//真ん中のフレームの位置X
#define FRAME_CENTER_Y (Window::ClientHeight() / 2)		//真ん中のフレームの位置Y
#define FRAME_INTERVAL (Window::ClientHeight() * 0.2)	//フレームの間隔

#define SELECT_INTERVAL_COUNT (60 * 0.2)

SelectSaveData::SelectSaveData(void) {
	//アセットへロード
	FontAsset::Register(U"selectSDfont", 70);
	FontAsset::Preload(U"selectSDfont");
	FontAsset::Register(U"selectSDfontsmall", 40);
	FontAsset::Preload(U"selectSDfontsmall");
	TextureAsset::Register(U"selectSDback", U"resources/images/backs/selectsavedata.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectSDframe", U"resources/images/items/selectsavedata/frame.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"selectSDframeon", U"resources/images/items/selectsavedata/frameon.png", AssetParameter::LoadAsync());

	MySqlite3::getDB();//これを使用してSQL文を実行してデータの取得が必要になる。

	for (int i = 0; i < USER_SIZE; i++) {	//セーブデータフレームの初期化
		user_frame[i].id = i + 1;			//データベースのIDは１始まりなので１から指定
		//if文でもしユーザー名が空白ならNo Dataを格納する
		user_frame[i].user_name = U"No Data";		//名前の指定
		user_frame[i].total_play_time = U"";//プレイ時間の初期化
		user_frame[i].x = FRAME_CENTER_X;	//X座標を指定
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y座標を中心から上下になるように指定
	}

	//変数の初期化
	selectedUser = 0;//初期選択されているユーザーを一番上のものに
	selectCountPrev = 0;
	currentUserSize = User::getSaveDataSize();//現在のユーザー数を格納
	for (int i = 0; i < currentUserSize; i++) {//ユーザーが存在するものを更新する
		int64 totalplaytime = 0;
		User::simpleSaveDataAccess(i+1, user_frame[i].user_name, totalplaytime);
		if ((int)(totalplaytime / 3600) >= 0) {//プレイ時間が１時間を超えている場合
			user_frame[i].total_play_time = U"プレイ時間" + Format(totalplaytime / 3600) + U" 時間";
		}
		else {//１時間超えていないので分数
			user_frame[i].total_play_time = U"プレイ時間" + Format(totalplaytime / 60) + U" 分";
		}
	}
}
SelectSaveData::~SelectSaveData(void) {
	delete backAudio;
	FontAsset::Unregister(U"selectSDfont");
	FontAsset::Unregister(U"selectSDfontsmall");
	TextureAsset::Unregister(U"selectSDback");
	TextureAsset::Unregister(U"selectSDframe");
	TextureAsset::Unregister(U"selectSDframeon");
}
bool SelectSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"selectSDback")&&
		TextureAsset::IsReady(U"selectSDframe")&&
		TextureAsset::IsReady(U"selectSDframeon")) {
		return true;
	}
	return false;
}
void SelectSaveData::start(void) {
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void SelectSaveData::update(void) {
	if (MyKey::getDecisionKey()) {

		if (selectedUser < currentUserSize){//ユーザー数より小さい場所（既にユーザーが存在するところを選択している場合)
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			User::saveDataAccess(selectedUser + 1);
		}
		else {
			MySceneManager::setNextScene(SCENE::CREATE_SAVEDATA);
		}
	}
	updateFrameCount();
	if (!(MyKey::getUpKeyPressed() == true && MyKey::getDownKeyPressed() == true)) {
		if (MyKey::getUpKeyPressed()) {
			rotateSelectedUser(true);
		}
		if (MyKey::getDownKeyPressed()) {
			rotateSelectedUser(false);
		}
	}


}
void SelectSaveData::draw(void) {
	//背景描画
	TextureAsset(U"selectSDback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

	//セーブデータ選択
	FontAsset(U"selectSDfont")(U"～セーブデータの選択～").drawAt(Window::ClientWidth() / 2, user_frame[0].y - FRAME_INTERVAL, ColorF(0, 0, 0));

	//セーブデータのフレーム画像描画
	for (int i = 0; i < USER_SIZE; i++) {
		TextureAsset(U"selectSDframe").drawAt(user_frame[i].x, user_frame[i].y);
	}
	//選択されているものを強調して描画
	TextureAsset(U"selectSDframeon").drawAt(user_frame[selectedUser].x, user_frame[selectedUser].y);

	//セーブデータの情報を描画する
	for (int i = 0; i < USER_SIZE; i++) {
		FontAsset(U"selectSDfont")(user_frame[i].user_name).drawAt(user_frame[i].x, user_frame[i].y - 20 , (ColorF(0,0,0)));
		FontAsset(U"selectSDfontsmall")(user_frame[i].total_play_time).drawAt(user_frame[i].x, user_frame[i].y + 40, (ColorF(0, 0, 0)));
	}

	
}


void SelectSaveData::updateFrameCount() {
	frameCount++;
	if (frameCount > 60 * 3000) {//上限値チェック
		frameCount = 0;
	}
}

void SelectSaveData::rotateSelectedUser(bool isUp) {
	if (frameCount - selectCountPrev >= SELECT_INTERVAL_COUNT) {
		selectCountPrev = frameCount;
		if (isUp) {
			selectedUser--;
			if (selectedUser < 0) {
				selectedUser = USER_SIZE - 1;
			}
		}
		else {
			selectedUser++;
			if (selectedUser >= USER_SIZE) {
				selectedUser = 0;
			}
		}
	}
}