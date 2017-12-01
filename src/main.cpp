#include "app.h"

class Test:	public Application
{
public:
	virtual void render(void* pixel, int pitch) 
    {
		Uint32 color = SDL_MapRGBA(format, 0xff, 0, 0, 0xff / 3);
		for(int i = 0; i < pitch * 400 / 4; i++)
			((Uint32*)pixel)[i] = color;
    }
};

DECLARE_MAIN(Test);
