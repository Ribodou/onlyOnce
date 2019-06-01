#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include <tuple>
#include "Case.hpp"
#include <iostream>
#include "verify.h"

class Player {
    private:
        SDL_Renderer *pRenderer;
		std::vector<SDL_Surface*> sprites;
		std::vector<SDL_Texture*> textures;
        int x, y;
        int n_animation;
        int case_i, case_j;
        /* =0 if player is not moving, or x if player is in the xth frame of his move */
        /* direction is the last player_input */
        int nb_move, nb_move_max, direction;
    public:
        Player(SDL_Renderer *_pRenderer, std::tuple<int, int, int, int> startPos);
        ~Player();
        void draw(std::tuple<int, int> offset_in_pixel);
        void move(int player_input);
        bool canMove() const;
        std::tuple<int, int> getPosition() const;
        std::tuple<int, int> getCaseIndex() const;
        void continueMoving();
        void changeCase();
        int getNbMove();
};

#endif