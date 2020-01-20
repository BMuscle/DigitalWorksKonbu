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

	//�h�b�W�{�[���̃K�`���A�C�e���ǂݍ���
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		TextureAsset::Register(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1), U"resources/images/gachaitems/"+csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1) + U".png", AssetParameter::LoadAsync());
	}
	//�C��΂��̃K�`���A�C�e���ǂݍ���
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		TextureAsset::Register(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1), U"resources/images/gachaitems/" + csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1) + U".png", AssetParameter::LoadAsync());
	}
	//�T�b�J�[�̃K�`���A�C�e���ǂݍ���
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		TextureAsset::Register(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1), U"resources/images/gachaitems/" + csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1) + U".png", AssetParameter::LoadAsync());
	}
	//�ϐ��̏�����
	isButtonSelect = false;
	isCollectionSelected = false;
	//�e�[�u���̏�����
	initializeCollectionTable();

	alpha = 0;
}
MyRoomCollection::~MyRoomCollection() {
	TextureAsset::Unregister(U"myroomback");
	FontAsset::Unregister(U"myroomsmallfont");
	AudioAsset::Unregister(U"deci2");

	delete backAudio;

	//�h�b�W�{�[���̃K�`���A�C�e���A�����[�h
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		TextureAsset::Unregister(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1));
	}
	//�C��΂��̃K�`���A�C�e���A�����[�h
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		TextureAsset::Unregister(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1));
	}
	//�T�b�J�[�̃K�`���A�C�e���A�����[�h
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		TextureAsset::Unregister(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1));
	}
}
bool MyRoomCollection::isReady() {
	if (TextureAsset::IsReady(U"myroomback") &&
		FontAsset::IsReady(U"myroomsmallfont")) {

		//�h�b�W�{�[���̃K�`���A�C�e���`�F�b�N
		for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
			if (!TextureAsset::IsReady(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1))) {
				return false;
			}
		}
		//�C��΂��̃K�`���A�C�e���`�F�b�N
		for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
			if (!TextureAsset::IsReady(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1))) {
				return false;
			}
		}
		//�T�b�J�[�̃K�`���A�C�e���`�F�b�N
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

	//�R���N�V���������\�����
	if (isCollectionSelected) {
		if (MyKey::getDecisionKey()) {
			isCollectionSelected = false;
			deci2Play();
		}
		return;		
	}
	//�{�^����I�����
	if (isButtonSelect) {
		if(MyKey::getLeftKeyDown()){
			if (hasItem) {//�A�C�e�������݂��Ă���
				isButtonSelect = false;
				selectedItem.column = *itemVec[selectedItem.row].rbegin();//��ԉE���̃A�C�e����I��
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
			//�E�[��� 
			if (selectedItem.column >= *(itemVec[selectedItem.row].rbegin())) {
				isButtonSelect = true;
				isCollectionSelected = false;	//�����̕\����Ԃ��I�t��
			}
			else {
				//�ЂƂE�Ɉړ�����
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
			//�t���łЂƂ��̃A�C�e����I��������
			for (auto itemColumn = itemVec[selectedItem.row].rbegin(), e = itemVec[selectedItem.row].rend(); itemColumn != e; ++itemColumn) {
				if (selectedItem.column > * itemColumn) {
					selectedItem.column = *itemColumn;
					break;
				}
			}
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
	}
	
	Print(U"�e�X�g�p�@�I�𒆗�" + Format(selectedItem.column));
	Print(U"�e�X�g�p�@�I�𒆍s��" + Format(selectedItem.row));

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
	//�w�i�̕`��
	TextureAsset(U"myroomback").draw();

	button->drawNotWord(isButtonSelect);

	constexpr int ITEM_INTERVAL = 230;//�A�C�e�����m�̊Ԋu
	constexpr float ITEM_SCALED = 0.4;//�A�C�e���̑傫��
	constexpr int ITEM_OFFSET_X = 100;//�������傫���̂ŃI�t�Z�b�g�ő���
	constexpr int ITEM_Y[(int)GAME_TYPE::SIZE] = {
		200,
		545,
		890
	};
	constexpr float ITEM_ALPHA = 0.6;

	//�T�b�J�[�̃K�`���A�C�e���`��
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SOCCER, csvItem[(int)GAME_TYPE::SOCCER].get<int>(row, 0))){
			int median = csvItem[(int)GAME_TYPE::DODGE].rows() / 2;
			int x = (Window::ClientWidth() / 2) + ((row - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//��ʒ����ɃZ���^�����O�����悤�`��
			TextureAsset(csvItem[(int)GAME_TYPE::SOCCER].get<String>(row, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[(int)GAME_TYPE::SOCCER], AlphaF(ITEM_ALPHA));
		}
	}

	//�C��΂��̃K�`���A�C�e���`��
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SHOEKICK, csvItem[(int)GAME_TYPE::SHOEKICK].get<int>(row, 0))) {
			int median = csvItem[(int)GAME_TYPE::DODGE].rows() / 2;
			int x = (Window::ClientWidth() / 2) + ((row - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//��ʒ����ɃZ���^�����O�����悤�`��
			TextureAsset(csvItem[(int)GAME_TYPE::SHOEKICK].get<String>(row, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[(int)GAME_TYPE::SHOEKICK], AlphaF(ITEM_ALPHA));
		}
	}

	//�h�b�W�{�[���̃K�`���A�C�e���`��
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::DODGE, csvItem[(int)GAME_TYPE::DODGE].get<int>(row, 0))) {
			int median = csvItem[(int)GAME_TYPE::DODGE].rows() / 2;
			int x = (Window::ClientWidth() / 2) + ((row - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//��ʒ����ɃZ���^�����O�����悤�`��
			TextureAsset(csvItem[(int)GAME_TYPE::DODGE].get<String>(row, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[(int)GAME_TYPE::DODGE], AlphaF(ITEM_ALPHA));
		}
	}
	if (!isButtonSelect && hasItem) {
		int median = csvItem[selectedItem.row].rows() / 2;
		int x = (Window::ClientWidth() / 2) + ((selectedItem.column - median) * ITEM_INTERVAL) + ITEM_OFFSET_X;//��ʒ����ɃZ���^�����O�����悤�`��
		TextureAsset(csvItem[selectedItem.row].get<String>(selectedItem.column, 1)).scaled(ITEM_SCALED).drawAt(x, ITEM_Y[selectedItem.row]);
	}



	//�ڍא����\��
	if (isCollectionSelected) {
		Rect(0, 0, Window::ClientWidth(), Window::ClientHeight()).draw(ColorF(1, 1, 1, 0.5));
		TextureAsset(csvItem[selectedItem.row].get<String>(selectedItem.column, 1)).scaled(0.8).drawAt(Window::ClientWidth() * 0.25, Window::ClientHeight() / 2);
		TextureAsset(U"gachatext").drawAt(Window::ClientWidth() * 0.65, Window::ClientHeight() / 2);
		FontAsset(U"myroomsmallfont")(U"�`Press to Enter�`").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 100, ColorF(0, 0, 0, alpha));
	}
}


void MyRoomCollection::initializeCollectionTable() {
	hasItem = false;//�A�C�e�����[�����ǂ����̃t���O

	//�T�b�J�[�̃K�`���A�C�e���擾
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SOCCER].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SOCCER, csvItem[(int)GAME_TYPE::SOCCER].get<int>(row, 0))) {
			itemVec[(int)GAME_TYPE::SOCCER].push_back(row);
			hasItem = true;
		}
	}

	//�C��΂��̃K�`���A�C�e���擾
	for (int row = 0; row < csvItem[(int)GAME_TYPE::SHOEKICK].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::SHOEKICK, csvItem[(int)GAME_TYPE::SHOEKICK].get<int>(row, 0))) {
			itemVec[(int)GAME_TYPE::SHOEKICK].push_back(row);
			hasItem = true;
		}
	}

	//�h�b�W�{�[���̃K�`���A�C�e���擾
	for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
		if (User::getHasItems(GAME_TYPE::DODGE, csvItem[(int)GAME_TYPE::DODGE].get<int>(row, 0))) {
			itemVec[(int)GAME_TYPE::DODGE].push_back(row);
			hasItem = true;
		}
	}

	if (hasItem) {//�A�C�e�����P�ł������Ă���Ȃ�A�C�e����I����Ԃɂ���
		isButtonSelect = false;

		for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
			if (itemVec[i].size() > 0) {
				selectedItem.row = i;//�����s�̊m��
				for (int row = 0; row < csvItem[(int)GAME_TYPE::DODGE].rows(); row++) {
					if (User::getHasItems((GAME_TYPE)i, csvItem[i].get<int>(row, 0))) {
						selectedItem.column = row;//������̊m��
						break;
					}
				}
				break;
			}
		}
	}
	else {//�A�C�e���������Ă��Ȃ��Ȃ�߂�{�^���������I����Ԃɂ���
		isButtonSelect = true;
		//�����Ă��Ȃ��̂ŃA�C�e��������Ԃ�-1��
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
	int column;//�߂�l
	int minColumn = 999999;//�����ŏ��l
	for (auto vec : itemVec[row]) {
		if (std::abs(selectedItem.column - vec) < minColumn) {
			minColumn = std::abs(selectedItem.column - vec);
			column = vec;
		}
	}
	return column;
}

void MyRoomCollection::changeAlpha(void) {
	constexpr int CYCLE = 3000;//���߂��ς�����
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}

void MyRoomCollection::deci2Play() {
	AudioAsset(U"deci2").setPosSec(0);
	AudioAsset(U"deci2").setVolume(0.2);
	AudioAsset(U"deci2").play();

}