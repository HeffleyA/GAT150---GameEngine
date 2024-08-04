#pragma once
#include "../Math/Vector2.h"
#include <string>

class Texture
{
public:
	Texture() = default;
	~Texture();

	bool Load(const std::string& filename, class Renderer& renderer);

	Vector2 GetSize();

	friend class Renderer;

private:
	struct SDL_Texture* m_texture{ nullptr };
};