#pragma once
#include "Vector2.h"
#include "Matrix22.h"
namespace PhoenixEngine
{
	struct Transform
	{
		Vector2 position;
		float rotation{0};
		float scale{1};

		Matrix22 matrix;

		Transform() {}
		Transform(const Vector2& position, float rotation = 0, float scale = 1) : position{ position }, rotation{ rotation }, scale{ scale } {}

		void Update();
	};
}