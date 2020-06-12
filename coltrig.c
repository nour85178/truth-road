#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

typedef struct Cercle
{
   int x,y;
   int rayon;
}Cercle;

int Collision(Cercle C1,Cercle C2)
{
   int col;
   int d2 = (C1.x-C2.x)*(C1.x-C2.x) + (C1.y-C2.y)*(C1.y-C2.y);
   if (d2 > (C1.rayon + C2.rayon)*(C1.rayon + C2.rayon))
      col=0;
   else
      col=1;
return col;
}

int main()
{
   int col;
   Cercle C1,C2;
col=Collision(C1,C2);
   if (col=1)
     printf("il y a collision");
   else
     printf("pas de collision");
}
    
