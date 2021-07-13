#include "Player.h"
#include "Math/MathUtils.h"

void Player::Update(float dt)
{
	Actor::Update(dt);
	
	float thrust = 0;

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) thrust = speed;

	transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);
}
