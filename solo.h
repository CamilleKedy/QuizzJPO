/*
solo.h
Camille KEDY et Karim LYLI
------
Prototype des fonctions
*/

void pause();
int eventmenu(int M1,int M2,int M3);
void chronometre(SDL_Surface *ecran,SDL_Surface *fond,SDL_Color couleur,TTF_Font *police,int t,SDL_Rect position);
int chronoevent(SDL_Surface *ecran,SDL_Surface *fond,SDL_Color couleur,TTF_Font *police,int t,SDL_Rect position);
void menu(SDL_Surface *ecran,SDL_Surface *fond);
void menuserie(SDL_Surface *ecran,SDL_Surface *fond);
void questionsTI(SDL_Surface *ecran,SDL_Surface *fond);
void questionsSES(SDL_Surface *ecran,SDL_Surface *fond);
void questionsD(SDL_Surface *ecran,SDL_Surface *fond);
void questionsC(SDL_Surface *ecran,SDL_Surface *fond);
void questionsA(SDL_Surface *ecran,SDL_Surface *fond);



