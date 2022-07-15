#include "Joueur.hpp"

Joueur::Joueur(SDL_Renderer* rendu, int x, int y, std::string chemin)
{
    this->x = x;
    this->y = y;
    w = 64;
    h = 64;
    dest = {x, y, w, h};

    if((this->texture = IMG_LoadTexture(rendu, chemin.c_str())) == nullptr)
    {
        std::cerr << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Joueur::Draw(SDL_Renderer* rendu, int cameraX, int cameraY)
{
    dest = {x + cameraX, y + cameraY, w, h};
    //if(y >= offsetCamera + 1080/2 + h || y + h <= offsetCamera + 1080 + 980)
    //{
        if(SDL_RenderCopy(rendu, texture, nullptr, &dest) < 0)
        {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    //}
}

bool Joueur::Collision(SDL_Rect dest_joueur, Tuile tile)
{
    if (dest_joueur.x < tile.x + tile.w          //collision a gauche
    &&  dest_joueur.x + dest_joueur.w  > tile.x  //collision a droite
    &&  dest_joueur.y  < tile.y + tile.h         //collision en haut
    &&  dest_joueur.h + dest_joueur.y  > tile.y  //collision en bas
    &&  tile.collision == true)
    {
        return true;
    }
    else return false;
}


void Joueur::Update(Uint32& timeStep, std::vector<Tuile> tuiles)
{
    static bool surBleu = false;
    static bool surVert = false;
    static bool surDepart = false;

    for(int i = 0; i < tuiles.size(); i++)
    {
        if(Collision({(int)x, (int)y, w, h}, tuiles[i]) == true)
        {
            // collision droite
            if(x + w > tuiles[i].x + tuiles[i].w)
                x = tuiles[i].x + tuiles[i].w;

            // collision gauche
            if(x < tuiles[i].x)
                x = tuiles[i].x - w;
        }
    }

    vitesseY += acceleration;
    y += vitesseY;

    for(int i = 0; i < tuiles.size(); i++)
    {
        if(Collision({(int)x, (int)y, w, h}, tuiles[i]) == true)
        {
            //ces deux lignes pour ameliorer la chute lors d'une collision avec un bloc au dessus du joueur
            vitesseY = 0;
            vitesseY += acceleration;

            // collision haut : on est sur un bloc
            if(y < tuiles[i].y)
            {
                y = tuiles[i].y - h;
                vitesseY = 0;
                surSol = true;
                if(tuiles[i].type == 0)
                {
                    surVert = true;
                    surBleu = false;
                    surDepart = false;
                }
                else if(tuiles[i].type == 1)
                {
                    surBleu = true;
                    surVert = false;
                    surDepart = false;
                }
            }

            // collision bas
            if(y + h > tuiles[i].y + tuiles[i].h)
                y = tuiles[i].y + tuiles[i].h;
        }
    }


    if(y >= 984)
    {
        y = 984;
        vitesseY = 0.0f;
        surSol = true;
        surDepart = true;
        surBleu = false;
        surVert = false;
    }

    if(surSol == true)
    {
        if(surDepart || surBleu)
            vitesseY = -30.0f;
        else if(surVert)
            vitesseY = -50.0f;
        surSol = false;
    }

    if(x < 0-w)
        x = 1920;
    else if(x > 1920)
        x = 0-w;

    if(gauche == true)
        x -= 20;
    else if(droite == true)
        x += 20;
}

void Joueur::HandleEvents(SDL_Event* e)
{
    switch(e->type)
    {
        case SDL_KEYDOWN:

            if(e->key.keysym.sym == SDLK_LEFT)
            {
                gauche = true;
            }
            else if(e->key.keysym.sym == SDLK_RIGHT)
            {
                droite = true;
            }
            break;


        case SDL_KEYUP:

            if(e->key.keysym.sym == SDLK_LEFT || e->key.keysym.sym == SDLK_RIGHT)
            {
                gauche = false;
                droite = false;
            }
            break;

        default:
            break;
    }
}
