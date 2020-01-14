#include "MySceneManager.h"

LoadEffect* MySceneManager::loadEffect;
MyScene* MySceneManager::scene;
SCENE MySceneManager::NOWSCENE;
SCENE MySceneManager::NEXTSCENE;
bool MySceneManager::isLoadFinished;


void MySceneManager::initialize() {
	scene = new Title();
	((Title*)scene)->start();
	loadEffect = new LoadEffect();
	isLoadFinished = true;
}
void MySceneManager::finalize() {
	delete scene;
}
void MySceneManager::updateScene() {
	if (NOWSCENE != NEXTSCENE) {//シーン移行中
		switch (loadEffect->getLoadState())
		{
		case LOAD_STATE::DARK://真っ黒の画面になった
			changeScene();//シーン移行
			loadEffect->nextState();
			break;
		case LOAD_STATE::BLACK://ロード中
			if (scene->isReady()) {//ロードが終わったなら
				loadEffect->nextState();
			}
			break;
		case LOAD_STATE::BRIGHT://真っ白の画面になった
			scene->start();
			loadEffect->nextState();
			NOWSCENE = NEXTSCENE;//シーン移行を完了する
			MyKey::setKeyLock(false);//キー入力のロック解除
			break;
		default:
			break;
		}
		loadEffect->update();
	}
	scene->update();
}
void MySceneManager::drawScene() {
	scene->draw();
	loadEffect->draw();
}

void MySceneManager::setNextScene(SCENE next) {
	NEXTSCENE = next;
	loadEffect->loadStart();//ロードを開始させる
	MyKey::setKeyLock(true);//キー入力をlockする
}

void MySceneManager::changeScene() {
	int user_id = 0;
	switch (NEXTSCENE) {//nextsceneがNONE以外の時シーン移行する
	case SCENE::TITLE:
		delete scene;
		scene = new Title();
		break;
	case SCENE::SELECT_SAVEDATA:
		delete scene;
		scene = new SelectSaveData();
		break;
	case SCENE::CREATE_SAVEDATA:
		user_id = ((SelectSaveData*)scene)->getSelectUser_Id();
		delete scene;
		scene = new CreateSaveData(user_id);
		break;
	case SCENE::SELECT_MODE:
		delete scene;
		scene = new SelectMode();
		break;
	case SCENE::GAME:
		if (NOWSCENE == SCENE::SELECT_MODE) {
			MODE mode = ((SelectMode*)scene)->getSelectedMode();
			delete scene;
			scene = new Game(mode);
		}
		break;
	case SCENE::MYROOM:
		delete scene;
		scene = new MyRoom();
		break;
	case SCENE::GACHA:
		delete scene;
		scene = new Gacha();
		break;
	}

}
