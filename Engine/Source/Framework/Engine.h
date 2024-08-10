#pragma once
// ** core **
#include "../Core/ETime.h"
#include "../Core/EAssert.h"
#include "../Core/EFile.h"
#include "Core/Json.h"
#include "Core/Factory.h"

// ** systems **
// renderer
#include "../Renderer/Renderer.h"
#include "../Renderer/Particle.h"
#include "../Renderer/ParticleSystem.h"
#include "../Renderer/Text.h"
#include "../Renderer/Font.h"
#include "../Renderer/Model.h"
#include "../Renderer/Color.h"
#include "../Renderer/Texture.h"
// input
#include "../Input/Input.h"
// audio
#include "../Audio/Audio.h"

// ** math **
#include "../Math/Vector2.h"
#include "../Math/Random.h"
#include "../Math/MathUtils.h"
#include "../Math/Transform.h"

// ** framework **
#include "../Framework/Actor.h"
#include "../Framework/Game.h"
#include "../Framework/Scene.h"

// ** resources **
#include "../Resources/Resource.h"
#include "../Resources/ResourceManager.h"

// ** components **
#include "Components/TextureComponent.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>
#include <cassert>

#define RENDERER g_engine.GetRenderer()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	Time& GetTime() { return *m_time; }
	ParticleSystem& GetPS() { return *m_particleSystem; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Time> m_time{ nullptr };

	std::unique_ptr<Renderer> m_renderer{ nullptr };
	std::unique_ptr<Input> m_input{ nullptr };
	std::unique_ptr<Audio> m_audio{ nullptr };

	std::unique_ptr<ParticleSystem> m_particleSystem;
};

