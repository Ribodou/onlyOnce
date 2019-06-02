#ifndef __TEXT_H__
#define __TEXT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Text {
    protected:
        SDL_Renderer *pRenderer;
        SDL_Point point_haut_gauche;
        TTF_Font* font;
        int largeur_pixel;
        int height_pixel;
        std::string value;
    public:
        Text(
            SDL_Renderer *_pRenderer,
            SDL_Point _point_haut_gauche,
            int _largeur_pixel,
            int _height_pixel);
        ~Text();
        void draw(int taille_pixel_bords);
        void set(std::string x);
};


#endif
