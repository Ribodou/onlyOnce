# include "Player.h"



Player::Player(SDL_Renderer *_pRenderer, std::tuple<int, int, int, int> casePosAndStartPos) {
    this->pRenderer = _pRenderer;
    this->nb_move = 0;
    this->n_animation = 0;
    this->nb_move_max = 3;
    std::tie(this->case_i, this->case_j, this->x ,this->y) = casePosAndStartPos;

    for (int i = 1; i <= 10; i++) {
        std::string filename = "./ressources/sprites/joueur/joueur_";
        std::string strnsprite = std::to_string(i);
        if (i < 10) {
            strnsprite = "0" + strnsprite;
        }
        filename += strnsprite + ".bmp";
        SDL_Surface* sprite = SDL_LoadBMP(filename.c_str());
        verify<SDL_Surface>(sprite);
        this->sprites.push_back(sprite);
        SDL_Texture* texture =  SDL_CreateTextureFromSurface(this->pRenderer, sprite);
        verify<SDL_Texture>(texture);
        this->textures.push_back(texture);
    }
}


Player::~Player() {
    // dete all the textures and the sprites
    for (uint i = 0; i < this->sprites.size(); i++) {
        SDL_DestroyTexture(this->textures[i]);
        this->sprites.erase(this->sprites.begin() + i);
        SDL_FreeSurface(this->sprites[i]);
        this->textures.erase(this->textures.begin() + i);
    }
}



void Player::draw(std::tuple<int, int> offset_in_pixel) {
    int offset_x, offset_y;
    std::tie(offset_x, offset_y) = offset_in_pixel;
    SDL_Rect dest = {
        this->x + offset_x,
        this->y + offset_y,
        this->sprites[n_animation]->w,
        this->sprites[n_animation]->h,
    };
    SDL_RenderCopy(this->pRenderer, this->textures[n_animation], NULL, &dest);
    this->n_animation++;
    this->n_animation = n_animation % (this->sprites.size() - 1 );
}


void Player::move(int player_input) {
    if (player_input == 0) {
        this->x -= 10;
        this->nb_move = 1;
        this->direction = player_input;
    } else if (player_input == 1) {
        this-> x += 10;
        this->nb_move = 1;
        this->direction = player_input;
    } else if (player_input == 2) {
        this->y -= 10;
        this->nb_move = 1;
        this->direction = player_input;
    } else if (player_input == 3) {
        this->y += 10;
        this->nb_move = 1;
        this->direction = player_input;
    }
}


bool Player::canMove() const {
    return this->nb_move == 0;
}


void Player::continueMoving() {
    if (this->direction == 0) {
        this->x -= 10;
    } else if (this->direction == 1) {
        this-> x += 10;
    } else if (this->direction == 2) {
        this->y -= 10;
    } else if (this->direction == 3) {
        this->y += 10;
    }
    this->nb_move++;
    if (this->nb_move == this->nb_move_max) {
        this->nb_move = 0;
    }
}


void Player::changeCase() {
    if (this->direction == 0) {
        this->case_j -= 1;
    } else if (this->direction == 1) {
        this->case_j += 1;
    } else if (this->direction == 2) {
        this->case_i -= 1;
    } else if (this->direction == 3) {
        this->case_i += 1;
    }
}


int Player::getNbMove() {
    return this->nb_move;
}


std::tuple<int, int> Player::getPosition() const {
    return std::make_tuple(this->x, this->y);
}


std::tuple<int, int> Player::getCaseIndex() const {
    return std::make_tuple(this->case_i, this->case_j);
}
