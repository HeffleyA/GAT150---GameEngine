#include "EnemyComponent.h"
#include "../Source/Framework/Engine.h"
#include "Components/TextureAnimationComponent.h"
#include "CharacterComponent.h"

FACTORY_REGISTER(EnemyComponent)

void EnemyComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&EnemyComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void EnemyComponent::Update(float dt)
{
	bool onGround = (groundCount > 0);
	Vector2 direction{ 1, 0 };
	flipTimer -= dt;

	if (flipTimer <= 0)
	{
		animation->hflip = true;

		flipTimer = randomf(3, 5);
	}

	flipTimerR -= dt;

	if (flipTimerR <= 0)
	{
		animation->hflip = false;

		flipTimerR = randomf(3, 5);
	}

	if (animation->hflip && direction.x == 1)
	{
		direction = { -1, 0 };
	}
	else if (!animation->hflip && direction.x == -1)
	{
		direction = { 1, 0 };
	}

	float modifier = (onGround) ? 1 : 0.2f;
	physics->ApplyForce(direction * speed * 5 * modifier);

	if (physics->velocity.x < -0.1f) animation->hflip = true;
	else if (physics->velocity.x > 0.1f) animation->hflip = false;
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "Ground") groundCount++;

	if (actor->name == "player")
	{
		CharacterComponent* playerAtt = actor->GetComponent<CharacterComponent>();

		if (playerAtt->isAttacking)
		{
			owner->destroyed = true;
		}
	}
}

void EnemyComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "Ground") groundCount--;
}

void EnemyComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
}