#pragma once
#include "core.h"
#include "Base/Object.h"
#include "Math/Transform.h"
#include <memory>

namespace PhoenixEngine
{
	class Shape;
	class Scene;

	class Actor : public Object
	{
	public:
		Actor(const Transform& transform, std::shared_ptr<Shape> shape) : transform{ transform }, shape{ shape } {}

		virtual void Update(float dt) {}
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();
	
	public:
		bool destroy = false;
		std::string tag;

		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene{nullptr};
	};
}