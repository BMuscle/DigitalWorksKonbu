#include "MyEffects.h"

MyEffects::MyEffects() {
	stopwatch.start();//ストップウォッチスタート
}

MyEffects::~MyEffects() {

}

void MyEffects::add(EffectInterFace* effect, Vec2 pos) {
	EffectPack pack = { effect, pos, stopwatch.sF() };
	effects.push_back(pack);
}

void MyEffects::draw(){
	Print(stopwatch.sF());
	if (0 < effects.size()) {//エフェクトが存在する場合
		auto itr = effects.begin();
		while (itr != effects.end()) {//全てに対して計算描画処理
			float f = stopwatch.sF();
			if (itr->effect->update(stopwatch.sF() - itr->addTime, itr->pos)) {
				//描画正常終了
				itr++;			//次のイテレータへ更新
			}
			else {
				//描画が終了している場合削除処理
				auto tmp = itr;		//一旦退避させる
				itr++;				//次のイテレータへ更新
				effects.erase(tmp);	//リストから消去する
			}
		}
	}
}

void MyEffects::pause() {
	stopwatch.pause();
}

void MyEffects::resume() {
	stopwatch.resume();
}

bool MyEffects::isPaused() {
	return stopwatch.isPaused();
}

void MyEffects::clear() {
	effects.clear();
}

bool MyEffects::isEmpty() {
	return effects.empty();
}