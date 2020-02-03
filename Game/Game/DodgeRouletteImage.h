#pragma once

#include <Siv3D.hpp>
#include "DodgeRouletteBase.h"

//�P���̉摜�����邮��܂킵�A�`�悷��
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
	//���[���b�g���ɃC���^�[�o���̊Ԋu�ŌĂ΂��
	void updateRoulette() override {
		index = getRandomImageIndex();
	}
private:
	Vec2 pos;
	Array<String> fileNames;
	Array<Texture> textures;
	int baseIndex;//�������摜��index
	int index;
	


	int getRandomImageIndex() {
		return Random(textures.size() - 1);
	}
};