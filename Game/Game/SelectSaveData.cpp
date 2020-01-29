#include "SelectSaveData.h"

#define FRAME_CENTER_X (Scene::Width() / 2)		//真ん中のフレームの位置X
#define FRAME_CENTER_Y (Scene::Height() / 2 + 150)		//真ん中のフレームの位置Y
#define FRAME_INTERVAL (Scene::Height() * 0.23)	//フレームの間隔

//ポップアップのボタンの離れている間隔を定義
#define POPUP_INTERVAL (Scene::Width() * 0.07)

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

	TextureAsset::Register(U"selectSDdeleteon", U"resources/images/items/selectsavedata/delete/on.png");
	TextureAsset::Register(U"selectSDdeleteoff", U"resources/images/items/selectsavedata/delete/off.png");
	TextureAsset::Register(U"selectSDpopup", U"resources/images/items/selectsavedata/popup.png");
	//効果音ロード


	//セーブデータ取得等
	MySqlite3::getDB();//これを使用してSQL文を実行してデータの取得が必要になる。

	for (int i = 0; i < USER_SIZE; i++) {	//セーブデータフレームの初期化
		user_frame[i].id = i + 1;			//データベースのIDは１始まりなので１から指定
		if (User::isUser(i + 1)) {//ユーザーが存在するならユーザデータ格納
			int64 totalplaytime = 0;
			User::simpleSaveDataAccess(i + 1, user_frame[i].user_name, totalplaytime);
			if ((int)(totalplaytime / 3600) > 0) {//プレイ時間が１時間を超えている場合
				user_frame[i].total_play_time = U"プレイ時間" + Format(totalplaytime / 3600) + U" 時間";
			}
			else {//１時間超えていないので分数
				user_frame[i].total_play_time = U"プレイ時間" + Format(totalplaytime / 60) + U" 分";
			}
		}
		else {
			user_frame[i].user_name = U"No Data";		//名前の指定
			user_frame[i].total_play_time = U"";//プレイ時間の初期化
		}
		user_frame[i].x = FRAME_CENTER_X;	//X座標を指定
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y座標を中心から上下になるように指定
	}

	//ポップアップのボタン初期化
	popUpButton[(int)POPUP::DECISION] = new MyImageButton(U"resources/images/items/selectsavedata/popupdeci", U"", 0, (int)(Scene::Width() / 2) + (int)POPUP_INTERVAL, (int)Scene::Height() * 0.70, true);
	popUpButton[(int)POPUP::RETURN] = new MyImageButton(U"resources/images/items/selectsavedata/popupretu", U"", 0, (int)(Scene::Width() / 2) - (int)POPUP_INTERVAL, (int)Scene::Height() * 0.70, false);


	//変数の初期化
	selectedUser = 0;//初期選択されているユーザーを一番上のものに
	selectCountPrev = 0;
	selectDeleteButton = false;
	popUpState = POPUP::NONE;
	isPopUp = false;
}
SelectSaveData::~SelectSaveData(void) {
	delete backAudio;
	FontAsset::Unregister(U"selectSDfont");
	FontAsset::Unregister(U"selectSDfontsmall");
	TextureAsset::Unregister(U"selectSDback");
	TextureAsset::Unregister(U"selectSDframe");
	TextureAsset::Unregister(U"selectSDframeon");
	TextureAsset::Unregister(U"selectSDdeleteon");
	TextureAsset::Unregister(U"selectSDdeleteoff");
	TextureAsset::Unregister(U"selectSDpopup");
	AudioAsset::Unregister(U"selectSDdecision");
	AudioAsset::Unregister(U"selectSDcursor");

	delete popUpButton[(int)POPUP::DECISION];
	delete popUpButton[(int)POPUP::RETURN];
}
bool SelectSaveData::isReady(void) {
	if (TextureAsset::IsReady(U"selectSDback")&&
		TextureAsset::IsReady(U"selectSDframe")&&
		TextureAsset::IsReady(U"selectSDframeon")&&
		popUpButton[(int)POPUP::DECISION]->isReady() &&
		popUpButton[(int)POPUP::RETURN]->isReady()) {
		return true;
	}
	return false;
}
void SelectSaveData::start(void) {
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/selectSD.wav");
	backAudio->setLoop(true);
	backAudio->setVolume(0.1);
	backAudio->play();
}
void SelectSaveData::update(void) {

	if (isPopUp) {//ポップアップ選択状態の場合
		if (MyKey::getDecisionKey()) {
			if (popUpState == POPUP::DECISION) {
				deleteSaveData();
				GeneralSoundEffects::play(SE_NAME::DECISION);
			}
			else if (popUpState == POPUP::RETURN) {
				GeneralSoundEffects::play(SE_NAME::BACK);

			}
			isPopUp = false;
			selectDeleteButton = false;
			popUpState = POPUP::NONE;
		}
		else if (MyKey::getRightKeyDown()) {
			popUpState = POPUP::DECISION;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		else if (MyKey::getLeftKeyDown()) {
			popUpState = POPUP::RETURN;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		return;
	}

	//削除ボタン選択状態の場合
	if (selectDeleteButton && MyKey::getDecisionKey()) {
		isPopUp = true;
		popUpState = POPUP::DECISION;
		GeneralSoundEffects::play(SE_NAME::DECISION);
		return;
	}

	if (MyKey::getDecisionKey()) {//選択されているセーブデータにより分岐、シーン移行処理
		if (User::isUser(getSelectUser_Id())) {//ユーザーが存在している場合
			MySceneManager::setNextScene(SCENE::SELECT_MODE);	//モード選択へ移行
			User::saveDataAccess(getSelectUser_Id());				//セーブデータへアクセスしデータを保持
			TotalPlayTimeTimer::start();						//プレイ時間カウント開始
		}
		else {
			MySceneManager::setNextScene(SCENE::CREATE_SAVEDATA);
		}
		
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}else if (MyKey::getReturnKey()) {
		MySceneManager::setNextScene(SCENE::TITLE);
	}
	else if (MyKey::getRightKeyDown()) {//ユーザー存在するなら削除ボタンを選択させる
		if (!selectDeleteButton && User::isUser(getSelectUser_Id())) {
			selectDeleteButton = true;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
	}
	else if (MyKey::getLeftKeyDown() && selectDeleteButton) {
		selectDeleteButton = false;
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}




	updateFrameCount();//フレーム数をカウントアップする
	if (!(MyKey::getUpKeyPressed() == true && MyKey::getDownKeyPressed() == true)) {
		if (MyKey::getUpKeyPressed()) {//セーブデータ選択状態を上方向に回転
			rotateSelectedUser(true);
			if (!User::isUser(getSelectUser_Id())) {
				selectDeleteButton = false;
			}
		}
		if (MyKey::getDownKeyPressed()) {//セーブデータ選択状態を下方向に回転
			rotateSelectedUser(false);
			if (!User::isUser(getSelectUser_Id())) {
				selectDeleteButton = false;
			}
		}
	}


}
void SelectSaveData::draw(void) {
	//背景描画
	TextureAsset(U"selectSDback").drawAt(Scene::Width() / 2, Scene::Height() / 2);


	//セーブデータのフレーム画像描画
	for (int i = 0; i < USER_SIZE; i++) {
		TextureAsset(U"selectSDframe").drawAt(user_frame[i].x, user_frame[i].y);
		//削除ボタン描画
		if (User::isUser(i + 1)) {
			if (selectDeleteButton && i == selectedUser) {
				TextureAsset(U"selectSDdeleteon").drawAt(user_frame[i].x + 570, user_frame[i].y - 10);
			}
			else {
				TextureAsset(U"selectSDdeleteoff").drawAt(user_frame[i].x + 570, user_frame[i].y - 10);
			}
		}
	}
	//選択されているものを強調して描画
	TextureAsset(U"selectSDframeon").drawAt(user_frame[selectedUser].x, user_frame[selectedUser].y);

	//セーブデータの情報を描画する
	for (int i = 0; i < USER_SIZE; i++) {
		FontAsset(U"selectSDfont")(user_frame[i].user_name).drawAt(user_frame[i].x, user_frame[i].y - 20 , (ColorF(0,0,0)));
		FontAsset(U"selectSDfontsmall")(user_frame[i].total_play_time).drawAt(user_frame[i].x, user_frame[i].y + 40, (ColorF(0, 0, 0)));
	}

	if (isPopUp) {
		//ポップアップ背景を描画
		TextureAsset(U"selectSDpopup").drawAt(Scene::Width() * 0.5 - 35, Scene::Height() * 0.6);
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
}


//フレーム数をカウントアップする
void SelectSaveData::updateFrameCount() {
	frameCount++;
	if (frameCount > 60 * 3000) {//上限値チェック
		frameCount = 0;
	}
}

//ユーザーの選択状態を更新する(true = 上方向 false = 下方向)
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
		//効果音を鳴らす
		GeneralSoundEffects::play(SE_NAME::CURSOR);
	}
}

int SelectSaveData::getSelectUser_Id() {
	return selectedUser + 1;
}

void SelectSaveData::deleteSaveData() {
	User::deleteUserData(getSelectUser_Id());
	//データ格納し直し
	for (int i = 0; i < USER_SIZE; i++) {	//セーブデータフレームの初期化
		user_frame[i].id = i + 1;			//データベースのIDは１始まりなので１から指定
		if (User::isUser(i + 1)) {//ユーザーが存在するならユーザデータ格納
			int64 totalplaytime = 0;
			User::simpleSaveDataAccess(i + 1, user_frame[i].user_name, totalplaytime);
			if ((int)(totalplaytime / 3600) > 0) {//プレイ時間が１時間を超えている場合
				user_frame[i].total_play_time = U"プレイ時間" + Format(totalplaytime / 3600) + U" 時間";
			}
			else {//１時間超えていないので分数
				user_frame[i].total_play_time = U"プレイ時間" + Format(totalplaytime / 60) + U" 分";
			}
		}
		else {
			user_frame[i].user_name = U"No Data";		//名前の指定
			user_frame[i].total_play_time = U"";//プレイ時間の初期化
		}
		user_frame[i].x = FRAME_CENTER_X;	//X座標を指定
		user_frame[i].y = (int)(FRAME_CENTER_Y + (FRAME_INTERVAL * (i - (USER_SIZE / 2))));//Y座標を中心から上下になるように指定
	}
}