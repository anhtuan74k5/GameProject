#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <SDL.h>
#include <SDL_image.h> // Thêm th? vi?n SDL_image

class Additional {
public:
    static bool isGamePaused;

    static void pauseGame(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            isGamePaused = !isGamePaused;
        }
    }

    static void renderHeart(SDL_Renderer* renderer, int numHearts) {
        int heartWidth = 50; // Chi?u r?ng c?a trái tim
        int heartHeight = 40; // Chi?u cao c?a trái tim
        int offsetX = 10; // Kho?ng cách gi?a các trái tim
        int offsetY = 10; // Kho?ng cách t? trên xu?ng d??i
        int startY = 0; // V? trí b?t ??u v? trái tim

        // V? numHearts trái tim
        for (int i = 0; i < numHearts; ++i) {
            SDL_Surface* heartSurface = IMG_Load("assets/heart.png"); // T?i hình ?nh trái tim
            if (!heartSurface) {
                std::cerr << "Failed to load heart image: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_Texture* heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface); // T?o texture t? surface
            if (!heartTexture) {
                std::cerr << "Failed to create heart texture: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(heartSurface); // Gi?i phóng b? nh? c?a surface
                return;
            }

            SDL_Rect heartRect; // T?o hình ch? nh?t cho trái tim
            heartRect.x = 1000 - (i + 1) * (heartWidth + offsetX); // Cài ??t v? trí x ?? n?m ? góc trên ph?i c?a màn hình
            heartRect.y = startY + offsetY * i;
            heartRect.w = heartWidth;
            heartRect.h = heartHeight;

            SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect); // V? trái tim lên màn hình
            SDL_DestroyTexture(heartTexture); // Gi?i phóng b? nh? c?a texture
            SDL_FreeSurface(heartSurface); // Gi?i phóng b? nh? c?a surface
        }
    }
};

bool Additional::isGamePaused = false;

#endif // ADDITIONAL_H
