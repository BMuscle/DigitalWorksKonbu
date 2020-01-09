#include "MyRoomReport.h"

MyRoomReport::MyRoomReport(MYROOM_SCENE* scenep) : MyRoomSceneBase(scenep){
	TextureAsset::Register(U"myroomback", U"resources/images/backs/myroom/recode.png", AssetParameter::LoadAsync());
	//�A�Z�b�g�փ��[�h
	FontAsset::Register(U"myroomfont", 80, AssetParameter::LoadAsync());
	FontAsset::Preload(U"myroomfont");

	FontAsset::Register(U"myroomsmallfont", 50, AssetParameter::LoadAsync());
	FontAsset::Preload(U"myroomsmallfont");

	//�ϐ�������
	user_name = User::getUser_Name();			//���[�U�[��
	itemAcquisitionRate = User::getItemAcquisitionRate();	//�A�C�e���擾��
	total_play_time = User::getTotalPlayTime();
	for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
		gameHighScore[i] = User::getGameHighScore((GAME_TYPE)i);//�Q�[�����n�C�X�R�A
		gamePlayCount[i] = User::getGamePlayCount((GAME_TYPE)i);//�Q�[�����v���C��
	}
	age = calcAge();					//�Q�[�����N��

	if (age >= 70) {
		TextureAsset::Register(U"myroomword", U"resources/images/items/myroom/report/word70.png", AssetParameter::LoadAsync());
	}
	else if (age >= 50) {
		TextureAsset::Register(U"myroomword", U"resources/images/items/myroom/report/word50.png", AssetParameter::LoadAsync());
	}
	else if (age >= 30) {
		TextureAsset::Register(U"myroomword", U"resources/images/items/myroom/report/word30.png", AssetParameter::LoadAsync());
	}
	else {
		TextureAsset::Register(U"myroomword", U"resources/images/items/myroom/report/word0.png", AssetParameter::LoadAsync());
	}

}	
MyRoomReport::~MyRoomReport() {
	TextureAsset::Unregister(U"myroomback");
	TextureAsset::Unregister(U"myroomword");
}
bool MyRoomReport::isReady() {
	if (TextureAsset::IsReady(U"myroomback") &&
		TextureAsset::IsReady(U"myroomword") &&
		FontAsset::IsReady(U"myroomfont") &&
		FontAsset::IsReady(U"myroomsmallfont")) {
		return true;
	}
	return false;
}
void MyRoomReport::start() {

}
void MyRoomReport::update() {
	if (MyKey::getDecisionKey()) {
		GeneralSoundEffects::play(SE_NAME::DECISION);
		setNextScene(MYROOM_SCENE::TITLE);
	}

	Print(U"�N��=" + Format(age));

	changeAlpha();
}
void MyRoomReport::draw() {
	//�w�i�̕`��
	TextureAsset(U"myroomback").draw();

	//��������W�i�[
	constexpr Vec2 nameVec2(1000,310),
				   ageVec2(1000,415),
				   pointVec2(1000,583),
				   itemVec2(1000,657),
				   playTimeVec2(1000,733),
				   wordVec2(1150, 905);

	//������`��
	FontAsset(U"myroomfont")(user_name).draw(nameVec2, Color(0,0,0));
	FontAsset(U"myroomfont")(Format(age) + U"��").draw(ageVec2, Color(0, 0, 0));
	FontAsset(U"myroomsmallfont")(Format(User::getUserPoint()) + U"P").draw(pointVec2, Color(0, 0, 0));
	FontAsset(U"myroomsmallfont")(Format((int)(itemAcquisitionRate * 100)) + U"%").draw(itemVec2, Color(0, 0, 0));
	FontAsset(U"myroomsmallfont")(total_play_time).draw(playTimeVec2, Color(0, 0, 0));
	//���]�`��
	TextureAsset(U"myroomword").drawAt(wordVec2);

	FontAsset(U"myroomsmallfont")(U"�`Press to Enter�`").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 70, ColorF(0, 0, 0));
	FontAsset(U"myroomsmallfont")(U"�`Press to Enter�`").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 70, AlphaF(alpha));



}

int MyRoomReport::calcAge() {
	constexpr float baseAge = 40;//��͂S�O��
	float weight = 0;//�{����0.1 ���� 2�܂�

	constexpr float gameCountWeiht = 10.0;//�Q�[���񐔂Ɋ|����d��
	constexpr float gameScoreWeight = 0.1;//�Q�[���X�R�A�Ɋ|����d��
	float tmp = 0;
	for (int i = 0; i < (int)GAME_TYPE::SIZE; i++) {
		tmp += gameHighScore[i] * gameScoreWeight* gamePlayCount[i] * gameCountWeiht;
	}

	weight = (float)tmp / 1000.0;//�d�݂Ŋ���
	float t = itemAcquisitionRate;//�A�C�e���擾����������
	if (t <= 0.3) {
		t = 0.3;
	}
	weight *= t;

	weight = 2.0 - weight;
	if (weight < 0.1) {
		weight = 0.1;
	}


	return baseAge * weight;
}

void MyRoomReport::changeAlpha(void) {
	constexpr int CYCLE = 3000;//���߂��ς�����
	const uint64 t = Time::GetMillisec();
	alpha = Sin(t % CYCLE / static_cast<double>(CYCLE)* s3d::Math::Constants::TwoPi) * 0.42 + 0.58;
}