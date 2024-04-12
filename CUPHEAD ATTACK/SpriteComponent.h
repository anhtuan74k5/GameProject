#pragma once

#include "SDL.h"
#include "Components.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect = {}; // Initialize srcRect with empty braces
	SDL_Rect destRect = {}; // Initialize destRect with empty braces
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) : srcRect{}, destRect{} // Initialize srcRect and destRect with empty braces
	{
		setTex(path);
		texture = nullptr; // Initialize position with nullptr
	}

	void setTex (const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 150;
		destRect.w = destRect.h = 75;
	}

	void update() override
	{
		destRect.x = (int) transform->position.x;
		destRect.y = (int) transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

