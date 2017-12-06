#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL.h>
#include "config.h"
#include "raster.h"

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
        _app = the_app;

		SDL_Init(SDL_INIT_VIDEO);

        init();

		_gWindow = SDL_CreateWindow(_info.title, 100, 100, _info.winWidth, _info.winHeight, SDL_WINDOW_SHOWN);

		_gRender = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

		//创建texture,注意像素格式和访问方式
		_gTexture = SDL_CreateTexture(_gRender, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, _info.winWidth, _info.winHeight);

		_gFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

		_gRaster.setInfo(_info.winWidth, _info.winHeight, _gFormat);

        startup();

		void* pix;
		int32 pitch;
        do
        {
			SDL_PollEvent(&_event);
			if(_event.type == SDL_QUIT)
				break;
			SDL_LockTexture(_gTexture, NULL, &pix, &pitch);
			_gRaster.setBuffer(pix);
			_gRaster.clear();
			render();
			SDL_UnlockTexture(_gTexture);

			SDL_RenderCopy(_gRender, _gTexture, NULL, NULL);
			SDL_RenderPresent(_gRender);
        } while (running);

        shutdown();

		SDL_FreeFormat(_gFormat);
		SDL_DestroyRenderer(_gRender);
		SDL_DestroyTexture(_gTexture);
		SDL_DestroyWindow(_gWindow);
		SDL_Quit();
    }

    virtual void init()
    {
        strcpy(_info.title, "RenderEngine");

        _info.winWidth = 800;
        _info.winHeight = 600;
    }

    virtual void startup()
    {

    }

	virtual void render() 
    {

    }

    virtual void shutdown()
    {

    }

public:
    struct APPINFO
    {
        char title[128];
        int32 winWidth;
        int32 winHeight;
    };

protected:
    APPINFO     _info;
    static      Application *_app;

	SDL_Window* _gWindow = nullptr;
	SDL_Renderer* _gRender = nullptr;
	SDL_Texture* _gTexture = nullptr;
	SDL_Event _event;
	SDL_PixelFormat* _gFormat = nullptr;

	render::Raster _gRaster;	
};

#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}
Application * Application::_app = nullptr;
#endif /* __APP_H__ */

