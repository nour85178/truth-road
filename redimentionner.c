#include <SDL/SDL.h>

#ifdef WIN32
#pragma comment(lib,"sdl.lib")
#pragma comment(lib,"sdlmain.lib")
#endif

void UpdateEvents(char* key,SDL_Surface** pscreen)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            key[event.key.keysym.sym]=1;
            break;
        case SDL_KEYUP:
            key[event.key.keysym.sym]=0;
            break;
        case SDL_VIDEORESIZE:
            *pscreen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_VIDEORESIZE);  
            break;
        }
    }
}

SDL_Rect Rect(int x,int y,int w,int h)        // pour faire un rectangle plus vite
{
    SDL_Rect r;
    r.x=x;
    r.y=y;
    r.w=w;
    r.h=h;
    return r;
}

SDL_Surface* LoadBMP(char* fichier,int vram)
{
    SDL_Rect R;
    SDL_Surface* r,*f = SDL_LoadBMP(fichier);    // charge l'image dans f en RAM
    if (!f)
    {
        printf("Echec chargement %s\n",fichier);
        SDL_Quit();
        exit(-1);
    }
    r=NULL;
    if (vram)
        r=SDL_CreateRGBSurface(SDL_HWSURFACE, f->w, f->h, 32, 0, 0, 0, 0);// cree une image en VRAM
    if (r==NULL) vram=0;    // Si plus de place en VRAM, alors r= NULL.
    if (!vram)
        r=SDL_CreateRGBSurface(SDL_SWSURFACE, f->w, f->h, 32, 0, 0, 0, 0);  // cree une image en RAM
    R=Rect(0,0,f->w,f->h);
    SDL_BlitSurface(f,NULL,r,&R);    // copie l'image f de la RAM vers firstscreen en VRAM
    SDL_FreeSurface(f);      // supprime la surface f : inutile maintenant --> libere la mémoire
    return r;
}

unsigned char GetPixelComp32(SDL_Surface* surface,int x,int y,int c)
{ // recupere le pixel x,y de la surfece "surface", la composante c (3 composantes RGB)
    unsigned char *p = ((unsigned char*)surface->pixels) + y * surface->pitch + x * 4;
    return p[c];
}

void PutPixelComp32(SDL_Surface* surface,int x,int y,int c,unsigned char val)
{ // ecrit la composante c (3 composantes RGB) sur le pixel x,y de la surface "surface"
    unsigned char *p = ((unsigned char*)surface->pixels) + y * surface->pitch + x * 4;
    p[c] = val;
}

void Stretch_Nearest(SDL_Surface* src,SDL_Surface* dest)
{
    int i,j,k;
    double rx,ry;
    rx = dest->w*1.0/src->w;
    ry = dest->h*1.0/src->h;
    for(i=0;i<dest->w;i++)
        for(j=0;j<dest->h;j++)
            for(k=0;k<3;k++)
            {
                unsigned char pix;
                pix = GetPixelComp32(src,(int)(i/rx),(int)(j/ry),k);
                PutPixelComp32(dest,i,j,k,pix);
            }
}

void Stretch_Linear(SDL_Surface* src,SDL_Surface* dest)
{
    int i,j,k;
    double rx,ry;
    rx = dest->w*1.0/src->w;
    ry = dest->h*1.0/src->h;
    for(i=0;i<dest->w;i++)
        for(j=0;j<dest->h;j++)
        {
            unsigned char pix;
            double valx,valy,fx,fy;
            int minx,miny,maxx,maxy;
            valx = i/rx;
            valy = j/ry;
            minx = (int)valx;
            miny = (int)valy;
            maxx = minx+1;
            if (maxx>=src->w)
                maxx--;
            maxy = miny+1;
            if (maxy>=src->h)
                maxy--;
            fx = valx-minx;  // garde partie flottante
            fy = valy-miny;
            for(k=0;k<3;k++)
            {
                pix = (unsigned char)(GetPixelComp32(src,minx,miny,k)*(1-fx)*(1-fy) + GetPixelComp32(src,maxx,miny,k)*fx*(1-fy)
                    + GetPixelComp32(src,minx,maxy,k)*(1-fx)*fy + GetPixelComp32(src,maxx,maxy,k)*fx*fy);
                PutPixelComp32(dest,i,j,k,pix);
            }
        }
}

void Strechblit(SDL_Surface* src,SDL_Surface* dest)
{
    SDL_Surface* img = SDL_CreateRGBSurface(SDL_SWSURFACE,dest->w,dest->h,32,0,0,0,0);
    Stretch_Nearest(src,img);
    //Stretch_Linear(src,img);
    SDL_BlitSurface(img,NULL,dest,NULL);
    SDL_FreeSurface(img);
}

int main(int argc,char** argv)
{
    SDL_Surface* image,*screen;
    char key[SDLK_LAST]={0};
    SDL_Init(SDL_INIT_VIDEO);
    image = LoadBMP("b1.bmp",0);
    screen=SDL_SetVideoMode(image->w,image->h,32,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_VIDEORESIZE);  
    SDL_ShowCursor(1);
    while(!key[SDLK_ESCAPE])
    {
        UpdateEvents(key,&screen);
        Strechblit(image,screen);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(image);
    SDL_Quit();
    return 0;
}
