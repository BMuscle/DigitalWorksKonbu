#include "Game.h"

//�|�b�v�A�b�v�̃{�^���̗���Ă���Ԋu���`
#define POPUP_INTERVAL (Window::ClientWidth() * 0.12)

Game::Game(MODE gamemode) {
	switch (gamemode) {//�n���ꂽ�Q�[���̎�ނɂ���ĕύX����
	case MODE::SOCCER:
		minigame = new Soccer();
		break;
	case MODE::DODGE:
		minigame = new Dodge();
		break;
	case MODE::SHOEKICK:
		minigame = new ShoeKick();
		break;
	default:
		//�G���[
		break;
	}

	isStop = false;
	TextureAsset::Register(U"stopback", U"resources/images/items/game/stopback.png");
	TextureAsset::Register(U"wordok", U"resources/images/items/game/ok.png");
	TextureAsset::Register(U"wordnot", U"resources/images/items/game/not.png");

	//�|�b�v�A�b�v�̃{�^��������
	popUpButton[(int)POPUP::RESTART] = new MyImageButton(U"resources/images/items/game/restart", U"", 0, (int)(Window::ClientWidth() / 2) + (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, true);
	popUpButton[(int)POPUP::NEXTMAP] = new MyImageButton(U"resources/images/items/game/nextmap", U"", 0, (int)(Window::ClientWidth() / 2) - (int)POPUP_INTERVAL, (int)Window::ClientHeight() * 0.6, false);

	popUpState = POPUP::NONE;//�|�b�v�A�b�v�I���̏�����Ԃ�NONE��
}
Game::~Game(void) {
	delete minigame;
	TextureAsset::Unregister(U"stopback");
	TextureAsset::Unregister(U"wordok");
	TextureAsset::Unregister(U"wordnot");
}
bool Game::isReady(void) {
	if (minigame->isReady() && 
		popUpButton[(int)POPUP::RESTART]->isReady() &&
		popUpButton[(int)POPUP::NEXTMAP]->isReady()) {
		return true;
	}
	return false;
}
void Game::start(void) {
	minigame->start();
}
void Game::update(void) {
	if (MySocketServer::isConnection()) {//�R���g���[���[�R�l�N�V�����m����
		if (isStop) {
			if (MyKey::getRightKeyDown()) {
				popUpState = POPUP::RESTART;//�|�b�v�A�b�v���}�b�v�ւ�
				GeneralSoundEffects::play(SE_NAME::CURSOR);
			}
			else if (MyKey::getLeftKeyDown()) {
				popUpState = POPUP::NEXTMAP;//�|�b�v�A�b�v���}�b�v�ւ�
				GeneralSoundEffects::play(SE_NAME::CURSOR);
			}
		}
		else {
			minigame->update();//�Q�[���i�s
		}
	}
	else {//�R�l�N�V�����ؒf��
		if (isStop) {
			if (MyKey::getRightKeyDown()) {
				GeneralSoundEffects::play(SE_NAME::BACK);
			}
			else if (MyKey::getLeftKeyDown()) {
				popUpState = POPUP::NEXTMAP;//�|�b�v�A�b�v���}�b�v�ւ�
				GeneralSoundEffects::play(SE_NAME::CURSOR);
			}
		}
		else {//�n�߂Đؒf���ꂽ��
			isStop = true;//true�ɕύX
			minigame->stopGame();//��~����
			popUpState = POPUP::NEXTMAP;//�|�b�v�A�b�v���}�b�v�ւ�
			GeneralSoundEffects::play(SE_NAME::CANCEL);
		}
	}

	if (isStop && MyKey::getDecisionKey()) {
		switch (popUpState)
		{
		case Game::POPUP::RESTART:
			isStop = false;//���Q�[���X�g�b�v����
			popUpState = POPUP::NONE;//�|�b�v�A�b�v���}�b�v�ւ�
		//�Q�[��restart�����K�{
			break;
		case Game::POPUP::NEXTMAP:
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
			break;
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}
}
void Game::draw(void) {
	minigame->draw();
	if (isStop) {

		//�|�b�v�A�b�v�w�i��`��
		TextureAsset(U"stopback").drawAt(Window::ClientWidth() * 0.5, Window::ClientHeight() * 0.45);

		if (MySocketServer::isConnection()) {//�R���g���[���[�R�l�N�V�����m����
			TextureAsset(U"wordok").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
		}
		else {//�ؒf��
			TextureAsset(U"wordnot").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() * 0.4);
		}

		switch (popUpState)
		{
		case POPUP::RESTART://YES���I������Ă���Ƃ� �I����Ԃ�ύX
			//�`�揈��
			popUpButton[(int)POPUP::RESTART]->drawNotWord(true);
			popUpButton[(int)POPUP::NEXTMAP]->drawNotWord(false);
			break;
		case POPUP::NEXTMAP://NO���I������Ă���Ƃ� �I����Ԃ�ύX
			//�`�揈��
			popUpButton[(int)POPUP::RESTART]->drawNotWord(false);
			popUpButton[(int)POPUP::NEXTMAP]->drawNotWord(true);
			break;
		}
	}
}