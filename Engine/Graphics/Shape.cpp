#include "Shape.h"

namespace PhoenixEngine {
	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale) {
		graphics.SetColor(color);
		
		for (size_t i = 0; i < points.size() - 1; i++)
		{
			PhoenixEngine::Vector2 p1 = position + (points[i] * scale); // + Vector2{rand() % 10 - 5, rand() % 10 - 5};
			PhoenixEngine::Vector2 p2 = position + (points[i + 1] * scale); //+ Vector2{ rand() % 10 - 5, rand() % 10 - 5 };

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}