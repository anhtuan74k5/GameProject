#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"


Map* map;
Manager manager;
SDL_Event Game::event;

SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.addEntity());
auto& Enemy_Plane1(manager.addEntity());
auto& Enemy_Plane2(manager.addEntity());
auto& Enemy_Pawn1(manager.addEntity());
auto& Enemy_Pawn2(manager.addEntity());
auto& Bullet(manager.addEntity());
auto& EnemyBullet1(manager.addEntity());
auto& EnemyBullet2(manager.addEntity());
