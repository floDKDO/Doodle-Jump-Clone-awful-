#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <fstream>

#include "Tuile.hpp"
#include "Joueur.hpp"

#define LONGUEUR_FENETRE 1920
#define HAUTEUR_FENETRE 1080

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    srand (time(NULL));

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() < 0)
    {
        std::cerr << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
    {
        std::cerr << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0)
    {
        std::cerr << Mix_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Window* fenetre = nullptr;
    if((fenetre = SDL_CreateWindow("Mon jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LONGUEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_MAXIMIZED)) == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* rendu = nullptr;
    if((rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    Joueur joueur(rendu, 1920/2 - 64/2, 1080-64 - 64/2, "joueur.png");

    std::vector<Tuile> tuiles;
    for(int i = 0; i < 10000; i++)
    {
        if(rand() % 7 == 0)
            tuiles.push_back(Tuile(rendu, rand() % 1920, 700 - i*200, 0));
        else
            tuiles.push_back(Tuile(rendu, rand() % 1920, 700 - i*200, 1));
    }

    SDL_Texture* image = IMG_LoadTexture(rendu, "fond.png");

    Uint32 timeStep = SDL_GetTicks();

    bool quitter = false;
    while(quitter == false)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_WINDOWEVENT:

                    if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                        quitter = true;
                    break;

                case SDL_KEYDOWN:

                    if(e.key.keysym.sym == SDLK_ESCAPE)
                        quitter = true;

                default :
                    break;
            }
            joueur.HandleEvents(&e);
        }

        int cameraY = -joueur.y + (HAUTEUR_FENETRE / 2);

        joueur.Update(timeStep, tuiles);

        if(SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255) < 0)
        {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        if(SDL_RenderClear(rendu) < 0)
        {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        for(long long unsigned int i = 0; i < tuiles.size(); i++)
            tuiles[i].Draw(rendu, 0, cameraY);

        joueur.Draw(rendu, 0, cameraY);

        SDL_Rect dest = {0, 0, 1920, 1080};

        SDL_RenderCopy(rendu, image, nullptr, &dest);

        SDL_RenderPresent(rendu);
    }
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
