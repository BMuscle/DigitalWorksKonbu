#include "ShoeKick.h"
#include <Siv3D.hpp>
#include "MyKey.h"


ShoeKick::ShoeKick(void) {
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"shoekickfont", 70);
	FontAsset::Preload(U"shoekickfont");
	TextureAsset::Register(U"shoekickback", U"resources/images/backs/shoekick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_title", U"resources/images/items/game/shoekick/title.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_kick", U"resources/images/items/game/shoekick/kick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_fly", U"resources/images/items/game/shoekick/fry.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_fall", U"resources/images/items/game/shoekick/fall.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_sunny", U"resources/images/items/game/shoekick/sunny.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_rain", U"resources/images/items/game/shoekick/rain.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"shoekick_cloudy", U"resources/images/items/game/shoekick/cloudy.png", AssetParameter::LoadAsync());

	nowScene = TITLE;//�����V�[���Z�b�g
	nextScene = TITLE;
}
ShoeKick::~ShoeKick(void) {
	FontAsset::Unregister(U"shoekickfont");
	TextureAsset::Unregister(U"shoekickback");
	delete backAudio;
}
bool ShoeKick::isReady(void) {	//���[�h�I�����Ă��������ǂ���
	if (TextureAsset::IsReady(U"shoekickback")) {
		return true;
	}
	return false;
}
void ShoeKick::start(void) {	//���[�h�󂯂���Ɏ��s��������
	//BGM�Đ��J�n
	backAudio = new Audio(U"resources/musics/backs/shoekick.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void ShoeKick::update(void) {	//�v�Z����
	if (nowScene != nextScene) {
		changeScene();
	}
	switch (nowScene) { 
	case TITLE:/*�^�C�g��*/

		if (MyKey::getDecisionKey()) { //�G���^�[�����ꂽ�炯���ʂɈڍs����
			setNextScene(KICK);
		}
		break;

	case KICK: /*����U���đ���������Ă��Ĕ�΂��܂ł̉��*/
		
	
		
		while (countDown<0) {

			countDown = countDown - 1;

		};

		setNextScene(FLY);
		break;
	case FLY:/*�o���������狗��������ČC���΂����*/
		//�o�������ɉ�������������ċ������o��
		break;
	case FALL:/*�C�𗎉���������*/

		if (MyKey::getDecisionKey()) { //�G���^�[�����ꂽ��V�C�̉�ʂɈڍs����
			setNextScene (RESULT);
		}
		break;

	case RESULT:/*�����ɂ���ĕ\������V�C��ς���E������x�Q�[�������邩�}�b�v�ɖ߂邩���m�F������*/
		//������x�Q�[�����v���C���邩�}�b�v�ɖ߂邩�����L�[�őI�����ăG���^�[�Ō��� 
		break;

	}

}
void ShoeKick::draw(void) {	//�`�揈��

	switch (nowScene) { //��ʐ؂�ւ��̃t���O

	case TITLE://home
		TextureAsset(U"shoekick_title").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	case KICK://keru
		TextureAsset(U"shoekick_kick").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		FontAsset(U"shoekickfont")(U"�J�E���g�_�E��" + Format(countDown)).drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2, ColorF(0,0,0));
		break;
	case FLY://tonnderu
		TextureAsset(U"shoekick_fly").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	case FALL:
		TextureAsset(U"shoekick_fall").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	case RESULT:
		TextureAsset(U"shoekick_sunny").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		TextureAsset(U"shoekick_rain").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		TextureAsset(U"shoekick_cloudy").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		break;
	}
}
void ShoeKick::outputResult(void) {//���ʂ�DB�֏o�͂���

}

void ShoeKick::changeScene() {
	switch (nowScene)//�I������
	{
	case ShoeKick::TITLE:
		break;
	case ShoeKick::KICK:
		break;
	case ShoeKick::FLY:
		break;
	case ShoeKick::FALL:
		break;
	case ShoeKick::RESULT:
		break;
	}
	switch (nextScene)//����������
	{
	case ShoeKick::TITLE:
		break;
	case ShoeKick::KICK:
		countDown = 3;
		break;
	case ShoeKick::FLY:
		break;
	case ShoeKick::FALL:
		break;
	case ShoeKick::RESULT:
		break;
	}
	nowScene = nextScene;
}
void ShoeKick::setNextScene(SCENE next) {
	nextScene = next;
}



