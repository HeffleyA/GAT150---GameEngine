#pragma once
#include "../Resources/Resource.h"
#include <string>
#include <SDL_ttf.h>

class Font : public Resource
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontSize);

	// Inherited via Resource
	bool Create(std::string name, ...) override;

	friend class Text;

private:
	_TTF_Font* m_ttfFont{ nullptr };

};