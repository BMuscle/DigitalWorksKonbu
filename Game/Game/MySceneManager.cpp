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
			if (scene->isReady()) {//ロードが終わったなら
				loadEffect->nextState();
			}
			break;
		case LOAD_STATE::BRIGHT://真っ白の画面になった
			scene->start();
			loadEffect->nextState();
			NOWSCENE = NEXTSCENE;//シーン移行を完了する
			break;
		default:
			break;
		}
	}
	scene->update();
}
void MySceneManager::drawScene() {
	scene->draw();
	loadEffect->draw();
}

void MySceneManager::setNextScene(SCENE next) {
	NEXTSCENE = next;
}

void MySceneManager::changeScene() {

	switch (NEXTSCENE) {//nextsceneがNONE以外の時シーン移行する
	case SCENE::TITLE:
		delete scene;
		scene = new Title();
		break;
	}

}
