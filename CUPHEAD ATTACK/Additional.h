#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Game.h"

class Additional {
public:

    static bool isGamePaused;

    static void pauseGame(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            isGamePaused = !isGamePaused;
        }
    }

    static void renderPauseMenu(SDL_Renderer* renderer) {
        if (isGamePaused) {
            SDL_Surface* pauseSurface = IMG_Load("assets/pause.png");
            if (!pauseSurface) {
                std::cerr << "Failed to load pause image: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
            if (!pauseTexture) {
                std::cerr << "Failed to create pause texture: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(pauseSurface);
                return;
            }

            SDL_Rect pauseRect;
            pauseRect.x = 0;
            pauseRect.y = 0;
            pauseRect.w = 1000;
            pauseRect.h = 600;

            SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
            SDL_DestroyTexture(pauseTexture);
            SDL_FreeSurface(pauseSurface);
        }
    }



    static void renderStartMenu(SDL_Renderer* renderer) {
        SDL_Surface* startSurface = IMG_Load("assets/start.png");
        if (!startSurface) {
            std::cerr << "Failed to load start image: " << SDL_GetError() << std::endl;
            return;
        }

        SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
        if (!startTexture) {
            std::cerr << "Failed to create start texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(startSurface);
            return;
        }

        SDL_Rect startRect;
        startRect.x = 0;
        startRect.y = 0;
        startRect.w = startSurface->w;
        startRect.h = startSurface->h;

        SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
        SDL_DestroyTexture(startTexture);
        SDL_FreeSurface(startSurface);
    }



    static void renderHeart(SDL_Renderer* renderer, int numHearts) {
        int heartWidth = 50;
        int heartHeight = 40;
        int offsetX = 10;
        int offsetY = 10;
        int startY = 0;

        for (int i = 0; i < numHearts; ++i) {
            SDL_Surface* heartSurface = IMG_Load("assets/heart.png");
            if (!heartSurface) {
                std::cerr << "Failed to load heart image: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_Texture* heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
            if (!heartTexture) {
                std::cerr << "Failed to create heart texture: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(heartSurface);
                return;
            }

            SDL_Rect heartRect;
            heartRect.x = 1000 - (i + 1) * (heartWidth + offsetX);
            heartRect.y = startY + offsetY * i;
            heartRect.w = heartWidth;
            heartRect.h = heartHeight;

            SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect);
            SDL_DestroyTexture(heartTexture);
            SDL_FreeSurface(heartSurface);
        }
    }



    static void renderScore(SDL_Renderer* renderer, int score, int xpos, int ypos, int size, std::string str) {
        TTF_Font* font = TTF_OpenFont("assets/STENCIL.TTF", size);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Color textColor = { 255, 255, 255 };

        std::string scoreText =  std::to_string(score);

        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, (str + ": " + scoreText).c_str(), textColor);


        if (!scoreSurface) {
            std::cerr << "Failed to create score surface: " << TTF_GetError() << std::endl;
            TTF_CloseFont(font);
            return;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        if (!scoreTexture) {
            std::cerr << "Failed to create score texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(scoreSurface); 
            TTF_CloseFont(font);
            return;
        }

        SDL_Rect scoreRect; 
        scoreRect.x = xpos; 
        scoreRect.y = ypos; 
        scoreRect.w = scoreSurface->w; 
        scoreRect.h = scoreSurface->h;


        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        SDL_DestroyTexture(scoreTexture);
        SDL_FreeSurface(scoreSurface);
        TTF_CloseFont(font);

    }

};
bool Additional::isGamePaused = false;


#endif // ADDITIONAL_H
