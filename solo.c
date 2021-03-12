/*
solo.c
Camille KEDY
------
Les fonctions appelées dans le main.cpp sont ici en plus des fonctions d'affichage, de chronometrage, de lecture et d'écriture des fichiers

*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//#include "fgifsdl.h"
#include "solo.h"
//#include "constantes.h"

#define HAUTEUR_TUILES_SERIE 226
#define LARGEUR_TUILES_SERIE 350
//#define TAILLE_TABLEAU 50
#define TAILLE_TABLEAU 200
#define TAILLE_POLICE_QUESTION_REPONSE 30
#define LARGEUR_RECT_REPONSE 565
#define TEMPS_REPONSE 10

/*Boucle infinie qui servira generalement a mettre le code en pause et a quitter le programme
  en cas de relachement de la touche ESCAPE ou de clic sur le bouton Fermer de la barre de titre*/
void pause()
{
    int continuer=1;
    SDL_Event event;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer=0;
                break;
            }
            break;
        }
    }
}

/*void chrono(SDL_Surface *ecran,SDL_Color couleur,TTF_Font *police,int t)
{
    //int tempsActuel=0, tempsPrecedent=0, compteur=0;
    SDL_Surface *texte=NULL;
    char temps[2]="";

    //Initialisation Temps et texte
    //tempsActuel=SDL_GetTicks();
    //sprintf(temps,"%d",t);
    //texte=TTF_RenderText_Solid(police,temps,couleur);
    while(t!=0)
    {
        sprintf(temps,"%d",t);
        t--;
        SDL_FreeSurface(texte);
        texte=TTF_RenderText_Solid(police,temps,couleur);
        SDL_BlitSurface(texte, NULL, ecran, NULL);
        SDL_Flip(ecran);
        Sleep(1000);
    }
    SDL_FreeSurface(texte);
}*/

/*Gere les evenements de clic dans tous les menus du jeu
  M1=1----Menu 1 (SOLO-MULTI-QUITTER)
  M2=1----Menu 2 (A-SES-C-D-TI-Retour)*/
int eventmenu(int M1,int M2,int M3)
{
    int continuer=1;
    SDL_Event event;
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            return 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                return 0;
                break;
             }
        case SDL_MOUSEBUTTONUP:
            if(M1==1 && M2==0 && M3==0){
                if(event.button.button==SDL_BUTTON_LEFT && event.button.x<=890 && event.button.x>=390 && event.button.y<=640 && event.button.y>=590)
                {
                    return 0;
                }
                if(event.button.button==SDL_BUTTON_LEFT && event.button.x<=890 && event.button.x>=390 && event.button.y<=500 && event.button.y>=450)
                {
                    return 1;
                }
                /*if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=890&&event.button.x>=390&&event.button.y<=570&&event.button.y>=520)
                {
                    return 2;
                }*/
            }
            else{
                if(M1==1&&M2==1&&M3==0){
                    if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=50+LARGEUR_TUILES_SERIE&&event.button.x>=50&&event.button.y<=168+HAUTEUR_TUILES_SERIE&&event.button.y>=168)
                    {
                        return 1;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=50+2*LARGEUR_TUILES_SERIE+65&&event.button.x>=50+LARGEUR_TUILES_SERIE+65&&event.button.y<=168+HAUTEUR_TUILES_SERIE&&event.button.y>=50)
                    {
                        return 2;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=50+3*LARGEUR_TUILES_SERIE+2*65&&event.button.x>=50+2*LARGEUR_TUILES_SERIE+2*65&&event.button.y<=168+HAUTEUR_TUILES_SERIE&&event.button.y>=50)
                    {
                        return 3;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=50+LARGEUR_TUILES_SERIE&&event.button.x>=50&&event.button.y<=168+2*HAUTEUR_TUILES_SERIE+40&&event.button.y>=168+HAUTEUR_TUILES_SERIE+40)
                    {
                        return 4;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=50+2*LARGEUR_TUILES_SERIE+65&&event.button.x>=50+LARGEUR_TUILES_SERIE+65&&event.button.y<=168+2*HAUTEUR_TUILES_SERIE+40&&event.button.y>=168+HAUTEUR_TUILES_SERIE+40)
                    {
                        return 5;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT&&event.button.x<=50+3*LARGEUR_TUILES_SERIE+2*65&&event.button.x>=50+2*LARGEUR_TUILES_SERIE+2*65&&event.button.y<=168+2*HAUTEUR_TUILES_SERIE+40&&event.button.y>=168+HAUTEUR_TUILES_SERIE+40)
                    {
                        return 0;
                    }
                }
            }
            break;
        }
    }
}

/*Pour le decompte du temps qui s'affichera au coin haut gauche de l'ecran
  Le parametre t designe le temps du compte a rebours*/
void chronometre(SDL_Surface *ecran,SDL_Surface *fond,SDL_Color couleur,TTF_Font *police,int t,SDL_Rect position)
{
    int tempsActuel=0, tempsPrecedent=0;
    SDL_Surface *texte=NULL;
    char temps[10];

    tempsActuel = SDL_GetTicks();/*Recuperation du temps courant*/
    sprintf(temps, "%d", t);
    texte = TTF_RenderText_Solid(police, temps, couleur);
        while(t>-0.5)
        {
            tempsActuel=SDL_GetTicks();
            if (tempsActuel - tempsPrecedent >= 1000)
            
                sprintf(temps, "%d", t);
                SDL_FreeSurface(texte);
                texte = TTF_RenderText_Solid(police, temps, couleur);
                tempsPrecedent = tempsActuel;
                SDL_BlitSurface(fond, NULL, ecran, NULL);
                SDL_BlitSurface(texte, NULL, ecran, &position);

                SDL_Flip(ecran);
                t--;
            }
        }
    SDL_FreeSurface(texte);
}


/*version plus complete du chrono, prise en compte les evenements de clic*/
int chronoevent(SDL_Surface *ecran,SDL_Surface *fond,SDL_Color couleur,TTF_Font *police,int t,SDL_Rect position)
{
    SDL_Event event;
    int tempsActuel=0, tempsPrecedent=0, nbreclic=0, tuileclic;
    SDL_Surface *texte=NULL, *cadre=NULL;
    SDL_Rect positCadre, positSurfChrono;
    positSurfChrono.x=(1280/2)-(600/2);positSurfChrono.y=430;

    char temps[10];

    cadre=IMG_Load("cadre.png");
    tempsActuel = SDL_GetTicks();
    sprintf(temps, "%d", t);
    texte = TTF_RenderText_Solid(police, temps, couleur);


        while(t>=0)
        {
            SDL_PollEvent(&event);//Permet de mettre le programme en pause sans toutefois l'arreter
            switch(event.type)
            {
            case SDL_MOUSEBUTTONUP:
                if(nbreclic==0){//On limite le nombre de clic a 1
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.x<=50+LARGEUR_RECT_REPONSE && event.button.x>=50 && event.button.y<=370+TAILLE_POLICE_QUESTION_REPONSE+25 && event.button.y>=370)
                    {
                        positCadre.x=30;positCadre.y=365;
                        SDL_BlitSurface(cadre,NULL,ecran,&positCadre);
                        nbreclic++;
                        tuileclic=1;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.x<=2*50+2*LARGEUR_RECT_REPONSE && event.button.x>=2*50+LARGEUR_RECT_REPONSE && event.button.y<=370+TAILLE_POLICE_QUESTION_REPONSE+25 && event.button.y>=370)
                    {
                        positCadre.x=2*50+LARGEUR_RECT_REPONSE-20;positCadre.y=365;
                        SDL_BlitSurface(cadre,NULL,ecran,&positCadre);
                        nbreclic++;
                        tuileclic=2;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.x<=50+LARGEUR_RECT_REPONSE && event.button.x>=50 && event.button.y<=370+(25+TAILLE_POLICE_QUESTION_REPONSE)*2+185 && event.button.y>=370+TAILLE_POLICE_QUESTION_REPONSE+25+185)
                    {
                        positCadre.x=30;positCadre.y=580;
                        SDL_BlitSurface(cadre,NULL,ecran,&positCadre);
                        nbreclic++;
                        tuileclic=3;
                    }
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.x<=2*50+2*LARGEUR_RECT_REPONSE && event.button.x>=2*50+LARGEUR_RECT_REPONSE && event.button.y<=370+(25+TAILLE_POLICE_QUESTION_REPONSE)*2+185 && event.button.y>=370+TAILLE_POLICE_QUESTION_REPONSE+185)
                    {
                        positCadre.x=2*50+LARGEUR_RECT_REPONSE-20;positCadre.y=580;
                        SDL_BlitSurface(cadre,NULL,ecran,&positCadre);
                        nbreclic++;
                        tuileclic=4;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    return -1;
                break;
            }
            tempsActuel=SDL_GetTicks();
            if (tempsActuel - tempsPrecedent >= 1000)
            
                sprintf(temps, "%d", t);
                SDL_FreeSurface(texte);
                texte = TTF_RenderText_Solid(police, temps, couleur);
                tempsPrecedent = tempsActuel;
                SDL_BlitSurface(fond, NULL, ecran, &positSurfChrono);
                SDL_BlitSurface(texte, NULL, ecran, &position);

                SDL_Flip(ecran);
                t--;
            }
        }
        if(nbreclic!=0)
            return (tuileclic);
        else
            return 0;
}

/*Premier Menu du jeu 
  Blittage des differentes tuiles qui serviront de bouton pour naviguer vers l'écran de choix des séries*/
void menu(SDL_Surface *ecran,SDL_Surface *fond)
{
    int i;

    SDL_Surface *image1=NULL,*image2=NULL,*image3=NULL;
    SDL_Rect positionFond,positionImage,positionImage2,positionImage3;

    positionFond.x=0;positionFond.y=0;//ATTENTION REDONDANCE SI RECOPIE DANS LE MAIN
    fond=SDL_LoadBMP("fondstart.bmp");
    for(i=0;i<256;i+=3){//Apparition
        SDL_SetAlpha(fond,SDL_SRCALPHA,i);
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_Flip(ecran);
    }
    image1=SDL_LoadBMP("tuilestart1.bmp");image2=SDL_LoadBMP("tuilestart2.bmp");image3=SDL_LoadBMP("quitter.bmp");
    positionImage.x=390;positionImage.y=450;
    for(i=0;i<256;i++){//apparition  tuile solo
        SDL_SetAlpha(image1,SDL_SRCALPHA,i);
        SDL_BlitSurface(image1, NULL, ecran, &positionImage);
        SDL_Flip(ecran);
    }
    positionImage2.x=390;positionImage2.y=450;
    for(i=0;i<71;i++){//Apparition tuile multi
        positionImage2.y++;
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_BlitSurface(image2, NULL, ecran, &positionImage2);
        SDL_BlitSurface(image1, NULL, ecran, &positionImage);
        SDL_Flip(ecran);
    }

    positionImage3.x=390;positionImage3.y=450+i;
    for(i=0;i<71;i++){//tuile Quitter
        positionImage3.y++;
        SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_BlitSurface(image1, NULL, ecran, &positionImage);
        SDL_BlitSurface(image2, NULL, ecran, &positionImage2);
        SDL_BlitSurface(image3, NULL, ecran, &positionImage3);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(fond);SDL_FreeSurface(image1);SDL_FreeSurface(image2);SDL_FreeSurface(image3);
}

/*Affiche menu du choix des series*/
void menuserie(SDL_Surface *ecran,SDL_Surface *fond)
{
    int i;
    SDL_Surface *image1=NULL,*image2=NULL,*image3=NULL,*image4=NULL,*image5=NULL,*image6=NULL;
    SDL_Rect positionFond,positionImage1,positionImage2,positionImage3,positionImage4,positionImage5,positionImage6;

    positionImage1.x=50;positionImage1.y=168;
    positionImage2.x=50+LARGEUR_TUILES_SERIE+65;positionImage2.y=168;
    positionImage3.x=50+2*LARGEUR_TUILES_SERIE+2*65;positionImage3.y=168;
    positionImage4.x=50;positionImage4.y=168+HAUTEUR_TUILES_SERIE+40;
    positionImage5.x=50+LARGEUR_TUILES_SERIE+65;positionImage5.y=168+HAUTEUR_TUILES_SERIE+40;
    positionImage6.x=50+2*LARGEUR_TUILES_SERIE+2*65;positionImage6.y=168+HAUTEUR_TUILES_SERIE+40;

    positionFond.x=0;positionFond.y=0;
    fond=SDL_LoadBMP("fondserie.bmp");image1=SDL_LoadBMP("A.bmp");image2=SDL_LoadBMP("C.bmp");image3=SDL_LoadBMP("D.bmp");
    image4=SDL_LoadBMP("SES.bmp");image5=SDL_LoadBMP("TI.bmp");image6=SDL_LoadBMP("RETOUR.bmp");
    for(i=0;i<251;i+=15){//Apparition
        SDL_SetAlpha(fond,SDL_SRCALPHA,i);SDL_BlitSurface(fond, NULL, ecran, &positionFond);
        SDL_SetAlpha(image1,SDL_SRCALPHA,i);SDL_BlitSurface(image1, NULL, ecran, &positionImage1);
        SDL_SetAlpha(image2,SDL_SRCALPHA,i);SDL_BlitSurface(image2, NULL, ecran, &positionImage2);
        SDL_SetAlpha(image3,SDL_SRCALPHA,i);SDL_BlitSurface(image3, NULL, ecran, &positionImage3);
        SDL_SetAlpha(image4,SDL_SRCALPHA,i);SDL_BlitSurface(image4, NULL, ecran, &positionImage4);
        SDL_SetAlpha(image5,SDL_SRCALPHA,i);SDL_BlitSurface(image5, NULL, ecran, &positionImage5);
        SDL_SetAlpha(image6,SDL_SRCALPHA,i);SDL_BlitSurface(image6, NULL, ecran, &positionImage6);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(fond),SDL_FreeSurface(image1),SDL_FreeSurface(image2),SDL_FreeSurface(image3),SDL_FreeSurface(image4),SDL_FreeSurface(image5),SDL_FreeSurface(image6);
}

/*void fondquestion(SDL_Surface *ecran,SDL_Surface fond,SDL_Gif gif,int temps)
{
    while(temps>0){
        fond=SDLGifAutoFrame(gif);
        SDL_BlitSurface(fond,NULL,ecran,NULL);
        SDL_Flip(ecran);
        Sleep(1000);
        temps--;
    }
}*/

/* Affichage des réponses correctes après réponse aux différentes questions*/
void AfficheRep(SDL_Surface *ecran, TTF_Font *police, int Serie, FILE** f)
{
    int i;
    char tab[TAILLE_TABLEAU], chaine[TAILLE_TABLEAU];
    SDL_Surface *fondRep=NULL, *txt;
    SDL_Color Blanche = {255, 255, 255};
    SDL_Rect lieu;

    lieu.x=300; lieu.y=(720-TAILLE_POLICE_QUESTION_REPONSE)/2;
    if(fgets(chaine,TAILLE_TABLEAU,*f)!=NULL)
    {
        fondRep=IMG_Load("fondreponse.jpg");
        for(i=0;i<251;i+=15){//Apparition
            SDL_SetAlpha(fondRep,SDL_SRCALPHA,i);
            SDL_BlitSurface(fondRep, NULL, ecran, NULL);
            SDL_Flip(ecran);
        }
        sprintf(tab,chaine);        /*Conversion en chaine de caracteres*/
        txt=TTF_RenderText_Blended(police,tab,Blanche);
        for(i=0;i<251;i+=15){//Apparition
            SDL_SetAlpha(txt,SDL_SRCALPHA,i);
            SDL_BlitSurface(txt, NULL, ecran, &lieu);
            SDL_Flip(ecran);
        }
        //SDL_BlitSurface(txt,NULL,ecran,&lieu);
        pause();
        SDL_FreeSurface(fondRep);
    }
    else exit(EXIT_FAILURE);
}

void questions(SDL_Surface *ecran,SDL_Surface *fond, int Serie)
{
    int i=0,j=0,k=0,choix=0,question=0,XY[10]={160,140,70,380,710,380,70,595,710,595};
    SDL_Surface *txt=NULL,*surface=NULL,*surfaceRep=NULL, *surfChrono=NULL;

    FILE *fichier=NULL,*fichierRep=NULL, *fichierSolution=NULL;
    char chaine[TAILLE_TABLEAU],tab[TAILLE_TABLEAU];
    SDL_Rect lieu,positSurface,positSurfRep,positChrono;

    lieu.x=XY[0];lieu.y=XY[1];
    positSurface.x=0;positSurface.y=100;
    //positSurfRep.x=50;positSurfRep.y=490;
    positSurfRep.x=50;positSurfRep.y=370;
    positChrono.x=(1280/2)-45;positChrono.y=435;

    SDL_Color Blanche = {255, 255, 255};
    TTF_Font *police,*police1;
    police=TTF_OpenFont("fonts/georgia.ttf",TAILLE_POLICE_QUESTION_REPONSE);
    police1=TTF_OpenFont("fonts/georgia.ttf",90);//police du chrono

    switch(Serie)
    {
    case 1:
        fichierSolution=fopen("reponses_vraies/reponses_vraiesA.txt","r");
        fichierRep=fopen("reponses_candidats/reponses_candidatsA.txt","w");
        fichier=fopen("questionsA.txt","r");
        break;
    case 2:
        fichierSolution=fopen("reponses_vraies/reponses_vraiesC.txt","r");
        fichierRep=fopen("reponses_candidats/reponses_candidatsC.txt","w");
        fichier=fopen("questionsC.txt","r");
        break;
    case 3:
        fichierSolution=fopen("reponses_vraies/reponses_vraiesD.txt","r");
        fichierRep=fopen("reponses_candidats/reponses_candidatsD.txt","w");
        fichier=fopen("questionsD.txt","r");
        break;
    case 4:
        fichierSolution=fopen("reponses_vraies/reponses_vraiesSES.txt","r");
        fichierRep=fopen("reponses_candidats/reponses_candidatsSES.txt","w");
        fichier=fopen("questionsSES.txt","r");
        break;
    case 5:
        fichierSolution=fopen("reponses_vraies/reponses_vraiesTI.txt","r");
        fichierRep=fopen("reponses_candidats/reponses_candidatsTI.txt","w");
        fichier=fopen("questionsTI.txt","r");
        break;
    }
        //fichierRep=fopen("reponses_candidats/reponses_candidatsD.txt","w");
        //fichier=fopen("questionsD.txt","r");
        if(fichier==NULL || fichierSolution==NULL)
            exit(EXIT_FAILURE);//printf("PROBLEME OUVERTURE FICHIER");
        else
        {
        while(question!=6)/*Le nombre de question prevues par fichier est de 6. Tant que ce nombre de questions n'est pas
                                                   atteint on continue de lire le fichier*/
        {
            //for(k=0;k<255;k+=15)
            //{
                //SDL_SetAlpha(fond,SDL_SRCALPHA,k);
                SDL_BlitSurface(fond,NULL,ecran,NULL);
                //SDL_Flip(ecran);
            //}

            //surface=SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 330, 32, 0, 0, 0, 0);/*Creation Surface Questions*/
            //SDL_FillRect(surface,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
            //SDL_SetAlpha(surface,SDL_SRCALPHA,128);
            //SDL_BlitSurface(surface,NULL,ecran,&positSurface);

            /*surfaceRep correspnd a la surface ou on va "ecrire" les reponses*/
            surfaceRep=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_RECT_REPONSE, TAILLE_POLICE_QUESTION_REPONSE+25, 32, 0, 0, 0, 0);
            SDL_FillRect(surfaceRep,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
            SDL_SetAlpha(surfaceRep,NULL,NULL);

            //surfChrono=SDL_CreateRGBSurface(SDL_HWSURFACE, 125, 125, 32, 0, 0, 0, 0);//Surface du chronometre
            surfChrono=SDL_LoadBMP("image.bmp");
            //SDL_FillRect(surfChrono,NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
            //SDL_SetAlpha(surfChrono,SDL_SRCALPHA,128);
            for(k=0;k<4;k++)
            {
                SDL_BlitSurface(surfaceRep,NULL,ecran,&positSurfRep);//Il y'a 4 reponses donc on blitte 4 Surfaces
                positSurfRep.x=positSurfRep.x+LARGEUR_RECT_REPONSE+50;
                if(k==1)
                {
                    positSurfRep.x=50;positSurfRep.y=positSurfRep.y+TAILLE_POLICE_QUESTION_REPONSE+185;
                }
                if(k==2)
                    positSurfRep.x=50+LARGEUR_RECT_REPONSE+50;
            }
            SDL_Flip(ecran);

            while(fgets(chaine,TAILLE_TABLEAU,fichier)!=NULL)
            {
                sprintf(tab,chaine);        //Conversion en chaine de caracteres
                txt=TTF_RenderText_Blended(police,tab,Blanche);
                SDL_BlitSurface(txt,NULL,ecran,&lieu);
                SDL_Flip(ecran);
                j+=2;
                lieu.x=XY[0+j];lieu.y=XY[1+j];
                i++;
                if(i==5)
                    break;
            }
            choix=chronoevent(ecran,surfChrono,Blanche,police1,TEMPS_REPONSE,positChrono);
            AfficheRep(ecran, police1, Serie, &fichierSolution);
            //Sleep(3000);
            question++;
            i=0;j=0;k=0;positSurfRep.x=50;;positSurfRep.y=370;lieu.x=XY[0];lieu.y=XY[1];//Reinitialisation
            switch(choix)
            {
            case -1:
                question=6;
                break;
            case 1:
                fputc('A',fichierRep);
                break;
            case 2:
                fputc('B',fichierRep);
                break;
            case 3:
                fputc('C',fichierRep);
                break;
            case 4:
                fputc('D',fichierRep);
                break;
            default:
                fputc(' ',fichierRep);
                break;
            }
        }
        //pause();
                //exit(0);
        }
        fclose(fichier);fclose(fichierRep);
}

/*void transition()
{
    int i;
    SDL_Surface *image1=NULL,*image2=NULL,*image3=NULL,*image4=NULL,*image5=NULL,*image6=NULL;
    //SDL_Rect positionFond,positionImage1,positionImage2,positionImage3,positionImage4,positionImage5,positionImage6;

    for(i=255;i>0;i-=15){//Apparition
        SDL_SetAlpha(fond,SDL_SRCALPHA,i);
        SDL_BlitSurface(fond, NULL, ecran, NULL);
        SDL_Flip(ecran);
    }
}*/


