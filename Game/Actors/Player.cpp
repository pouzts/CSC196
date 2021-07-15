#include "Player.h"
#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Engine.h"
#include <memory>

void Player::Update(float dt)
{
	Actor::Update(dt);
	
	float thrust = 0;
	
	// Movement
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) thrust = speed;

	transform.position += PhoenixEngine::Vector2::Rotate(PhoenixEngine::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = PhoenixEngine::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = PhoenixEngine::Wrap(transform.position.y, 0.0f, 600.0f);

	// Fire
	if (Core::Input::IsPressed(VK_SPACE))
	{
		std::vector<PhoenixEngine::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };
		std::shared_ptr<PhoenixEngine::Shape> enemyShape = std::make_shared<PhoenixEngine::Shape>(points, PhoenixEngine::Color::red);
		scene->AddActor(std::make_unique<Projectile>(transform, enemyShape, 600.0f));
	}
}
