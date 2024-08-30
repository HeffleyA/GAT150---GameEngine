#pragma once
#include "Framework/Game.h"
#include "Event/EventSystem.h"
#include "Math/Random.h"
#include <memory>

class SpaceGame : public Game, Observer
{
public:
	enum class State
	{
		STARTGAME,
		STARTLEVEL,
		GAME,
		DESTROYED,
		GAMEOVER
	};

	SpaceGame() = default;
	SpaceGame(Engine* engine) : Game{ engine } {}

	// Inherited via Game
	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	// events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);

private:
	std::unique_ptr<class Scene> m_scene;
	State m_state{ State::STARTGAME };

	int m_score = 0;
	int lives = 3;
	int m_money = 500;

	float timer = randomf(3, 10);
	float mushTimer = 30;
	float mushSpawn = randomf(5, 10);
	float gobTimer = 45;
	float gobSpawn = randomf(7, 10);
	float skeleTimer = 60;
	float skeleSpawn = randomf(9, 10);
};