#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

#include <iostream>
#include <vector>
#include <string>

std::vector<PhoenixEngine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };
PhoenixEngine::Transform transform{ PhoenixEngine::Vector2{400, 300}, 0, 3 };

const float speed = 250;
float timer = 0;

PhoenixEngine::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

PhoenixEngine::Engine engine;
PhoenixEngine::Scene scene;

bool Update(float dt)
{
	deltaTime = dt;
	gameTime += deltaTime;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	timer += dt;
	
	int x, y;
	Core::Input::GetMousePos(x, y);
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);
	
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		std::vector<PhoenixEngine::Color> colors = {PhoenixEngine::Color::white, PhoenixEngine::Color::red, PhoenixEngine::Color::blue };
		engine.Get<PhoenixEngine::ParticleSystem>()->Create(psPosition, 150, 3, colors[PhoenixEngine::RandomRangeInt(0, colors.size())], 150);
		engine.Get<PhoenixEngine::AudioSystem>()->PlayAudio("explosion");
	}

	PhoenixEngine::Vector2 input;

	//engine.Get<PhoenixEngine::ParticleSystem>()->Create(transform.position, 3, 2, PhoenixEngine::Color::white, 50);
	
	scene.GetActor<Player>()->shape->color = PhoenixEngine::Color{ PhoenixEngine::RandomRange(0.0f, 1.0f), PhoenixEngine::RandomRange(0.0f, 1.0f), PhoenixEngine::RandomRange(0.0f, 1.0f) };
	scene.GetActor<Enemy>()->shape->color = PhoenixEngine::Color{ PhoenixEngine::RandomRange(0.0f, 1.0f), PhoenixEngine::RandomRange(0.0f, 1.0f), PhoenixEngine::RandomRange(0.0f, 1.0f) };

	engine.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	float scale = 2 + std::sin(timer) * 10;
	scene.Draw(graphics);
	engine.Get<PhoenixEngine::ParticleSystem>()->Draw(graphics);

	PhoenixEngine::Color color = PhoenixEngine::Lerp(PhoenixEngine::Color::green, PhoenixEngine::Color::blue, psPosition.x / 800);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());
	graphics.DrawString(10, 40, std::to_string(scene.GetActor<Player>()->transform.position.x).c_str());
	graphics.DrawString(10, 50, std::to_string(scene.GetActor<Player>()->transform.position.y).c_str());
	graphics.DrawString(10, 60, std::to_string(scene.GetActors<Projectile>().size()).c_str());
}

void Init()
{
	std::shared_ptr<PhoenixEngine::Shape> shape = std::make_shared<PhoenixEngine::Shape>();
	shape->Load("playershape.txt");

	//std::shared_ptr<PhoenixEngine::Shape> playerShape = std::make_shared<PhoenixEngine::Shape>(points, PhoenixEngine::Color::yellow);
	std::shared_ptr<PhoenixEngine::Shape> enemyShape = std::make_shared<PhoenixEngine::Shape>(points, PhoenixEngine::Color::blue);

	engine.Get<PhoenixEngine::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	scene.AddActor(std::make_unique<Player>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{400, 300}, 0, 3 }, shape, speed));
	
	for (size_t i = 0; i < 10; i++)
	{
		scene.AddActor(std::make_unique<Enemy>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{PhoenixEngine::RandomRange(0.0f, 800.0f), PhoenixEngine::RandomRange(0.0f, 600.0f)}, PhoenixEngine::RandomRange(0.0f, PhoenixEngine::TwoPi), 3 }, enemyShape, speed));
	}
}

int main()
{
	srand(123);
	std::cout << RAND_MAX << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		int r = rand();
		std::cout << r  << " " << r / static_cast<float>(RAND_MAX) << std::endl;
	}
	PhoenixEngine::Random();

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	engine.Startup();

	Init();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}
