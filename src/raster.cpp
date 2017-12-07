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
void Raster::drawFilleRect(int32 startX,int32 startY,int32 w,int32 h)
{
	int32 left = std::max(startX, 0);
	int32 top = std::max(startY, 0);

	int32 right = std::min(startX + w, _width);
	int32 bottom = std::min(startY + h, _height);

	for(int32 x = left; x < right; ++x) 
	{
		for(int32 y = top; y < bottom; ++y)
		{
			setPixelEx(x, y, _color);
		}
	}
}
void Raster::drawRect(const Point2i* points,const Rgba* colors)
{
	int32 left = std::max(points[0].x(), 0);
	int32 top = std::max(points[0].y(), 0);

	int32 right = std::min(points[2].x(), _width);
	int32 bottom = std::min(points[2].y(), _height);

	float w = right - left;
	float h = bottom - top;
	for(int32 x = left; x < right; ++x) 
	{
		Rgba color1 = colorLerp(colors[0], colors[1], ( x - left ) / w);
		Rgba color2 = colorLerp(colors[3], colors[2], ( x - left ) / w);
		for(int32 y = top; y < bottom; ++y)
		{
			Rgba color = colorLerp(color1, color2, ( y - top ) / h);
			setPixelEx(x, y, color);
		}
	}
}
void Raster::drawLine(const Point2f& p1, const Point2f& p2, Rgba color1, Rgba color2)
{
	float xOffset = p1.x() - p2.x();
	float yOffset = p1.y() - p2.y();

	if ( xOffset == 0 && yOffset == 0 ) {
		setPixel(p1.x(), p1.y(), color1);
	}

	if ( fabs(xOffset) > fabs(yOffset) ) {
		float xMin;
		float xMax;
		if ( p1.x() > p2.x() ) {
			xMin = p2.x();
			xMax = p1.x();
		}
		else {
			xMin = p1.x();
			xMax = p2.x();
		}
		float length = xMax - xMin;
		float slope = yOffset / xOffset;
		for(float x = xMin; x < xMax; x += 1.f) {
			float y = p1.y() + slope * ( x - p1.x() );
			float s = (x - xMin) / length;
			Rgba color = colorLerp(color1, color2, s);
			setPixel(x, y, color);
		}
	}
	else {
		float yMin;
		float yMax;
		if ( p1.y() > p2.y() ) {
			yMin = p2.y();
			yMax = p1.y();
		}
		else {
			yMin = p1.y();
			yMax = p2.y();
		}
		float length = yMax - yMin;
		float slope = xOffset / yOffset;
		for(float y = yMin; y < yMax; y += 1.f) {
			float x = p1.x() + slope * ( y - p1.y() );
			float s = (y - yMin) / length;
			Rgba color = colorLerp(color1, color2, s);
			setPixel(x, y, color);
		}
	}
}
void Raster::drawArrays(DrawMode mode, const Point2f* points, int32 count)
{
	switch(mode) {
		case DM_POINTS:
			for(int32 i = 0 ; i < count; ++i)
				drawPoint(points[i], _color);
			break;
		case DM_LINES:
			count = count / 2 * 2;
			for(int32 i = 0 ; i < count; i+=2)
				drawLine(points[i], points[i+1], _color, _color);
			break;
		case DM_LINE_LOOP:
			drawLine(points[0], points[1], _color, _color);
			for(int32 i = 2 ; i < count; ++i)
				drawLine(points[i-1], points[i], _color, _color);
			drawLine(points[0], points[count-1], _color, _color);
			break;
		case DM_LINE_STRIP:
			drawLine(points[0], points[1], _color, _color);
			for(int32 i = 2 ; i < count; ++i)
				drawLine(points[i-1], points[i], _color, _color);
			break;
		default:
			break;
	}
}
