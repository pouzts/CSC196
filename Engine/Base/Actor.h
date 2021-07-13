#pragma once
#include "core.h"
#include "Base/Object.h"
#include "Math/Transform.h"

namespace PhoenixEngine
{
	class Shape;

	class Actor : public Object
	{
	public:
		Actor(const Transform& transform, Shape* shape) : transform{ transform }, shape{ shape } {}

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);
	
	public:
		Transform transform;
		Shape* shape;
	};
}