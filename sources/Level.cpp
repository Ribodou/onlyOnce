#include "Level.hpp"
#include "Case.hpp"

Level::Level(SDL_Renderer *_pRenderer, int _nlevel, int x, int y) : pRenderer(_pRenderer), nlevel(_nlevel) {
    this->start_x = 0;
    this->start_y = 0;
    this->casesLeftToBreak = 0;
    this->offset_in_pixel[0] = x;
    this->offset_in_pixel[1] = y;
    std::string strnlevel = std::to_string(this->nlevel);
    if (this->nlevel < 10) {
        strnlevel = "0" + strnlevel;
    }
    this->height = 0;
    this->width = 0;
    std::string filename = "./ressources/levels/level_" + strnlevel + ".txt";
    std::ifstream file(filename);
    std::string line;
    int nColumn = 0;
    while (std::getline(file, line)) {
        std::vector<Case*> temp;
        int tmpNColumn = 0;
        for(char& c : line) {
            if (c == 'X') {
                this->xcase = new XCase(this->pRenderer, "noir");
                temp.push_back(this->xcase);
            } else if (c == 'D') {
                temp.push_back(new Case(this->pRenderer, "depart"));
            } else if (c == 'G') {
                temp.push_back(new Case(this->pRenderer, "glace"));
                this->casesLeftToBreak++;
            } else if (c == 'A') {
                temp.push_back(new Case(this->pRenderer, "arrivee"));
            } else if (c == 'B') {
                temp.push_back(new Case(this->pRenderer, "blocage"));
            } else { // \n
                temp.push_back(new Case(this->pRenderer, "blanc"));
            }
            // std::cout << c << " ";
            tmpNColumn += 1;
        }
        if (nColumn == 0) {
            nColumn = tmpNColumn;
        } else if (nColumn > 0) {
            if (!(nColumn == tmpNColumn)) {
                nColumn = -1;
            }
        }
        if (nColumn == -1) {
            std::cout << "Les lignes du niveau ./ressources/levels/level_";
            std::cout << strnlevel;
            std::cout << ".txt n'ont pas le même nombre de lignes.";
            std::cout << std::endl;
            exit(-1);
        }
        this->cases.push_back(temp);
    }
    this->xcase->setCount(this->casesLeftToBreak);
    this->height = this->cases.size();
    this->width = nColumn;
}


Level::~Level() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->cases[i][j] != NULL) {
                delete this->cases[i][j];
                this->cases[i][j] = NULL;
            }
        }
    }
}


void Level::draw() const {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->cases[i][j] != NULL) {
                std::cout << "dessions une case du niveau" << std::endl;
                this->cases[i][j]->draw(j*30+this->offset_in_pixel[0], i*30+this->offset_in_pixel[1]);
            }
        }
    }
}


std::tuple<int, int, int, int> Level::getStartCasePositionandPixelPosition() const {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->cases[i][j] != NULL) {
                std::string color = this->cases[i][j]->getColor();
                if (color.compare("depart") == 0) {
                    return std::make_tuple(i, j, j*30 + this->start_x, i*30 + this->start_y);
                }
            }
        }
    }
    std::cout << "No start case where found ! Please put a 'D' on the level_*.txt file." << std::endl;
    exit(-1); // pas de depart trouve, on sort du jeu
}


bool Level::canPlayerMove(const Player &player, int player_input) const {
    int i, j;
    std::tie(i, j) = player.getCaseIndex();
    if (player_input == 0) {
        j -= 1;
    } else if (player_input == 1) {
        j += 1;
    } else if (player_input == 2) {
        i -= 1;
    } else if (player_input == 3) {
        i += 1;
    }
    if (this->cases[i][j]->getColor().compare("noir") != 0 &&
        this->cases[i][j]->getColor().compare("blocage") != 0) {
        return true;
    } else {
        return false;
    }
}


bool Level::isGameFinished(const Player &player) {
    int i, j;
    std::tie(i, j) = player.getCaseIndex();
    return this->cases[i][j]->getColor().compare("arrivee") == 0;
}


void Level::walkOnCase(std::tuple<int, int> tuple) {
    int i, j;
    std::tie(i, j) = tuple;
    this->cases[i][j]->use();
    this->casesLeftToBreak--;
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->cases[i][j]->getColor().compare("blocage") == 0) {
                if (this->casesLeftToBreak == 0) {
                    delete this->cases[i][j];
                    this->cases[i][j] = new Case(pRenderer, "blanc");
                } else {
                    this->xcase->setCount(this->casesLeftToBreak);
                }
            }
        }
    }
}


bool Level::isCaseUsed(std::tuple<int, int> tuple) {
    int i, j;
    std::tie(i, j) = tuple;
    return this->cases[i][j]->isBroken();
}


int Level::getCasesLeftToBreak() {
    return this->casesLeftToBreak;
}


std::tuple<int, int> Level::getOffsetInPixel() const {
    return std::make_tuple(this->offset_in_pixel[0], this->offset_in_pixel[1]);
}
