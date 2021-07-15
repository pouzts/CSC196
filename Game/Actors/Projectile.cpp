#include "Projectile.h"
#include "Math/MathUtils.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);
	
	transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);
}