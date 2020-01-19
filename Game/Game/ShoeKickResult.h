#pragma once

#include <Siv3D.hpp>
#include "MySceneManager.h"
#include "ShoeKickSceneBase.h"
#include "GeneralSoundEffects.h"

class ShoeKickResult : public ShoeKickSceneBase {
private:
	Audio* backAudio;
	int meter;
	int point;
	bool isHighScoreUpdate;

	float alpha;
	void changeAlpha(void);
public:
	ShoeKickResult(SHOEKICK_SCENE* scenep, int meter);
	~ShoeKickResult();

	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
};
