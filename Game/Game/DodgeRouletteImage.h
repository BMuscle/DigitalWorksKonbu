#pragma once

#include <Siv3D.hpp>
#include "DodgeRouletteBase.h"

//１枚の画像をぐるぐるまわし、描画する
class DodgeRouletteImage : public DodgeRouletteBase {
public:
	DodgeRouletteImage(String filepath, String fileName, Vec2 pos, int endFrame = 60, int intervalFrame = 5, bool flag = false) : DodgeRouletteBase(1, endFrame, intervalFrame, flag) {
		this->pos = pos;
		fileNames = FileSystem::DirectoryContents(filepath);
		int i = 0;
		for (auto name : fileNames) {
			textures.push_back(Texture(filepath + U"/" + FileSystem::BaseName(name) + U".png"));
			if (FileSystem::BaseName(name).compare(FileSystem::BaseName(fileName)) == 0) {
				baseIndex = i;
			}
			i++;
		}
		

	}
	~DodgeRouletteImage() {

	}
	void draw() override {
		if (isRoulette()) {
			textures.at(index).drawAt(pos);
		}
		else {
			textures.at(baseIndex).drawAt(pos);
		}
	}
protected:
	//ルーレット中にインターバルの間隔で呼ばれる
	void updateRoulette() override {
		index = getRandomImageIndex();
	}
private:
	Vec2 pos;
	Array<String> fileNames;
	Array<Texture> textures;
	int baseIndex;//正しい画像のindex
	int index;
	


	int getRandomImageIndex() {
		return Random(textures.size() - 1);
	}
};