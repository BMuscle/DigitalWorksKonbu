#include "ShoeCharacter.h"

constexpr int CHAR_CHIP_SIZE = 3;
constexpr float moveSpeedX = 3.5;

ShoeCharacter::ShoeCharacter(Vec2 init): moveSpeed(Vec2(moveSpeedX,0)) {
	pos = init;
	Image baseImage = Image(U"resources/images/items/game/shoekick/human.png");
	for (int i = 0; i < CHAR_CHIP_SIZE; i++) {
		textureArray.push_back(new Texture(baseImage.clipped(i * (baseImage.width() / CHAR_CHIP_SIZE),
			0, baseImage.width() / CHAR_CHIP_SIZE,
			baseImage.height())));
	}
	textureIndex = 0;
	isJump = false;
	isMove = false;
	jumpSpeed = Vec2(0, 0);
	moveCnt = 0;

	AudioAsset::Register(U"jump", U"resources/musics/items/game/shoekick/jump.wav");
	AudioAsset::Register(U"dash", U"resources/musics/items/game/shoekick/dash.wav");
}
ShoeCharacter::~ShoeCharacter() {
	for (int i = 0; i < textureArray.size(); i++) {
		delete textureArray.at(i);
	}
}


void ShoeCharacter::update() {
	constexpr int MOVE_CNT_LIMIT = 5;
	if (isMove) {
		if (!AudioAsset(U"dash").isPlaying()) {
			AudioAsset(U"dash").setPosSec(0);
			AudioAsset(U"dash").setVolume(0.4);
			AudioAsset(U"dash").play();
		}
		moveRight();
		moveCnt++;
		//フレーム制限必要かも？
		if (moveCnt % MOVE_CNT_LIMIT == 0) {
			textureIndex++;
			if (textureIndex >= textureArray.size()) {
				textureIndex = 0;
			}
		}
		isMove = false;
	}
	else {
		AudioAsset(U"dash").stop();
	}
	if (isJump) {
		textureIndex = 0;
		moveJump();
		if (GROUND < pos.y) {
			pos.y = GROUND;
			isJump = false;
		}
	}

}
void ShoeCharacter::setMoveRight() {
	isMove = true;
}
void ShoeCharacter::setMoveJump() {
	isJump = true;
	jumpSpeed = Vec2(0, -23.5);
	AudioAsset(U"jump").setPosSec(0);
	AudioAsset(U"jump").setVolume(0.1);
	AudioAsset(U"jump").play();

}

void ShoeCharacter::moveRight() {
	pos += moveSpeed;
}
void ShoeCharacter::moveJump() {
	pos += jumpSpeed;
	jumpSpeed.y += 1.5;	
}
void ShoeCharacter::draw() {
	textureArray.at(textureIndex)->drawAt(pos);
}
void ShoeCharacter::setVecMoveLeft(int x) {
	pos.x = x;
}

Vec2 ShoeCharacter::getPos() {
	return pos;
}