#pragma once
#include "../Source/Components/Component.h"
#include "Math/Random.h"

class EnemyComponent : public Component
{
public:
	CLASS_DECLARATION(EnemyComponent)
	CLASS_PROTOTYPE(EnemyComponent)


		// Inherited via Component
	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);

public:
	float speed{ 0 };
	int groundCount{ 0 };
	float flipTimer{ randomf(3, 5) };
	float flipTimerR{ randomf(3, 5) };

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };

};