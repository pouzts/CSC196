#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <vector>

PhoenixEngine::Vector2 position{400, 300};
std::vector<PhoenixEngine::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
PhoenixEngine::Color color{ 1, 1, 0 };
PhoenixEngine::Shape shape{ points, color };
const float speed = 10;
float timer = 0;

PhoenixEngine::ParticleSystem particleSystem;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	timer += dt;
	
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);
		PhoenixEngine::Vector2 psPosition;
		psPosition.x = static_cast<float>(x);
		psPosition.y = static_cast<float>(y);
		
		std::vector<PhoenixEngine::Color> colors = { PhoenixEngine::Color{1,1,1}, PhoenixEngine::Color{1, 0, 0}, PhoenixEngine::Color{0, 0, 1} };
		particleSystem.Create(psPosition, 150, 3, colors[rand() % colors.size()], 150);
	}
	
	particleSystem.Update(dt);


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
	particleSystem.Draw(graphics);
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();

	particleSystem.Shutdown();
}
