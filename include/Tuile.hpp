#ifndef __TUILE__HPP__
#define __TUILE__HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Tuile
{
    public:
        Tuile(SDL_Renderer* rendu, int x, int y, int type);
        Tuile(){}
        int x, y, w, h;
        SDL_Rect dest;
        SDL_Texture* texture;
        bool collision;
        std::string chemin;
        int type;

        void Draw(SDL_Renderer* rendu, int cameraX, int cameraY);

        int tileType;

    protected:

    private:
};

#endif // __TUILE__HPP__
