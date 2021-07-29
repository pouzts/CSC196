#include "Actor.h"
#include "Graphics/Shape.h"
#include <algorithm>

namespace PhoenixEngine
{
	void Actor::Initialize()
	{
	}
	void Actor::Update(float dt)
	{
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		if (shape) 
		{
			shape->Draw(graphics, transform);
		}

		std::for_each(children.begin(), children.end(), [graphics](auto& child) mutable { if (child->shape) child->shape->Draw(graphics, child->transform); });
	}

	void Actor::AddChild(std::unique_ptr<Actor> child)
	{
		child->parent = this;
		children.push_back(std::move(child));
	}

	float Actor::GetRadius()
	{
		return (shape) ? shape->radius * transform.scale.x : 0;
	}
}