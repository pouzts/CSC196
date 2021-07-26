#include "Projectile.h"
#include "Engine.h"
#include <vector>

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);
	
	transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);
	
	transform.Update();
	/*std::vector<PhoenixEngine::Color> colors = { PhoenixEngine::Color::white, PhoenixEngine::Color::red, PhoenixEngine::Color::blue };
	scene->engine->Get<PhoenixEngine::ParticleSystem>()->Create(transform.position, 150, 3, colors[PhoenixEngine::RandomRangeInt(0, colors.size())], 150);*/
}