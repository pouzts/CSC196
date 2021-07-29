#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState 
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		EndLevel,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void DrawTitle(Core::Graphics& graphics);
	
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	
	void OnAddPoints(const PhoenixEngine::Event& event);
	void OnPlayerDead(const PhoenixEngine::Event& event);

public:
	std::unique_ptr<PhoenixEngine::Engine> engine;
	std::unique_ptr<PhoenixEngine::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game::* stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t health = 0;
	size_t level = 1;
};

