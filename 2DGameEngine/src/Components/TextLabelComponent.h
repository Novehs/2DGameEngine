#pragma once
#include "../Component.h"
#include <SDL_ttf.h>


class TextLabelComponent : public Component
{
private:
	SDL_Rect position;
	std::string text;
	std::string fontFamily;
	SDL_Color colour;
	SDL_Texture* texture;

public:

	TextLabelComponent(std::string text, int x, int y, std::string fontFamily, const SDL_Color& colour);

	void SetLabelText(std::string text, std::string fontFamily);

	void Initalise() override;
	void Update(float deltaTime) override;
	void Render() override;
};

