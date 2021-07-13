#pragma once
#include "Base/Actor.h"

class Player : public PhoenixEngine::Actor
{
public:
	Player(const PhoenixEngine::Transform& transform, PhoenixEngine::Shape* shape, float speed) : Actor{ transform, shape }, speed{speed} {}

	void Update(float dt) override;

private:
	float speed{ 300 };
};