#pragma once

class Engine;
class Renderer;
class Scene;

class Game
{
public:
	Game() = default;
	Game(Engine* engine) : m_engine{ engine } {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	int GetScore() const { return m_score; }
	void AddPoints(int points) { m_score += points; }

	int GetHealth() const { return m_health; }
	void SetHealth(int health) { m_health = health; }

protected:
	int m_score = 0;
	int m_health = 1000;
	int m_money = 500;

	Engine* m_engine{ nullptr };
};