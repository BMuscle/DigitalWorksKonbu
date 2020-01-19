#pragma once
#include <Siv3D.hpp>

class Shoe {
private:
	bool isRotation;
	float angle;
	float angleSpeed;
	Texture* texture;
public:
	Shoe();
	~Shoe();
	void setAngle(bool rotate);
	void update();
	void draw(Vec2 pos);
};