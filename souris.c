#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "SDL/SDL_mixer.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>




int main(int argc,char **agrv[])
{
int continuer =1;
SDL_Event event ;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *ecran=NULL,*image=NULL,*personnage=NULL;
SDL_Rect positionPersonnage;
SDL_Rect positionImage;
positionPersonnage.x=0;
positionPersonnage.y=300;
positionImage.x=0;
positionImage.y=0;
image=IMG_Load("background-level1.png");
personnage=IMG_Load("calque-2.png");
 SDL_SetColorKey(personnage,SDL_SRCCOLORKEY,SDL_MapRGB(personnage->format,255,255,255));//fond du personn transpar
ecran=SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
 SDL_WM_SetCaption("TESTE",NULL);//donner le nom de la fenetre

while (continuer)
{
SDL_PollEvent(&event);
 switch (event.type)
{
case SDL_QUIT:
continuer=0;
break ;
case SDL_MOUSEBUTTONUP:
if (event.button.button==SDL_BUTTON_LEFT)
{positionPersonnage.x =event.button.x; //coordonnee du curseur
positionPersonnage.y=event.button.y;
break ;

}}
 
SDL_BlitSurface(image,NULL,ecran,&positionImage); //mise a jou
SDL_BlitSurface(personnage,NULL,ecran,&positionPersonnage); //mise a jou
SDL_Flip(ecran); //mis a jours
}}
