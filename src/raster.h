#ifndef RASTER_H
#define RASTER_H

#include <SDL.h>
#include "config.h"
#include "math.h"
#include "image.h"

namespace render {


enum DrawMode {
	DM_POINTS		= 0,
	DM_LINES		= 1,
	DM_LINE_LOOP	= 2,
	DM_LINE_STRIP	= 3,
};

class Span {
public:
	int32 _xStart;
	int32 _xEnd;

	Rgba _colorStart;
	Rgba _colorEnd;

	int32 _y;
public:
	Span(int32 xStart, int32 xEnd, Rgba colorStart, Rgba colorEnd, int32 y)
	{
		if ( xStart < xEnd ) {
			_xStart = xStart;
			_xEnd = xEnd;

			_colorStart = colorStart;
			_colorEnd = colorEnd;

			_y = y;
		}
		else
		{
			_xStart = xEnd;
			_xEnd = xStart;

			_colorStart = colorEnd;
			_colorEnd = colorStart;

			_y = y;
		}
	}
};

class Edge {
public:
	int32 _x1;
	int32 _y1;
	Rgba _color1;

	int32 _x2;
	int32 _y2;
	Rgba _color2;
public:
	Edge(int32 x1, int32 y1, Rgba color1, int32 x2, int32 y2, Rgba color2)
	{
		if ( y1 < y2 ) {
			_x1 	= x1;
			_y1		= y1;
			_color1	= color1;

			_x2		= x2;
			_y2		= y2;
			_color2	= color2;
		}
		else {
			_x1 	= x2;
			_y1		= y2;
			_color1	= color2;

			_x2		= x1;
			_y2		= y1;
			_color2	= color1;
		}
	}
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

	inline bool isInRect(const Point2i& point) {
		return point.x() >= 0 && point.x() <= _width && point.y() >= 0 && point.y() <= _height;
	}
	void drawTriangle(const Point2i* points,const Rgba* colors);
	// |y2 - y1| in e1 >= |y2 - y1| in e2
	void drawEdge(const Edge& e1, const Edge& e2);

	void drawSpan(const Span& span);

	void drawImage(int32 startX, int32 startY, const Image* image);

	void drawImageWithColorKey(int32 startX, int32 startY, const Image* image, Rgba key);
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
