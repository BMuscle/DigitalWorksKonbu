#include"DodgeGame.h"
#include<Siv3D.hpp>

DodgeGame::DodgeGame(DODGE_SCENE* nextScene) :DodgeSceneBase(nextScene) {
	TextureAsset::Register(U"gameback",U"resources/images/backs/10278318_p0_master1200.jpg");
}

DodgeGame::~DodgeGame()
{

}
void DodgeGame::start(void)
{

}
void DodgeGame::update()
{
	
}
void DodgeGame::draw()
{
	TextureAsset(U"gameback").draw();
}