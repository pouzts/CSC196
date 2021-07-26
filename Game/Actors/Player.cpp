#include "Player.h"
#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Engine.h"
#include "Enemy.h"
#include <memory>

void Player::Update(float dt)
{
	Actor::Update(dt);
	
	float thrust = 0;
	
	// Movement
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::right, transform.rotation) * thrust * dt;
	transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);

	// Fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;

		std::shared_ptr<PhoenixEngine::Shape> bulletShape = std::make_shared<PhoenixEngine::Shape>();
		bulletShape->Load("bulletshape.txt");

		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, scene->engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("bulletshape.txt"), 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));

		scene->engine->Get<PhoenixEngine::AudioSystem>()->PlayAudio("playerFire");
	}
	
	scene->engine->Get<PhoenixEngine::ParticleSystem>()->Create(transform.position, 3, 2, PhoenixEngine::Color::white, 50);

	transform.Update();
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
	{
		//destroy = true;
		scene->engine->Get<PhoenixEngine::ParticleSystem>()->Create(transform.position, 200, 2, PhoenixEngine::Color::white, 50);
		scene->engine->Get<PhoenixEngine::AudioSystem>()->PlayAudio("explosion");

		PhoenixEngine::Event event;
		event.name = "PlayerDead";
		event.data = std::string("YOU ARE DEAD");
		scene->engine->Get<PhoenixEngine::EventSystem>()->Notify(event);
	}
}

