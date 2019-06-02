#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "Case.hpp"
#include <tuple>
#include "Player.h"

class Level {
    protected:
        SDL_Renderer *pRenderer;
        XCase *xcase;
        int nlevel;
        int width;
        int height;
        int px_case_size;
        int start_x, start_y;
        int casesLeftToBreak;
        int offset_in_pixel[2];

        std::vector<std::vector<Case*> > cases;
    public:
        Level(SDL_Renderer *_pRenderer, int _nlevel, int x, int y);
        ~Level();
        void draw() const;
        std::tuple<int, int, int, int> getStartCasePositionandPixelPosition() const;
        bool canPlayerMove(const Player &player, int user_input) const;
        bool isGameFinished(const Player &player);
        void walkOnCase(std::tuple<int, int> tuple);
        bool isCaseUsed(std::tuple<int, int> tuple);
        int getCasesLeftToBreak();
        std::tuple<int, int> getOffsetInPixel() const;
};


#endif
