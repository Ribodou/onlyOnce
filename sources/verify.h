#ifndef VERIFY_H
#define VERIFY_H


template <typename T>
void verify(T* t)
{
    if (not(t))
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }
}

#endif