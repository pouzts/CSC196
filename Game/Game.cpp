#include "Game.h"
#include "Base/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"
#include "Framework/ResourceSystem.h"

void Game::Initialize()
{
	engine = std::make_unique<PhoenixEngine::Engine>(); // new Engine
	engine->Startup();
	scene = std::make_unique<PhoenixEngine::Scene>(); // new Scene
	scene->engine = engine.get();

	engine->Get<PhoenixEngine::AudioSystem>()->AddAudio("playerFire", "player_fire.wav");
	engine->Get<PhoenixEngine::AudioSystem>()->AddAudio("enemyFire", "enemy_fire.wav");

	engine->Get<PhoenixEngine::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<PhoenixEngine::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<PhoenixEngine::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));

	stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	//(this->*stateFunction)(dt);

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 5;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateLevelStart(dt);
		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0)
		{
			state = eState::GameOver;
		}
		break;
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}
	
	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		DrawTitle(graphics);
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(PhoenixEngine::Color::white);
		graphics.DrawString(350, 400, "Game Over");
		break;
	default:
		break;
	}

	graphics.SetColor(PhoenixEngine::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::DrawTitle(Core::Graphics& graphics)
{
	scene->AddActor(std::make_unique<PhoenixEngine::Actor>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{ 150, 300 }, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logov.txt")));
	scene->AddActor(std::make_unique<PhoenixEngine::Actor>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{ 250, 300 }, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logoe.txt")));
	scene->AddActor(std::make_unique<PhoenixEngine::Actor>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{ 350, 300 }, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logor.txt")));
	scene->AddActor(std::make_unique<PhoenixEngine::Actor>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{ 450, 300 }, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logot.txt")));
	scene->AddActor(std::make_unique<PhoenixEngine::Actor>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{ 550, 300 }, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logoe.txt")));
	scene->AddActor(std::make_unique<PhoenixEngine::Actor>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{ 650, 300 }, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logox.txt")));

	graphics.SetColor(PhoenixEngine::Color::white);
	graphics.DrawString(325, 400, "Press SPACE to continue");
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE)) {
		state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt)
{
	scene->RemoveAllActors();
	std::shared_ptr<PhoenixEngine::Shape> playerShape = std::make_shared<PhoenixEngine::Shape>();
	playerShape->Load("playershape.txt");
	std::shared_ptr<PhoenixEngine::Shape> enemyShape = std::make_shared<PhoenixEngine::Shape>();
	enemyShape->Load("enemyshape.txt");

	scene->AddActor(std::make_unique<Player>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{400, 300}, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("playershape.txt"), 300.0f));

	for (size_t i = 0; i < 3; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{PhoenixEngine::RandomRange(0.0f, 800.0f), PhoenixEngine::RandomRange(0.0f, 600.0f)}, PhoenixEngine::RandomRange(0.0f, PhoenixEngine::TwoPi), 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("enemyshape.txt"), 300.0f));
	}
	state = eState::Game;
}

void Game::OnAddPoints(const PhoenixEngine::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const PhoenixEngine::Event& event)
{
	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
	state = eState::GameOver;
}
