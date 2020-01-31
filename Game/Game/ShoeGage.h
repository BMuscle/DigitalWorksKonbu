#pragma once
#include <Siv3D.hpp>
#include <stdlib.h>

constexpr Vec2 POS = Vec2(1920 / 2, 230);
//constexpr Vec2 GAGE = Vec2(107, 523);
constexpr Vec2 GAGE = Vec2(58, 478);

class ShoeGage {
private:
	float power;
	float nowGage;
	Rect rect;
	Texture texture[10];
public:

	ShoeGage() {
		TextureAsset::Register(U"gageback", U"resources/images/items/game/shoekick/game/gageback.png");
		TextureAsset::Register(U"gageline", U"resources/images/items/game/shoekick/game/gageline.png");
		Image baseImage(U"resources/images/items/game/shoekick/game/gage.png");
		for (int i = 0; i < 10; i++) {
			texture[i] = Texture(baseImage.clipped(0, i * 103, baseImage.width(), 103));
		}

		power = 0;
		nowGage = 0;
	}
	~ShoeGage() {
		TextureAsset::Unregister(U"gageback");
		TextureAsset::Unregister(U"gageline");
		TextureAsset::Unregister(U"gage");
	}
	void setPower(float power) {
		this->power = std::max(power, this->power);
	}

	void update() {
		if (power > 0) {
			nowGage += 0.02;
			if (nowGage > power) {
				nowGage = power;
			}
		}
	}
	void draw() {
		int i = (int)(nowGage * 10.0);
		if (i > 9) {
			i = 9;
		}
		texture[i].drawAt(POS.x, POS.y - i);
		/*
		TextureAsset(U"gageback").drawAt(POS);
		
		rect = Rect(POS.x - (GAGE.x / 2.0 + 1), POS.y - (GAGE.y / 2.0 + 13), GAGE.x, GAGE.y - GAGE.y * nowGage).draw(ColorF(0,0,0));

		TextureAsset(U"gageline").drawAt(POS);
		*/

	}
};

