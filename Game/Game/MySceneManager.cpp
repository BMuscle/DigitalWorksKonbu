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
			loadEffect->nextState();
			break;
		case LOAD_STATE::BLACK://���[�h��
			if (scene->isReady()) {//���[�h���I������Ȃ�
				loadEffect->nextState();
			}
			break;
		case LOAD_STATE::BRIGHT://�^�����̉�ʂɂȂ���
			scene->start();
			loadEffect->nextState();
			NOWSCENE = NEXTSCENE;//�V�[���ڍs����������
			MyKey::setKeyLock(false);//�L�[���͂̃��b�N����
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
	loadEffect->loadStart();//���[�h���J�n������
	MyKey::setKeyLock(true);//�L�[���͂�lock����
}

void MySceneManager::changeScene() {
	int user_id = 0;
	switch (NEXTSCENE) {//nextscene��NONE�ȊO�̎��V�[���ڍs����
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
