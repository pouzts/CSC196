#pragma once
#include "Base/Actor.h"

class Player : public PhoenixEngine::Actor
{
public:
	Player(const PhoenixEngine::Transform& transform, std::shared_ptr<PhoenixEngine::Shape> shape, float speed) : Actor{ transform, shape }, speed{speed} {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 0.2f };
	float speed{ 300 };
};