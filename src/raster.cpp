#include "raster.h"

using namespace render;

void Raster::clear() 
{
	memset(_buffer, 0, _width * _height * sizeof(BufferType));
}
void Raster::drawPoint(int32 x, int32 y, Rgba color, int32 ptSize) 
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
