#pragma once
#include <Siv3D.hpp>
#include "ShoeKickGame.h"

class ShoeCharacter {
private:
	Vec2 pos;						//座標
	Array<Texture*> textureArray;	//連番画像
	int textureIndex;				//画像何枚目か
	const Vec2 moveSpeed;			//移動スピード
	Vec2 jumpSpeed;					//ジャンプするスピード
	bool isJump;					//ジャンプしているかフラグ
	bool isMove;					//移動しているかフラグ

	int moveCnt;					//何回移動したら、移動するかどうか

	void moveRight();				//右移動
	void moveJump();				//ジャンプ処理
public:
	ShoeCharacter(Vec2 init);
	~ShoeCharacter();
	//計算処理
	void update();
	//右移動フラグON
	void setMoveRight();
	//左へベクトル量移動させる
	void setVecMoveLeft(int x);
	//ジャンプフラグON
	void setMoveJump();
	//描画処理
	void draw();

	Vec2 getPos();
};