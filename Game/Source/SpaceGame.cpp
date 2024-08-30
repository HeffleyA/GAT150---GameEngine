#include "SpaceGame.h"
#include "../Source/Framework/Engine.h"
#include "Components/CharacterComponent.h"

#include <memory>
#include <functional>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);

	std::string sceneNames[] = { "Scenes/game.json", "Scenes/tilemap.json"};

	for (auto sceneName : sceneNames)
	{
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);
	}

	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, SpaceGame::OnAddPoints);

    return true;
}

void SpaceGame::Shutdown()
{
	m_scene->RemoveAll();
}

void SpaceGame::Update(float dt)
{
	timer -= dt;
	mushTimer -= dt;
	gobTimer -= dt;
	skeleTimer -= dt;

	if (timer <= 0)
	{
		auto enemy = Factory::Instance().Create<Actor>("Eye");
		enemy->transform.position = { random(100, 500), random(100, 500)};

		m_scene->AddActor(std::move(enemy), true);

		timer = randomf(3, 10);
	}

	if (mushTimer <= 0)
	{
		mushSpawn -= dt;

		if (mushSpawn <= 0)
		{
			auto enemy = Factory::Instance().Create<Actor>("Mushroom");
			enemy->transform.position = { random(100, 500), random(100, 500) };

			m_scene->AddActor(std::move(enemy), true);

			mushSpawn = randomf(5, 10);
		}
	}

	if (gobTimer <= 0)
	{
		gobSpawn -= dt;

		if (gobSpawn <= 0)
		{
			auto enemy = Factory::Instance().Create<Actor>("Goblin");
			enemy->transform.position = { random(100, 500), random(100, 500) };

			m_scene->AddActor(std::move(enemy), true);

			gobSpawn = randomf(5, 10);
		}
	}

	if (skeleTimer <= 0)
	{
		skeleSpawn -= dt;

		if (skeleSpawn <= 0)
		{
			auto enemy = Factory::Instance().Create<Actor>("Skeleton");
			enemy->transform.position = { random(100, 500), random(100, 500) };

			m_scene->AddActor(std::move(enemy), true);

			skeleSpawn = randomf(5, 10);
		}
	}

	m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	std::cout << "game player dead\n";
}

void SpaceGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
