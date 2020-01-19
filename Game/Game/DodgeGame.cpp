#include"DodgeGame.h"
#include<Siv3D.hpp>
#include"MyKey.h"


DodgeGame::DodgeGame(DODGE_SCENE* nextScene) :DodgeSceneBase(nextScene) {
	TextureAsset::Register(U"gameback",U"resources/images/backs/10278318_p0_master1200.jpg");
	TextureAsset::Register(U"rule",U"resources/images/backs/rule.jpg");
	TextureAsset::Register(U"landscape",U"resources/images/backs/landscape.jpg");

	//TextureAsset::Register(U"Scopeimage", U"resource/images/backs/landscape.jpg");
	nowselect = START;
}

DodgeGame::~DodgeGame()
{

}
void DodgeGame::start(void)
{

}
void DodgeGame::update()
{
	if (nowselect==START) {
		nowselect = RULE;
	}
	else if (nowselect == RULE && MyKey::getDecisionKey()) {
		nowselect = GAME;
	}

}

void DodgeGame::draw()
{
	switch (nowselect)
	{
		case START:
			break;
		case RULE:
			TextureAsset(U"rule").draw();
			break;
		case GAME:
			
			Match();
			
		default:
			break;
	}
}

bool DodgeGame::HitCheck(int r1, Vec2 z1, int r2, Vec2 z2)
{	//�֐����œ����蔻��̕�����
	float d;
	Vec2 gap(z2 - z1);
	d = sqrt((gap.x * gap.x) + (gap.y * gap.y));

	if (r1+r2>=d) {//����l���߂�
		return true;	
	}
		return false;
}


void DodgeGame::Match()
{
	//�Q�[���X�^�[�g�I�i�����j�i���ʉ��j

	//�R���X�g���N�^
	int radius = 20;
	float movement = 0.001;
	//int count = 0;
	Vec2 initial(480, 450);
	Target target(50,initial);	//{x,y}�����_�Ƃ������ar�̉~
	Vec2 spawn(340,60);
	Scope scope(40, spawn);
	Vec2 random1(Random(0,1900),Random(0,1000));
	Vec2 random2(Random(0, 1900), Random(0, 1000));
	Vec2 random3(Random(0, 1900), Random(0, 1000));
	Vec2 random4(Random(0, 1900), Random(0, 1000));
	Vec2 random5(Random(0, 1900), Random(0, 1000));
	Mob Mob1(random1);
	Mob Mob2(random2);
	Mob Mob3(random3);
	Mob Mob4(random4);
	Mob Mob5(random5);

	const Texture Scopeimage(U"resources/images/backs/Scopeimage.png");
	const Texture Targetimage(U"resources/images/backs/Target.png");
	const Texture Mobimage(U"resources/images/backs/Mob.png");

	/*const Texture Mobimage1(U"resources/images/backs/Mob1.png");
	const Texture Mobimage2(U"resources/images/backs/Mob2.png");
	const Texture Mobimage3(U"resources/images/backs/Mob3.png");
	const Texture Mobimage4(U"resources/images/backs/Mob4.png");
	*/

	
	while(System::Update())
	{
		//�ꏊ�̃Z�b�g 
		target.setPlace(target.getPlace() + target.Getmovement(target.getPlace(), movement));	
		Mob1.setPlace(Mob1.getPlace() + Mob1.Getmovement(Mob1.getPlace(),movement));
		Mob2.setPlace(Mob2.getPlace() + Mob2.Getmovement(Mob2.getPlace(), movement));
		Mob3.setPlace(Mob3.getPlace() + Mob3.Getmovement(Mob3.getPlace(), movement));
		Mob4.setPlace(Mob4.getPlace() + Mob4.Getmovement(Mob4.getPlace(), movement));
		Mob5.setPlace(Mob5.getPlace() + Mob5.Getmovement(Mob5.getPlace(), movement));
		scope.setPlace(scope.getPlace() + Vec2(0, 5));//�X�V����update


		//�^�[�Q�b�g�̕`��
		Targetimage.drawAt(target.getPlace());

		//���u�̕`��
		Mobimage.drawAt(Mob1.getPlace());
		Mobimage.drawAt(Mob2.getPlace());
		Mobimage.drawAt(Mob3.getPlace());
		Mobimage.drawAt(Mob4.getPlace());
		Mobimage.drawAt(Mob5.getPlace());

		//�X�R�[�v�̕`��
		Scopeimage.drawAt(scope.getPlace());//�`�揈��draw

		
			
		//Circle scopeimage(scope.getPlace(), scope.getRadius());
		//�����蔻��`�F�b�N�@���������Ƃ��A������悤�Ɏd������
		if (HitCheck(scope.getRadius(),scope.getPlace(),target.getRadius()-10,target.getPlace())==true){//�X�R�[�v�A�^�[�Q�b�g
			scope.setPlace(scope.getPlace() + Vec2(0, -5));//�X�V����update ����������~�܂�
			
		}

		//�ĕ`��
		if (scope.getPlace().y > Window::ClientHeight() * 0.5) {//���܂ōs������
			scope.setPlace(Vec2(scope.getPlace().x + 30, -50));
		}
		
		
		Rect(0, Window::ClientHeight() * 0.5, Window::ClientWidth(), 10).draw(ColorF(1, 0, 0));
		for (int i = 0; i < 20; i++) {
			Rect(i * 100, Window::ClientHeight() * 0.5, 3, 100).draw(ColorF(1, 0, 0));
		}
	}

}