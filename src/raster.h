#ifndef RASTER_H
#define RASTER_H

#include "math.h"

namespace render {

class Raster {
public:
	Rgba _buffer[256][256];
public:
	void clear() 
	{
		memset(&_buffer, 0, sizeof(_buffer));
	}
	void setPixel(int32_t x, int32_t y, const Rgba& color) 
	{
		if ( x < 0 || y < 0 || x >= 256 || y >= 256 )
			return;
		_buffer[y][x] = color;
	}
	void drawPoint(int32_t x, int32_t y, const Rgba& color, int32_t ptSize) 
	{
		switch(ptSize) 
		{
			case 1:
				setPixel(x, y, color);
				break;
			case 2:
				setPixel(x + 0, y + 0, color);
				setPixel(x + 1, y + 0, color);
				setPixel(x + 0, y + 1, color);
				setPixel(x + 1, y + 1, color);
				break;
			case 3:
				setPixel(x - 1, y - 1, color);
				setPixel(x + 0, y - 1, color);
				setPixel(x + 1, y - 1, color);

				setPixel(x - 1, y + 0, color);
				setPixel(x + 0, y + 0, color);
				setPixel(x + 1, y + 0, color);

				setPixel(x - 1, y + 1, color);
				setPixel(x + 0, y + 1, color);
				setPixel(x + 1, y + 1, color);
				break;
		}
	}
};
}
#endif
