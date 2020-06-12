#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

int initialiser_enigme1()
{SDL_Surface *ecran=NULL,*image=NULL,*quest=NULL,*im1=NULL,*im2=NULL,*im3=NULL;
 SDL_Rect p1,p2,p3,pos,position;
 
 position.x=0;
 position.y=0;
 pos.x=300;
 pos.y=20;
 p1.x=70;
 p1.y=420;
 p2.x=500;
 p2.y=420;
 p3.x=1000;
 p3.y=420;

 SDL_Init(SDL_INIT_VIDEO);
//ecran=SDL_SetVideoMode(1280,720,32, SDL_HWSURFACE);
 ecran=SDL_SetVideoMode(800,600,32,SDL_HWSURFACE);
 image=IMG_Load("background-level1");
 quest=IMG_Load("question1.png");
 im1=IMG_Load("rep1.1.png");
 im2=IMG_Load("rep1.2.png");
 im3=IMG_Load("rep1.3.png");
 return 1;
}
 
int afficher_enigme1()
{
 SDL_BlitSurface(image,NULL,ecran,&position);
 SDL_BlitSurface(quest,NULL,ecran,&pos);
 SDL_BlitSurface(im1,NULL,ecran,&p1);
 SDL_BlitSurface(im2,NULL,ecran,&p2);
 SDL_BlitSurface(im3,NULL,ecran,&p3);
 SDL_Flip(ecran);
 return 1;
}

int main()
{

int continuer=0;
int cont=0;
continuer=initialiser_enigme();
cont=afficher_enigme();

if ((continuer==1)&&(cont==1))
 printf("initialisation et affichage enigme");
else 
 SDL_Quit();
}
