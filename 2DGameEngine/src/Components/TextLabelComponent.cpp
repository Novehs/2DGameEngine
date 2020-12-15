#include "TextLabelComponent.h"
#include "../AssetManager.h"
#include "../Game.h"
#include "../FontManager.h"
#include <SDL_ttf.h>

TextLabelComponent::TextLabelComponent(std::string text, int x, int y, std::string fontFamily, const SDL_Color& colour)
{
	this->text = text;
	this->position.x = x;
	this->position.y = y;
	this->fontFamily = fontFamily;
	this->colour = colour;

	SetLabelText(text, fontFamily);
}

void TextLabelComponent::SetLabelText(std::string text, std::string fontFamily)
{
	SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), colour);
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
}

void TextLabelComponent::Initalise()
{
}

void TextLabelComponent::Update(float deltaTime)
{
}

void TextLabelComponent::Render()
{
	FontManager::Draw(texture, position);
}
