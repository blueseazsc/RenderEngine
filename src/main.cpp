#include <SDL.h>
#include "config.h"

#include "raster.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRender = NULL;
SDL_Texture* gTexture = NULL;
SDL_Event event;
SDL_PixelFormat* format;

render::Raster raster;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("RenderEngine", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

    gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    //创建texture,注意像素格式和访问方式
    gTexture = SDL_CreateTexture(gRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
}

void close()
{
	SDL_FreeFormat(format);
    SDL_DestroyRenderer(gRender);
    SDL_DestroyTexture(gTexture);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void render(void* pixel, int pitch);

int main()
{
    void* pix;
    int pitch;
    init();

	while (1) {
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			break;
		SDL_LockTexture(gTexture, NULL, &pix, &pitch);
		render(pix, pitch);
		SDL_UnlockTexture(gTexture);

		SDL_RenderCopy(gRender, gTexture, NULL, NULL);
		SDL_RenderPresent(gRender);
	}

    close();
	return 0;
}

/*
void render(void* pixel, int pitch) 
{
	uint32 color = sdl_maprgba(format, 0xff, 0, 0, 0xff / 3);
	for(int i = 0; i < pitch * 400 / 4; i++)
		((uint32*)pixel)[i] = color;
}
*/

void render(void* pixel, int pitch) 
{
	uint32 color = sdl_maprgba(format, 0xff, 0, 0, 0xff / 3);
}
