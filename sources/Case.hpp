#ifndef __CASE_H__
#define __CASE_H__

#include <vector>
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"
#include "Text.hpp"


class Case {
    protected:
        SDL_Renderer *pRenderer;
        std::string color;
        static int number_cases;
        static std::vector<struct sprite> sprites;
        SDL_Surface* sprite;
        SDL_Texture* texture;
        bool used;
        void loadCase();
        struct sprite createSprite(std::string color, std::string path);
        void innerDraw(int x, int y);

    public:
        /* Create a Case with the color n° _color */
        Case(SDL_Renderer *_pRenderer, std::string _color);
        /* Destroy the Case and free everything inside it */
        virtual ~Case();

        void deleteTextureAndSprite();
        /* Return the state of the Case */
        std::string getColor();
        /* Draw the Case on the pRender inside it */
        virtual void draw(int x, int y);
        /* walk on the Case */
        void use();
        /* true if the Case has been used and cant't be used anymore */
        bool isBroken();
};

class XCase : public Case {
    private:
        Text text;
    public:
        XCase(SDL_Renderer *_pRenderer, std::string _color);
        void draw(int x, int y);
        void setCount(int count);
};
#endif

