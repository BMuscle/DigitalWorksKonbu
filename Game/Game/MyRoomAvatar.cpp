#include "MyRoomAvatar.h"

MyRoomAvatar::MyRoomAvatar(MYROOM_SCENE* scenep) :MyRoomSceneBase(scenep) {
	TextureAsset::Register(U"myroomback", U"resources/images/backs/myroom/avatar.png", AssetParameter::LoadAsync());
}
MyRoomAvatar::~MyRoomAvatar() {
	TextureAsset::Unregister(U"myroomback");
}
bool MyRoomAvatar::isReady() {
	if (TextureAsset::IsReady(U"myroomback")) {
		return true;
	}
	return false;
}
void MyRoomAvatar::start() {

}
void MyRoomAvatar::update() {
	if (MyKey::getDecisionKey()) {
		setNextScene(MYROOM_SCENE::TITLE);
	}
}
void MyRoomAvatar::draw() {
	//”wŒi‚Ì•`‰æ
	TextureAsset(U"myroomback").draw();
}