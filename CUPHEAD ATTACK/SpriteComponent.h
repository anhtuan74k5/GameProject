#pragma once

#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"


class SpriteComponent : public Component
{
private:
	TransformComponent* transform = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect = {};
	SDL_Rect destRect = {};
	
	bool animated = false;
	int frames = 0;
	int speed = 100;
	int h, w;
	int xyRect;

public:

	

	SpriteComponent() = default;

	SpriteComponent(const char* path, int nFrames, int mSpeed, int height, int width, int RectPos)
	{
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
		h = height;
		w = width;
		xyRect = RectPos;
	}

	
	~SpriteComponent()  
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = w;
		srcRect.h = h;
		destRect.w = destRect.h = xyRect;
	}
	
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};
