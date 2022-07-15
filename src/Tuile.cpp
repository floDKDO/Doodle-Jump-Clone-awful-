#include "Tuile.hpp"

Tuile::Tuile(SDL_Renderer* rendu, int x, int y, int type)
{
    this->x = x;
    this->y = y;
    w = 128;
    h = 32;
    dest = {x, y, w, h};
    collision = true;
    this->chemin = chemin;
    this->type = type;
}


void Tuile::Draw(SDL_Renderer* rendu, int cameraX, int cameraY)
{
    dest = {x + cameraX, y + cameraY, w, h};
    if(type == 0)
        SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
    else if(type == 1)
        SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
    SDL_RenderFillRect(rendu, &dest);
}
