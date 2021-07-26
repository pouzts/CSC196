#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	if (scene->GetActor<Player>())
	{
		PhoenixEngine::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		PhoenixEngine::Vector2 forward = PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::right, transform.rotation);

		float turnAngle = PhoenixEngine::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);
		//transform.rotation = PhoenixEngine::Lerp(transform.rotation, transform.rotation + turnAngle, 2 * dt);

		float angle = PhoenixEngine::Vector2::Angle(forward, direction.Normalized());
		
		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= PhoenixEngine::DegToRad(10))
		{
			fireTimer = fireRate;

			std::shared_ptr<PhoenixEngine::Shape> bulletShape = std::make_shared<PhoenixEngine::Shape>();
			bulletShape->Load("bulletshape.txt");

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, scene->engine->Get<PhoenixEngine::ResourceSystem>()->Get<PhoenixEngine::Shape>("bulletshape.txt"), 600.0f);
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));

			scene->engine->Get<PhoenixEngine::AudioSystem>()->PlayAudio("enemyFire");
		}
	
		transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::right, transform.rotation) * speed * dt;
		transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
		transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);

		transform.Update();
	}
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;
		destroy = true;
		scene->engine->Get<PhoenixEngine::ParticleSystem>()->Create(transform.position, 200, 3, PhoenixEngine::Color::white, 250);
		scene->engine->Get<PhoenixEngine::AudioSystem>()->PlayAudio("explosion");

		PhoenixEngine::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<PhoenixEngine::EventSystem>()->Notify(event);
	}
}
