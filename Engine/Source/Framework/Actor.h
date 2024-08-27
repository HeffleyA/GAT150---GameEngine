#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>

class Renderer;
class Scene;

class Actor : public Object
{
public:
	Actor() = default;
	Actor(const Transform& transform) : transform{ transform } {}
	Actor(const Actor& other);

	CLASS_DECLARATION(Actor)
	CLASS_PROTOTYPE(Actor)

	// Inherited via Object
	void Initialize() override;

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	std::function<void(Actor*)> OnCollisionEnter;
	std::function<void(Actor*)> OnCollisionExit;

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();
	template<typename T>
	std::vector<T*> GetComponents();
	
	//void SetDamping(float damping) { m_damping = damping; }

	//const Transform& GetTransform() { return transform; }
	//void setTransform(const Transform& transform) { transform = transform; }

	//void SetTag(const std::string tag) { tag = tag; }
	//const std::string& GetTag() { return tag; }

	//virtual void OnCollision(Actor* actor) {}

	friend class Scene;

public:
	std::string tag;
	float lifespan = 0;
	bool destroyed = false;
	Transform transform;
	Scene* scene{ nullptr };

protected:

	//Vector2 m_velocity{ 0, 0 };
	//float m_damping = 0;

	std::vector<std::unique_ptr<Component>> components;
};

template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents()
{
	std::vector<T*> results;

	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) results.push_back(result);
	}

	return results;
}
