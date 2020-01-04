#pragma once
#include <Siv3D.hpp>

class GachaItemDescription {
private:
	Texture texture;
	String text;
	Font font;
public:
	GachaItemDescription(String path, String text, int fontSize);
	~GachaItemDescription();

	void drawAt(int x, int y);
};