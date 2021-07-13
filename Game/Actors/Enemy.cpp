#include "Enemy.h"
#include "Math/MathUtils.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);
}