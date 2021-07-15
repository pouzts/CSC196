#pragma once
#include "Base/Actor.h"

class Enemy : public PhoenixEngine::Actor
{
public:
	Enemy(const PhoenixEngine::Transform& transform, std::shared_ptr<PhoenixEngine::Shape> shape, float speed) : Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;

private:
	float speed{ 300 };
};