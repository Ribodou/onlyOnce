#include "Text.hpp"

#include <SDL2/SDL.h>

Text::Text(
    SDL_Renderer *_pRenderer,
    SDL_Point _point_haut_gauche,
    int _largeur_pixel,
    int _height_pixel)
    :
    pRenderer(_pRenderer),
    point_haut_gauche(_point_haut_gauche),
    largeur_pixel(_largeur_pixel),
    height_pixel(_height_pixel),
    value("xxxxxx") {

    this->font = TTF_OpenFont("fonts/VeraMono.ttf", 20);
    if (this->font == NULL) {
        std::cout << "Could not find font file" << std::endl;
    }

}

Text::~Text() {

    TTF_CloseFont(this->font);

}

void Text::draw(int taille_pixel_bords) {
    std::cout << "on me dessine" << std::endl;
    std::string text_number = this->value;
    if (text_number.length() == 0) {
        std::cout << "Missing text content" << std::endl;
    }
    SDL_Color textColor = { 127, 127, 127, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(
        this->font,
        text_number.c_str(),
        textColor);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_Rect rect_score = {
        this->point_haut_gauche.x + this->largeur_pixel - text_width - 2,
        this->point_haut_gauche.y + this->height_pixel - text_height - 2,
        text_width,
        text_height};
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        this->pRenderer,
        textSurface);
    SDL_FreeSurface(textSurface);


    SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    int x, y, xfin, yfin;
    for (int i = 0; i < taille_pixel_bords; i++) {
        x = this->point_haut_gauche.x - i - 1;
        y = this->point_haut_gauche.y - i - 1;
        xfin = x - i + this->largeur_pixel + i + 1;
        yfin = y - i + this->height_pixel + i + 1;
        SDL_RenderDrawLine(pRenderer, x, y, xfin, y);
        SDL_RenderDrawLine(pRenderer, xfin, y, xfin, yfin);
        SDL_RenderDrawLine(pRenderer, xfin, yfin, x, yfin);
        SDL_RenderDrawLine(pRenderer, x, yfin, x, y);
    }
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderCopy(this->pRenderer, textTexture, NULL, &rect_score);
    SDL_DestroyTexture(textTexture);
}


void Text::set(std::string s) {
    std::cout << "on m'affecte " << s << std::endl;
    this->value = s;
}
