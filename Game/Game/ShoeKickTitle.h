#pragma once

#include <Siv3D.hpp>
#include "MySceneManager.h"
#include "ShoeKickSceneBase.h"
#include "GeneralSoundEffects.h"
#include "MyImageButton.h"

class ShoeKickTitle : public ShoeKickSceneBase{
private:
	Audio* backAudio;

	bool isDescription;//ê‡ñæï\é¶ÉtÉâÉO

	enum BUTTON {
		MAP,
		GAME,
		SIZE,
	};

	BUTTON selectButton;
	MyImageButton* button[BUTTON::SIZE];

public:
	ShoeKickTitle(SHOEKICK_SCENE* scenep, bool isDescription = false);
	~ShoeKickTitle();

	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
};
