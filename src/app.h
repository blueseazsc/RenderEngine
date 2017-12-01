#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL.h>

class Application
{
public:
    Application() {
	}
    virtual ~Application() {
	}
    virtual void run(Application* the_app)
    {
        bool running = true;
        app = the_app;

		SDL_Init(SDL_INIT_VIDEO);

        init();

		gWindow = SDL_CreateWindow(info.title, 100, 100, info.windowWidth, info.windowHeight, SDL_WINDOW_SHOWN);

		gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

		//创建texture,注意像素格式和访问方式
		gTexture = SDL_CreateTexture(gRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, info.windowWidth, info.windowHeight);

		format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

        startup();

		void* pix;
		int pitch;
        do
        {
			SDL_PollEvent(&event);
			if(event.type == SDL_QUIT)
				break;
			SDL_LockTexture(gTexture, NULL, &pix, &pitch);
			render(pix, pitch);
			SDL_UnlockTexture(gTexture);

			SDL_RenderCopy(gRender, gTexture, NULL, NULL);
			SDL_RenderPresent(gRender);
        } while (running);

        shutdown();

		SDL_FreeFormat(format);
		SDL_DestroyRenderer(gRender);
		SDL_DestroyTexture(gTexture);
		SDL_DestroyWindow(gWindow);
		SDL_Quit();
    }

    virtual void init()
    {
        strcpy(info.title, "RenderEngine");

        info.windowWidth = 800;
        info.windowHeight = 600;
    }

    virtual void startup()
    {

    }

	virtual void render(void* pixel, int pitch) 
    {

    }

    virtual void shutdown()
    {

    }

public:
    struct APPINFO
    {
        char title[128];
        int windowWidth;
        int windowHeight;
    };

protected:
    APPINFO     info;
    static      Application *app;

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRender = NULL;
	SDL_Texture* gTexture = NULL;
	SDL_Event event;
	SDL_PixelFormat* format;
};

#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}
Application * Application::app = 0;
#endif /* __APP_H__ */

