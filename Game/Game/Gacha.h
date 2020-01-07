#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "MyImageButton.h"
#include "MyImageEffect.h"
#include "MyEffects.h"
#include "MyToast.h"
#include "SimpleLoadEffect.h"
#include "GachaItemDescription.h"
#include "GeneralSoundEffects.h"

//時間があればリファクタリング（クラス分け）

class Gacha : public MyScene {
public:
	Gacha(void);
	~Gacha(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;	//BGM

	SimpleLoadEffect* simpleLoadEffect;

	enum class GACHA_STATE {//ガチャの状態を表す
		TITLE,
		EFFECT,
		RESULT,
		END,

	};

	GACHA_STATE nowGachaState;	//現在のガチャの状態
	GACHA_STATE nextGachaState;	//移行したいガチャの状態

	MyEffects* effects;//ガチャエフェクト以外のエフェクト管理(明示的に分けたのはエフェクトの終了処理が欲しかったから）
	MyToast* toast;//トーストメッセージエフェクト

	MyEffects* gachaEffects;	//ガチャエフェクト管理用
	MyImageEffect* gachaEffect;	//ガチャを回している画像エフェクト 画像が大きいので２枚に分割



	enum class BUTTON {//ボタンの種類
		GACHA,
		EXIT,
		SIZE,
	};
	MyImageButton* button[(int)BUTTON::SIZE];	//画像ボタンクラス
	BUTTON selectedButton;						//現在選択されているボタン

	String itemName;//ガチャで取得したアイテムの名前

	//現在選択されているものの更新処理
	void selectedMove();

	//ボタンの描画処理
	void drawButton();

	//ガチャの状態移行要求をする
	void setNextGachaState(GACHA_STATE nextState);

	//ガチャの状態要求に応じて変更する
	void changeNextGachaState();

	//明るくなり始める時に実行する
	void loadBrightingFunc();

	//ロードが終わった時に実行する
	void loadEndFunc();

	//ガチャタイトル画面の計算処理
	void updateTitle();

	//ガチャが出来るかどうかのcheck エラー処理もこの中に
	bool isPlayGacha();

	//ガチャを行う
	void randomGacha();

	//ガチャ結果の描画
	void resultDraw();
};
