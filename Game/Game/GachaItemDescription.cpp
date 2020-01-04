#include "GachaItemDescription.h"

GachaItemDescription::GachaItemDescription(String path, String text, int fontSize) {
	texture = Texture(path);
	this->text = text;
	font = Font(fontSize);
}
GachaItemDescription::~GachaItemDescription() {
	font.release();
	texture.release();
}

void GachaItemDescription::drawAt(int x, int y) {
	texture.drawAt(x, y);
	font(text).drawAt(x, y - texture.height() * 0.1, ColorF(0,0,0));
}