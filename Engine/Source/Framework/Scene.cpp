#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Components/CollisionComponent.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}


void Scene::Update(float dt)
{
	for (auto& actor : actors)
	{
		if (actor->active)
		{
			actor->Update(dt);
		}
	}

	// collision
	for (auto& actor1 : actors)
	{
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		if (!collision1) continue;

		for (auto& actor2 : actors)
		{
			if (actor1 == actor2) continue;

			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if (!collision2) continue;

			if (collision1->CheckCollision(collision2))
			{
				if (actor1->OnCollisionEnter) actor1->OnCollisionEnter(actor2.get());
				if (actor2->OnCollisionEnter) actor2->OnCollisionEnter(actor1.get());
			}
		}
	}

	// destroy
	std::erase_if(actors, [](auto& actor) { return actor->destroyed; });

	//auto iter = m_actors.begin();
	//while (iter != m_actors.end())
	//{
	//	iter = ((*iter)->m_destroyed) ? m_actors.erase(iter) : ++iter;
	//}

	//m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](Actor* actor) { return actor->m_destroyed; }), m_actors.end());
	//std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });
	
	// collision

	//for (auto& actor1 : m_actors)
	//{
	//	for (auto& actor2 : m_actors)
	//	{
	//		if (actor1 == actor2 || (actor1->m_destroyed || actor2->m_destroyed)) continue;

	//		Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
	//		float distance = direction.Length();
	//		//float radius = actor1->GetRadius() + actor2->GetRadius();

	//		/*if (distance <= radius)
	//		{
	//			actor1->OnCollision(actor2.get());
	//			actor2->OnCollision(actor1.get());
	//		}*/
	//	}
	//}
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{
		if (actor->active) 
		{
			actor->Draw(renderer);
		}
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	actors.clear();
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{

}
