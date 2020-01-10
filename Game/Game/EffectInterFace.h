#pragma once
#include <Siv3D.hpp>
class EffectInterFace {
public:
	EffectInterFace() {

	}
	~EffectInterFace() {

	}
	virtual bool update(float t, const Vec2& pos) = 0;
};