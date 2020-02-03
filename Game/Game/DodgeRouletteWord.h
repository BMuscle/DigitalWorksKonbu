#pragma once
#include <Siv3D.hpp>
#include "DodgeRouletteBase.h"

class DodgeRouletteWord : public DodgeRouletteBase {
public:
	DodgeRouletteWord(String drawWord, String useWord, Vec2 pos, Font font, Color color = Color(0,0,0), int endFrame = 60, int intervalFrame = 5, bool flag = false) : DodgeRouletteBase(drawWord.length(), endFrame, intervalFrame, flag){
		this->drawWordBase = drawWord;
		this->font = font;
		this->pos = pos;
		this->color = color;
		for (auto ch : useWord) {
			useChar.push_back(ch);
		}
		this->drawWord = getRandomWord();
	}
	~DodgeRouletteWord() {

	}
	void draw() override {
		if (isRoulette()) {
			font(drawWord).drawAt(pos, color);
		}
		else {
			font(drawWordBase).drawAt(pos, color);
		}
	}
protected:
	//ルーレット中にインターバルの間隔で呼ばれる
	void updateRoulette() override{
		drawWord = getRandomWord();
	}
private:
	String drawWord;
	String drawWordBase;
	Array<char32> useChar;
	Font font;
	Vec2 pos;
	Color color;

	String getRandomWord() {
		String tmp;
		for (int i = 0; i < getLength(); i++) {
			tmp.push_back(useChar.at(Random(useChar.size() - 1)));
		}
		return tmp;
	}
};