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
	if (NOWSCENE != NEXTSCENE) {//�V�[���ڍs��
		switch (loadEffect->getLoadState())
		{
		case LOAD_STATE::DARK://�^�����̉�ʂɂȂ���
			changeScene();//�V�[���ڍs
			if (scene->isReady()) {//���[�h���I������Ȃ�
				loadEffect->nextState();
			}
			break;
		case LOAD_STATE::BRIGHT://�^�����̉�ʂɂȂ���
			scene->start();
			loadEffect->nextState();
			NOWSCENE = NEXTSCENE;//�V�[���ڍs����������
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

	switch (NEXTSCENE) {//nextscene��NONE�ȊO�̎��V�[���ڍs����
	case SCENE::TITLE:
		delete scene;
		scene = new Title();
		break;
	}

}
