#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"


Map* map;

SDL_Event Game::event;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());
auto& Enemy_Plane1(manager.addEntity());
auto& Enemy_Plane2(manager.addEntity());
auto& Enemy_Pawn1(manager.addEntity());
auto& Enemy_Pawn2(manager.addEntity());