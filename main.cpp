/*
main.c
Camille KEDY et Karim LYLI
------
Menu du jeu. Appelles les fonctions des autres fichiers et affiche les images de presentation
Le menu principal du jeu sera présenté ici. Une fois le mode de jeu (solo, multi) choisi le joueur sera redirigé vers l'écran de choix des filières
5 filières disponibles correcspondant aux filières de l'enseignement secondaire général camerounais:
    A : Littéraire
    SES : Sciences economiques et sociales
    C : Scientifique (option mathematiques et sciences physiques)
    D : Scientifique (option mathematiques et biologie)
    TI : Scientifique (option mathematiques et informatique)
*/


#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "solo.c"
#include "solo.h"
//#include "constantes.h"
//#include "fgifsdl.h"

#define CHRONO 10
#define HAUTEUR_TUILES_SERIE 226
#define LARGEUR_TUILES_SERIE 350



int main ( int argc, char** argv )
{
    TTF_Font *police=NULL;
    int i,n1,n2,M1=0,M2=0,M3=0;
    //SDL_Gif *gif;
    SDL_Surface *ecran=NULL,*fond=NULL,*txt=NULL;
    SDL_Rect positionFond,position;//position du texte
    SDL_Color couleurNoire={0,0,0};//couleur du texte

    TTF_Init();
    police=TTF_OpenFont("fonts/georgia.ttf",105);//Choix de police georgia taille 105

    if(police==NULL){
        fprintf(stderr,"erreur POLICE : %s",TTF_GetError());
        exit(0);
    }


    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

    SDL_WM_SetIcon(SDL_LoadBMP("logo10ansminiature.bmp"),NULL);
    ecran=SDL_SetVideoMode(1280,720,32, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
    fond=SDL_LoadBMP("intro.bmp");
    SDL_WM_SetCaption("QUIZZ JPO PREPAVOGT",NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    positionFond.x=0;positionFond.y=0;
    for(i=0;i<256;i++){//Apparition
        SDL_SetAlpha(fond,SDL_SRCALPHA,i);
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_Flip(ecran);
    }
    /*while(t<3){
        Sleep(1000);
        t++;
    }*/
    for(i=0;i<256;i++){//Disparition
        SDL_SetAlpha(fond,SDL_SRCALPHA,255-i);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(fond);
    Sleep(5000);
    do{
        menu(ecran,fond);//affiche menu
        M1++;            //Verifie si on est entre dans le premier menu à savoir le menu principal 0 si l'on est jamais entré
        n1=eventmenu(M1,M2,M3);
        switch(n1)
        {                                                               
        case 0:
            break;
        case 1:
            M2++;menuserie(ecran,fond);//M2 Verifie si on est entre dans le menu des series 0 si l'on est jamais entré
            n2=eventmenu(M1,M2,M3);
            switch(n2)
            {
            case 0:
                //Sleep(1000);
                break;

            case 1:
                fond=SDL_LoadBMP("background/Hugo.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                }
                position.x=370;position.y=150;
                chronometre(ecran,fond,couleurNoire,police,CHRONO,position);
                SDL_FreeSurface(fond);
                fond=SDL_LoadBMP("background/fondQuestions.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    i+=5;
                }
                questions(ecran,fond,n2);
                pause();
                SDL_FreeSurface(txt);SDL_FreeSurface(fond);
                break;

            case 2:
                fond=SDL_LoadBMP("background/Einstein.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                }
                position.x=370;position.y=150;
                chronometre(ecran,fond,couleurNoire,police,CHRONO,position);
                SDL_FreeSurface(fond);
                fond=SDL_LoadBMP("background/fondQuestions.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    i+=5;
                }
                questions(ecran,fond,n2);
                pause();
                SDL_FreeSurface(txt);SDL_FreeSurface(fond);
                break;

            case 3:
                fond=SDL_LoadBMP("background/Mendel.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                }
                position.x=370;position.y=150;
                chronometre(ecran,fond,couleurNoire,police,CHRONO,position);
                SDL_FreeSurface(fond);
                fond=SDL_LoadBMP("background/fondQuestions.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    i+=5;
                }
                questions(ecran,fond,n2);
                pause();
                SDL_FreeSurface(txt);SDL_FreeSurface(fond);
                break;

            case 4:
                fond=SDL_LoadBMP("background/Keynes.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                }
                position.x=370;position.y=150;
                chronometre(ecran,fond,couleurNoire,police,CHRONO,position);
                SDL_FreeSurface(fond);
                fond=SDL_LoadBMP("background/fondQuestions.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    i+=5;
                }
                questions(ecran,fond,n2);
                pause();
                SDL_FreeSurface(txt);SDL_FreeSurface(fond);
                break;

            case 5:
                fond=SDL_LoadBMP("background/Jobs.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                }
                position.x=370;position.y=150;
                chronometre(ecran,fond,couleurNoire,police,CHRONO,position);
                SDL_FreeSurface(fond);
                fond=SDL_LoadBMP("background/fondQuestions.bmp");
                for(i=0;i<256;i++)
                {
                    SDL_SetAlpha(fond,SDL_SRCALPHA,i);
                    SDL_BlitSurface(fond,NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    i+=5;
                }
                questions(ecran,fond,n2);
                pause();
                SDL_FreeSurface(txt);SDL_FreeSurface(fond
                break;
            }

            M2--;
            break;
        }

        M1--;
    }while(n1!=0);
    //SDL_FreeSurface(fond);
    TTF_CloseFont(police);//fermeture police
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}


