#include "Case.hpp"
#include <iostream>
#include "verify.h"


std::vector<struct sprite> Case::sprites;


Case::Case(SDL_Renderer *_pRenderer, std::string _color) {
    this->pRenderer = _pRenderer;
    this->color = _color;
    this->sprite = nullptr;
    this->texture = nullptr;
    this->used = false;
    this->loadCase();
}


Case::~Case() {
    this->deleteTextureAndSprite();
}


void Case::deleteTextureAndSprite() {
    int index = -1;
    for (uint i = 0; i < Case::sprites.size(); i++) {
        if (Case::sprites[i].color.compare(this->color) == 0) {
            index = i;
        }
    }
    // std::cout << "deleting a case " << index << std::endl;
    // std::cout << ", it was used " << Case::sprites[index].used;
    // std::cout << " times." << std::endl;
    Case::sprites[index].used--;
    if (Case::sprites[index].used == 0) {
        SDL_DestroyTexture(Case::sprites[index].texture);
        SDL_FreeSurface(Case::sprites[index].sprite);
        Case::sprites.erase(Case::sprites.begin() + index);
    }
}

struct sprite Case::createSprite(std::string color, std::string path) {
    struct sprite spriteToLoad;
    spriteToLoad.color = color;
    spriteToLoad.used = 0;
    spriteToLoad.sprite = SDL_LoadBMP(path.c_str());
    verify<SDL_Surface>(spriteToLoad.sprite);
    spriteToLoad.texture =  SDL_CreateTextureFromSurface(this->pRenderer, spriteToLoad.sprite);
    verify<SDL_Texture>(spriteToLoad.texture);
    return spriteToLoad;
}



void Case::loadCase() {
    // std::cout << "trying to laod a case" << std::endl;
    int index = -1;
    for (uint i = 0; i < Case::sprites.size(); i++) {
        if (Case::sprites[i].color == this->color) {
            index = i;
        }
    }
    if (index == -1) {  // sprite not found
        // create the path of the sprite
        std::string name = "./ressources/sprites/";
        name += this->color;
        name += ".bmp";
        struct sprite spriteToLoad = this->createSprite(color, name);
        Case::sprites.push_back(spriteToLoad);
        index = Case::sprites.size() - 1;
    }
    Case::sprites[index].used++;//todo pointeur
    this->sprite = Case::sprites[index].sprite;
    this->texture = Case::sprites[index].texture;
}


std::string Case::getColor() {
    return this->color;
}


void Case::innerDraw(int x, int y) {
    SDL_Rect dest = {
        x,
        y,
        this->sprite->w,
        this->sprite->h,
    };
    SDL_RenderCopy(this->pRenderer, this->texture, NULL, &dest);
}


void Case::draw(int x, int y) {
    this->innerDraw(x, y);
}


void Case::use() {
    this->used = true;
    if (this->color.compare("glace") == 0) {
        this->deleteTextureAndSprite();
        this->color += "_brise";

    }
    this->loadCase();
}


bool Case::isBroken() {
    if ((this->used) && (this->getColor().compare("glace_brise") == 0)) {
        return true;
    }
    return false;
}

XCase::XCase(SDL_Renderer *_pRenderer, std::string _color) :
    Case(_pRenderer, _color),
    text(pRenderer, {0, 20}, 200, 80) {
    this->text.set("         ");
}

void XCase::setCount(int count) {
    this->text.set(std::to_string(count));
}

void XCase::draw(int x, int y) {
    this->innerDraw(x, y);
    this->text.draw(1);
}
