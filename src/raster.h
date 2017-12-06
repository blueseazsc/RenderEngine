#ifndef RASTER_H
#define RASTER_H

#include <SDL.h>
#include "config.h"
#include "math.h"

namespace render {

typedef Uint32 BufferType;

class Raster {
public:
	int32 _width = 0;
	int32 _height = 0;
private:
	BufferType* _buffer = nullptr;
	SDL_PixelFormat* _colorFormat = nullptr;
public:
	void clear();
	void drawPoint(int32 x, int32 y, Rgba color, int32 ptSize);
public:
	inline void setInfo(int32 width, int32 height, SDL_PixelFormat* colorFormat) { _width = width; _height = height; _colorFormat = colorFormat; }
	inline void setBuffer(void* buffer) { _buffer = (BufferType*)buffer;}
	inline void setPixel(uint32 x, uint32 y, Rgba color) 
	{
		if ( x >= _width || y >= _height )
			return;
		_buffer[y * _width + x] = SDL_MapRGBA(_colorFormat, color._r, color._g, color._b, color._a);
	}
};

}
#endif
