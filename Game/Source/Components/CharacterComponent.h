#pragma once
#include "../Source/Components/Component.h"

class CharacterComponent : public Component
{
public:
	CLASS_DECLARATION(CharacterComponent)
	CLASS_PROTOTYPE(CharacterComponent)


	// Inherited via Component
	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);

public:
	float speed{ 0 };
	int groundCount{ 0 };
	bool isAttacking = false;
	bool isHit = false;
	float attackTimer = 1.0f;
	int health = 1000;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };

};