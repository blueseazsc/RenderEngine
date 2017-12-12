#include "app.h"
#include "math.h"
#include "tictoc.h"

#include "SDL_image.h"

#include <stdio.h>

class Test:	public Application
{
public:
	virtual bool startup() 
	{
		_texture = IMG_LoadTexture(_gRender, "/Users/zhangsc/Downloads/image/1.jpg");
		if (_texture == nullptr){
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
	virtual void render() 
    {
		_gRaster.drawImage(100, 100, 200, 200);
    }
	virtual void shutdown() 
	{
		SDL_DestroyTexture(_texture);
	}
protected:
	SDL_Texture *_texture = nullptr;
};

DECLARE_MAIN(Test);
