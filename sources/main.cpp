#include <iostream>
#include <SDL2/SDL.h>
#include "Level.hpp"
#include "verify.h"
#include <tuple>
#include "Player.h"



inline bool exists (int n_level) {
    std::string strnlevel = std::to_string(n_level);
    if (n_level < 10) {
        strnlevel = "0" + strnlevel;
    }
    std::string filename = "./ressources/levels/level_" + strnlevel + ".txt";
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}


bool setup(int width, int height, SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {
    int game_over = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    pWindow = SDL_CreateWindow("Ma première application SDL2",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width,
                            height,
                            SDL_WINDOW_SHOWN
                            );
    verify<SDL_Window>(pWindow);

    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    verify<SDL_Renderer>(pRenderer);
    return game_over;
}


void draw(SDL_Renderer *&pRenderer, const Level &level, Player &player) {
    SDL_SetRenderDrawColor(pRenderer, 0, 50, 0, 255);
    SDL_RenderClear(pRenderer);
    level.draw();
    player.draw(level.getOffsetInPixel());
    SDL_RenderPresent(pRenderer);  // Affichage
}


int input(SDL_Event event) {
    int retour = -2;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            retour = -1;
        } else if (event.type == SDL_KEYDOWN) {
            switch( event.key.keysym.sym ) {
                case SDLK_LEFT:
                    retour = 0;
                    break;
                case  SDLK_RIGHT:
                    retour = 1;
                    break;
                case SDLK_UP:
                    retour = 2;
                    break;
                case SDLK_DOWN:
                    retour = 3;
                    break;
                default:
                    retour = -2;
                    break;
            }
        }
    }

    return retour;
}


int logic(int player_input, Level &level, Player &player) {
    if (player.canMove()) {  // the player is waiting
        if (level.canPlayerMove(player, player_input)) {
            player.move(player_input);
        }
    } else {  // the player is already moving toward a case
        player.continueMoving();
        if (player.getNbMove() == 0) { // the player just finished moving
            player.changeCase();
            if (level.isCaseUsed(player.getCaseIndex())) {
                return -1;  // game over
            }
            level.walkOnCase(player.getCaseIndex());
        }
    }
    bool player_has_win = level.isGameFinished(player);
    if (player_has_win) {
        return 1; // end of the game
    }
    std::cout << level.getCasesLeftToBreak() << std::endl;
    return 0; // let the game continue
}


void endGame(SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {
    SDL_DestroyRenderer(pRenderer);  // Libération de la mémoire du SDL_Renderer
    SDL_DestroyWindow(pWindow);  // Close and destroy the window
    SDL_Quit();  // Quit the SDL2
}


/*
-2 => quit the game immediatly
-1 => game over, retry the level
0 => continue
1 => next level
*/
int main() {
    int hauteur_fenetre = 480;
    int largeur_fenetre = 700;
    int n_level = 1;
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;
    SDL_Event event;
    int player_input;
    int game_over = setup(largeur_fenetre, hauteur_fenetre, pWindow, pRenderer);
    bool stop = false;

    while(exists(n_level) && !stop) {
        Level level(pRenderer, n_level, 0, 45);
        Player player(pRenderer, level.getStartCasePositionandPixelPosition());
        while (game_over == 0) {  // while the player has not walk on the last case
            draw(pRenderer, level, player);
            player_input = input(event);
            if (player_input == -1) {
                game_over = -2;
            } else {
                game_over = logic(player_input, level, player);
            }
            SDL_Delay(70);
        }
        if (game_over == -2) {
            stop = true;
        } else if (game_over == -1) {
            // do nothing
        } else if (game_over == 0) {
            // do nothing
        } else if (game_over == 1) {
            n_level++;
        } else {
            std::cout << "the 'game_over' variable is too high:" << n_level << "." << std::endl;
        }
        draw(pRenderer, level, player);
        SDL_Delay(70);
        game_over = false;
    }
    endGame(pWindow, pRenderer);
    return EXIT_SUCCESS;
}