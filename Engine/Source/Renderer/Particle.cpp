#include "Particle.h"

void Particle::Initialize(const Data& data)
{
	isActive = true;
	position = data.position;
	velocity = data.velocity;
	lifespan = data.lifespan;
}

void Particle::Update(float dt)
{
	if (lifespan != 0.0f) lifespan -= dt;
	isActive = (lifespan > 0);
	position = position + (velocity * dt);
}

void Particle::Draw(Renderer& renderer)
{
	renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
}
