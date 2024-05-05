#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <SDL.h>
#include <SDL_image.h> // Th�m th? vi?n SDL_image

class Additional {
public:
    static bool isGamePaused;

    static void pauseGame(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            isGamePaused = !isGamePaused;
        }
    }

    static void renderHeart(SDL_Renderer* renderer, int numHearts) {
        int heartWidth = 50; // Chi?u r?ng c?a tr�i tim
        int heartHeight = 40; // Chi?u cao c?a tr�i tim
        int offsetX = 10; // Kho?ng c�ch gi?a c�c tr�i tim
        int offsetY = 10; // Kho?ng c�ch t? tr�n xu?ng d??i
        int startY = 0; // V? tr� b?t ??u v? tr�i tim

        // V? numHearts tr�i tim
        for (int i = 0; i < numHearts; ++i) {
            SDL_Surface* heartSurface = IMG_Load("assets/heart.png"); // T?i h�nh ?nh tr�i tim
            if (!heartSurface) {
                std::cerr << "Failed to load heart image: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_Texture* heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface); // T?o texture t? surface
            if (!heartTexture) {
                std::cerr << "Failed to create heart texture: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(heartSurface); // Gi?i ph�ng b? nh? c?a surface
                return;
            }

            SDL_Rect heartRect; // T?o h�nh ch? nh?t cho tr�i tim
            heartRect.x = 1000 - (i + 1) * (heartWidth + offsetX); // C�i ??t v? tr� x ?? n?m ? g�c tr�n ph?i c?a m�n h�nh
            heartRect.y = startY + offsetY * i;
            heartRect.w = heartWidth;
            heartRect.h = heartHeight;

            SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect); // V? tr�i tim l�n m�n h�nh
            SDL_DestroyTexture(heartTexture); // Gi?i ph�ng b? nh? c?a texture
            SDL_FreeSurface(heartSurface); // Gi?i ph�ng b? nh? c?a surface
        }
    }
};

bool Additional::isGamePaused = false;

#endif // ADDITIONAL_H
