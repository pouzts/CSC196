#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <vector>

PhoenixEngine::Vector2 position{400, 300};
std::vector<PhoenixEngine::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
PhoenixEngine::Color color{ 1, 1, 0 };
PhoenixEngine::Shape shape{ points, color };

const float speed = 10;
float timer = 0;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	timer += dt;
	/*int x, y;
	Core::Input::GetMousePos(x, y);
	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);*/

	PhoenixEngine::Vector2 input;
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) input.x = -1;
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) input.y = 1;
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) input.y = -1;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) input.x = 1;

	position += input * speed;
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	shape.Draw(graphics, position);
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << i << " % 3 = " << i % 3 << std::endl;
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
