#include "MyRoomCollection.h"

MyRoomCollection::MyRoomCollection(MYROOM_SCENE* scenep) :MyRoomSceneBase(scenep) {
	TextureAsset::Register(U"myroomback", U"resources/images/backs/myroom/collection.png", AssetParameter::LoadAsync());

	button = new MyImageButton(U"resources/images/items/myroom/collection/return", U"", 0, Window::ClientWidth() - 120, Window::ClientHeight() / 2);

	FontAsset::Register(U"myroomsmallfont", 50, AssetParameter::LoadAsync());
	FontAsset::Preload(U"myroomsmallfont");

	AudioAsset::Register(U"deci2", U"resources/musics/items/myroom/deci2.wav");

	csvItem[(int)GAME_TYPE::DODGE].load(U"resources/gamedata/dodge.csv");
	csvItem[(int)GAME_TYPE::SHOEKICK].load(U"resources/gamedata/shoekick.csv");
	csvItem[(int)GAME_TYPE::SOCCER].load(U"resources/gamedata/soccer.csv");

	//ドッジボールのガチャアイテム読み込み
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		TextureAsset::Register(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1), U"resources/images/gachaitems/"+csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1) + U".png", AssetParameter::LoadAsync());
	}
	//靴飛ばしのガチャアイテム読み込み
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		TextureAsset::Register(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1), U"resources/images/gachaitems/" + csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1) + U".png", AssetParameter::LoadAsync());
	}
	//サッカーのガチャアイテム読み込み
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		TextureAsset::Register(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1), U"resources/images/gachaitems/" + csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1) + U".png", AssetParameter::LoadAsync());
	}
	//変数の初期化
	isButtonSelect = false;
	isCollectionSelected = false;
	//テーブルの初期化
	initializeCollectionTable();

	alpha = 0;
}
MyRoomCollection::~MyRoomCollection() {
	TextureAsset::Unregister(U"myroomback");
	FontAsset::Unregister(U"myroomsmallfont");
	AudioAsset::Unregister(U"deci2");

	delete backAudio;

	//ドッジボールのガチャアイテムアンロード
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		TextureAsset::Unregister(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1));
	}
	//靴飛ばしのガチャアイテムアンロード
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		TextureAsset::Unregister(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1));
	}
	//サッカーのガチャアイテムアンロード
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		TextureAsset::Unregister(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1));
	}
}
bool MyRoomCollection::isReady() {
	if (TextureAsset::IsReady(U"myroomback") &&
		FontAsset::IsReady(U"myroomsmallfont")) {

		//ドッジボールのガチャアイテムチェック
		for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
			if (!TextureAsset::IsReady(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1))) {
				return false;
			}
		}
		//靴飛ばしのガチャアイテムチェック
		for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
			if (!TextureAsset::IsReady(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1))) {
				return false;
			}
		}
		//サッカーのガチャアイテムチェック
		for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
			if (!TextureAsset::IsReady(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1))) {
				return false;
			}
		}

		return true;
	}
	return false;
}
void MyRoomCollection::start() {
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/myroomcollection.wav");
	backAudio->setVolume(0.1);
	backAudio->setLoop(true);
	backAudio->play();
}
void MyRoomCollection::update() {
	changeAlpha();

	//コレクション説明表示状態
	if (isCollectionSelected) {
		if (MyKey::getDecisionKey()) {
			isCollectionSelected = false;
			deci2Play();
		}
		return;		
	}
	//ボタンを選択状態
	if (isButtonSelect) {
		if(MyKey::getLeftKeyDown()){
			if (hasItem) {//アイテムが存在している
				isButtonSelect = false;
				selectedItem.column = *itemVec[selectedItem.row].rbegin();//一番右側のアイテムを選択
			}
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
	}
	else {
		if (MyKey::getUpKeyDown()) {
			int tmp = selectedMoveRow(selectedItem.row - 1);
			if (tmp != -1) {
				selectedItem.row--;
				selectedItem.column = tmp;
			}
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		if (MyKey::getDownKeyDown()) {
			int tmp = selectedMoveRow(selectedItem.row + 1);
			if (tmp != -1) {
				selectedItem.row++;
				selectedItem.column = tmp;
			}
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		if (MyKey::getRightKeyDown()) {
			//右端上限 
			if (selectedItem.column >= *(itemVec[selectedItem.row].rbegin())) {
				isButtonSelect = true;
				isCollectionSelected = false;	//説明の表示状態をオフに
			}
			else {
				//ひとつ右に移動する
				for (const auto& itemColumn : itemVec[selectedItem.row]) {
					if (selectedItem.column < itemColumn) {
						selectedItem.column = itemColumn;
						break;
					}
				}
			}
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		if (MyKey::getLeftKeyDown()) {
			//逆順でひとつ←のアイテムを選択させる
			for (auto itemColumn = itemVec[selectedItem.row].rbegin(), e = itemVec[selectedItem.row].rend(); itemColumn != e; ++itemColumn) {
				if (selectedItem.column > * itemColumn) {
					selectedItem.column = *itemColumn;
					break;
				}
			}
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
	}
	
	Print(U"テスト用　選択中列＝" + Format(selectedItem.column));
	Print(U"テスト用　選択中行＝" + Format(selectedItem.row));

	if (MyKey::getDecisionKey()) {
		if (isButtonSelect) {
			setNextScene(MYROOM_SCENE::TITLE);
			GeneralSoundEffects::play(SE_NAME::DECISION);
		}
		else if(!isCollectionSelected){
			selectedItemTextLoad();
			isCollectionSelected = true;
			deci2Play();
		}
	}
}
void MyRoomCollection::draw() {
	//背景の描画
	TextureAsset(U"myroomback").draw();

	button->drawNotWord(isButtonSelect);

	constexpr int ITEM_INTERVAL = 230;//アイテム同士の間隔
	constexpr float ITEM_SCALED = 0.4;//アイテムの大きさ
	constexpr int ITEM_OFFSET_X = 100;//左側が大きいのでオフセットで足す
	constexpr int ITEM_Y[(int)GAME_TYPE::SIZE] = {
		200,
		545,
		890
	};
	constexpr float ITEM_ALPHA = 0.6;

	//サッカーのガチャアイテム描画
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SOCCER, csvItem[(int)GAME_TYPE::SOCCER].get<int>(row, 0))){
			int median = csvItem[(int)GAME_TYPE::DODGE].rows() / 2;
			int x = (Window::ClientWidth() / 2) + ((row - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//画面中央にセンタリングされるよう描画
			TextureAsset(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[(int)GAME_TYPE::SOCCER], AlphaF(ITEM_ALPHA));
		}
	}

	//靴飛ばしのガチャアイテム描画
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SHOEKICK, csvItem[(int)GAME_TYPE::SHOEKICK].get<int>(row, 0))) {
			int median = csvItem[(int)GAME_TYPE::DODGE].rows() / 2;
			int x = (Window::ClientWidth() / 2) + ((row - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//画面中央にセンタリングされるよう描画
			TextureAsset(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[(int)GAME_TYPE::SHOEKICK], AlphaF(ITEM_ALPHA));
		}
	}

	//ドッジボールのガチャアイテム描画
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::DODGE, csvItem[(int)GAME_TYPE::DODGE].get<int>(row, 0))) {
			int median = csvItem[(int)GAME_TYPE::DODGE].rows() / 2;
			int x = (Window::ClientWidth() / 2) + ((row - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//画面中央にセンタリングされるよう描画
			TextureAsset(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[(int)GAME_TYPE::DODGE], AlphaF(ITEM_ALPHA));
		}
	}
	if (!isButtonSelect && hasItem) {
		int median = csvItem[selectedItem.row].rows() / 2;
		int x = (Window::ClientWidth() / 2) + ((selectedItem.column - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//画面中央にセンタリングされるよう描画
		TextureAsset(csvItem[selectedItem.row].get<String>(selectedItem.column, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[selectedItem.row]);
	}



	//詳細説明表示
	if (isCollectionSelected) {
		Rect(0, 0, Window::ClientWidth(), Window::ClientHeight()).draw(ColorF(1, 1, 1, 0.5));
		TextureAsset(csvItem[selectedItem.row].get<String>(selectedItem.column, 1)).scaled(0.8).drawAt(Window::ClientWidth() * 0.25, Window::ClientHeight() / 2);
		TextureAsset(U"gachatext").drawAt(Window::ClientWidth() * 0.65, Window::ClientHeight() / 2);
		FontAsset(U"myroomsmallfont")(U"～Press to Enter～").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 100, ColorF(0, 0, 0, alpha));
	}
}


void MyRoomCollection::initializeCollectionTable() {
	hasItem = false;//アイテムがゼロかどうかのフラグ

	//サッカーのガチャアイテム取得
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SOCCER, csvItem[(int)GAME_TYPE::SOCCER].get<int>(row, 0))) {
			itemVec[(int)GAME_TYPE::SOCCER].push_back(row);
			hasItem = true;
		}
	}

	//靴飛ばしのガチャアイテム取得
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SHOEKICK, csvItem[(int)GAME_TYPE::SHOEKICK].get<int>(row, 0))) {
			itemVec[(int)GAME_TYPE::SHOEKICK].push_back(row);
			hasItem = true;
		}
	}

	//ドッジボールのガチャアイテム取得
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::DODGE, csvItem[(int)GAME_TYPE::DODGE].get<int>(row, 0))) {
			itemVec[(int)GAME_TYPE::DODGE].push_back(row);
			hasItem = true;
		}
	}

	if (hasItem) {//アイテムを１つでも持っているならアイテムを選択状態にする
		isButtonSelect = false;

		for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
			if (itemVec[i].size() > 0) {
				selectedItem.row = i;//初期行の確定
				for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
					if (User::getHasItems((GAME_TYPE)i, csvItem[i].get<int>(row, 0))) {
						selectedItem.column = row;//初期列の確定
						break;
					}
				}
				break;
			}
		}
	}
	else {//アイテムを持っていないなら戻るボタンを初期選択状態にする
		isButtonSelect = true;
		//持っていないのでアイテム所持状態を-1に
		selectedItem.row = -1;
		selectedItem.column = -1;
	}
}

void MyRoomCollection::selectedItemTextLoad() {
	TextureAsset::Unregister(U"gachatext");
	TextureAsset::Register(U"gachatext", U"resources/images/gachaitems/description/" + csvItem[selectedItem.row].get<String>(selectedItem.column, 1) + U".png");
}

int MyRoomCollection::selectedMoveRow(int row) {
	if (row < 0 ||
		row >= (int)GAME_TYPE::SIZE ||
		itemVec[row].empty()) {
		return -1;
	}
	int column;//戻り値
	int minColumn = 999999;//差が最小値
	for (auto vec : itemVec[row]) {
		if (std::abs(selectedItem.column - vec) < minColumn) {
			minColumn = std::abs(selectedItem.column - vec);
			column = vec;
		}
	}
	return column;
}

void MyRoomCollection::changeAlpha(void) {
	constexpr int CYCLE = 3000;//透過が変わる周期
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}

void MyRoomCollection::deci2Play() {
	AudioAsset(U"deci2").setPosSec(0);
	AudioAsset(U"deci2").setVolume(0.2);
	AudioAsset(U"deci2").play();

}