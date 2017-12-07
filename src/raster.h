#ifndef RASTER_H
#define RASTER_H

#include <SDL.h>
#include "config.h"
#include "math.h"

namespace render {


enum DrawMode {
	DM_POINTS		= 0,
	DM_LINES		= 1,
	DM_LINE_LOOP	= 2,
	DM_LINE_STRIP	= 3,
};

class Raster {
public:
	typedef Uint32 BufferType;
	int32 _width = 0;
	int32 _height = 0;
private:
	BufferType* _buffer = nullptr;
	SDL_PixelFormat* _colorFormat = nullptr;
	Rgba _color;
public:
	void clear();
	inline void setInfo(int32 width, int32 height, SDL_PixelFormat* colorFormat) { _width = width; _height = height; _colorFormat = colorFormat; }
	inline void setBuffer(void* buffer) { _buffer = (BufferType*)buffer;}

	void drawArrays(DrawMode mode, const Point2f* points, int32 count);

	void drawPoint(int32 x, int32 y, Rgba color, int32 ptSize);

	void drawFilleRect(int32 startX,int32 startY,int32 w,int32 h);

	/*
	 *  drawRect points and colors sequence:
	 *	0 -> 1
	 *		 |
	 *	3 <- 2
	 */
	void drawRect(const Point2i* points,const Rgba* colors);
private:
	void drawPoint(const Point2f& p, Rgba color) { drawPoint(p.x(), p.y(), color, 1); }
	void drawLine(const Point2f& p1, const Point2f& p2, Rgba color1, Rgba color2);
	inline void setPixelEx(uint32 x, uint32 y, Rgba color) 
	{
		_buffer[y * _width + x] = SDL_MapRGBA(_colorFormat, color._r, color._g, color._b, color._a);
	}
	inline void setPixel(uint32 x, uint32 y, Rgba color) 
	{
		if ( x >= _width || y >= _height )
			return;
		_buffer[y * _width + x] = SDL_MapRGBA(_colorFormat, color._r, color._g, color._b, color._a);
	}
};

}
#endif
