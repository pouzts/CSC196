#include "Game.h"
#include "Base/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Astroid.h"
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
	engine->Get<PhoenixEngine::AudioSystem>()->AddAudio("hurt", "hurt.wav");

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

	switch (state)
	{
	case Game::eState::Title:
		UpdateTitle(dt);
		break;
	case Game::eState::StartGame:
		score = 0;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateLevelStart(dt);
		break;
	case Game::eState::Game:
		health = scene->GetActor<Player>()->GetHealth();
		if (scene->GetActors<Astroid>().size() == 0 && scene->GetActors<Enemy>().size() == 0)
		{
			state = eState::EndLevel;
			stateTimer = 0;
			level++;
		}
		break;
	case Game::eState::EndLevel:
		if (stateTimer >= 5)
		{
			state = eState::StartLevel;
			scene->RemoveAllActors();
		}
		break;
	case Game::eState::GameOver:
		if (stateTimer >= 5)
		{
			scene->RemoveAllActors();
			state = eState::Title;
		}
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
	case Game::eState::EndLevel:
	{
		std::string levelname = "Level " + std::to_string(level);
		graphics.SetColor(PhoenixEngine::Color::white);
		graphics.DrawString(350, 400, levelname.c_str());
	}
		break;
	case Game::eState::GameOver:
		graphics.SetColor(PhoenixEngine::Color::white);
		graphics.DrawString(350, 400, "Game Over");
		break;
	default:
		break;
	}

	graphics.SetColor(PhoenixEngine::Color::blue);
	graphics.DrawString(30, 20, "SCORE: ");
	graphics.SetColor(PhoenixEngine::Color::white);
	graphics.DrawString(80, 20, std::to_string(score).c_str());
	graphics.SetColor(PhoenixEngine::Color::red);
	graphics.DrawString(720, 20, "HEALTH: ");
	graphics.SetColor(PhoenixEngine::Color::white);
	graphics.DrawString(770, 20, std::to_string(health).c_str());

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::DrawTitle(Core::Graphics& graphics)
{
	graphics.SetColor(PhoenixEngine::Color(PhoenixEngine::Random(), PhoenixEngine::Random(), PhoenixEngine::Random()));
	engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logov.txt")->Draw(graphics, PhoenixEngine::Vector2{ 150, 300 }, 0, 3);
	engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logoe.txt")->Draw(graphics, PhoenixEngine::Vector2{ 250, 300 }, 0, 3);
	engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logor.txt")->Draw(graphics, PhoenixEngine::Vector2{ 350, 300 }, 0, 3);
	engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logot.txt")->Draw(graphics, PhoenixEngine::Vector2{ 450, 300 }, 0, 3);
	engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logoe.txt")->Draw(graphics, PhoenixEngine::Vector2{ 550, 300 }, 0, 3);
	engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("logox.txt")->Draw(graphics, PhoenixEngine::Vector2{ 650, 300 }, 0, 3);

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
	scene->AddActor(std::make_unique<Player>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{400, 300}, 0, 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("playershape.txt"), 300.0f));

	for (size_t i = 0; i < level; i++)
	{
		bool hasSpawned = false;
		while (!hasSpawned) {
			float spawnX = PhoenixEngine::RandomRange(0.0f, 800.0f);
			float spawnY = PhoenixEngine::RandomRange(0.0f, 600.0f);
			if ((spawnX < 300.0f || spawnX > 500.0f) && (spawnY < 200.0f || spawnY > 400.0f)) 
			{
				scene->AddActor(std::make_unique<Enemy>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{spawnX, spawnY}, PhoenixEngine::RandomRange(0.0f, PhoenixEngine::TwoPi), 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("enemyshape.txt"), 150.0f));
				hasSpawned = true;
			}
		}
	}

	for (size_t i = 0; i < 2 + level; i++)
	{
		bool hasSpawned = false;
		while (!hasSpawned) {
			float spawnX = PhoenixEngine::RandomRange(0.0f, 800.0f);
			float spawnY = PhoenixEngine::RandomRange(0.0f, 600.0f);
			if ((spawnX < 300.0f || spawnX > 500.0f) && (spawnY < 200.0f || spawnY > 400.0f))
			{
				scene->AddActor(std::make_unique<Astroid>(PhoenixEngine::Transform{ PhoenixEngine::Vector2{spawnX, spawnY}, PhoenixEngine::RandomRange(0.0f, PhoenixEngine::TwoPi), 3 }, engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("astroidshape.txt"), 150.0f));
				hasSpawned = true;
			}
		}
	}

	state = eState::Game;
}

void Game::OnAddPoints(const PhoenixEngine::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const PhoenixEngine::Event& event)
{
	std::cout << std::get<std::string>(event.data) << std::endl;
	stateTimer = 0;
	state = eState::GameOver;
}
