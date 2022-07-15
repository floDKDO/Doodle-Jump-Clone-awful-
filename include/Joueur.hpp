#ifndef __JOUEUR__HPP__
#define __JOUEUR__HPP__


#include "Tuile.hpp"

#include <vector>

class Joueur
{
    public:
        Joueur(SDL_Renderer* rendu, int x, int y, std::string chemin);
        int x, y, w, h;
        SDL_Rect dest;
        SDL_Texture* texture;

        bool gauche = false;
        bool droite = false;

        bool Collision(SDL_Rect dest_joueur, Tuile tile);

        void Draw(SDL_Renderer* rendu, int cameraX, int cameraY);

        void Update(Uint32& timeStep, std::vector<Tuile> tuiles);
        void HandleEvents(SDL_Event* e);

        float vitesseY = 0.0f;
        float acceleration = 1.0f;
        bool surSol;

    protected:

    private:
};

#endif // __JOUEUR__HPP__
