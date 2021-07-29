#pragma once
#include "Base\Actor.h"
class PowerUp : public PhoenixEngine::Actor
{
public:
	PowerUp(const PhoenixEngine::Transform& transform, std::shared_ptr<PhoenixEngine::Shape> shape) : Actor{ transform, shape } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
};

