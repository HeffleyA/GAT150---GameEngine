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
	bool onGround = false;

};