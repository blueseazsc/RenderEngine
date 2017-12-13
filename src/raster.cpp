#include "raster.h"
#include <iostream>

using namespace render;

Image* Image::loadFromFile(SDL_PixelFormat* format, const char* fileName)
{
	SDL_Surface *surface = IMG_Load(fileName);
	if (surface == nullptr)
	{
		std::cerr << SDL_GetError() << std::endl;
		return nullptr;
	}

	std::cout << fileName << " format: (" 
		<< SDL_PIXELFLAG(surface->format->format) << "," 
		<< SDL_PIXELTYPE(surface->format->format) << "," 
		<< SDL_PIXELORDER(surface->format->format) << "," 
		<< SDL_PIXELLAYOUT(surface->format->format) << "," 
		<< SDL_BITSPERPIXEL(surface->format->format) << "," 
		<< SDL_BYTESPERPIXEL(surface->format->format) << "," 
		<< SDL_GetPixelFormatName(surface->format->format) 
		<< ")" << std::endl;
	std::cout << fileName << " width: " << surface->w << " height: " << surface->h << std::endl;

	SDL_Surface *tmp = surface;
	surface = SDL_ConvertSurface(surface, format, 0);
	SDL_FreeSurface(tmp);

	std::cout << fileName << " convert format: (" 
		<< SDL_PIXELFLAG(surface->format->format) << "," 
		<< SDL_PIXELTYPE(surface->format->format) << "," 
		<< SDL_PIXELORDER(surface->format->format) << "," 
		<< SDL_PIXELLAYOUT(surface->format->format) << "," 
		<< SDL_BITSPERPIXEL(surface->format->format) << "," 
		<< SDL_BYTESPERPIXEL(surface->format->format) << "," 
		<< SDL_GetPixelFormatName(surface->format->format) 
		<< ")" << std::endl;
	std::cout << fileName << " width: " << surface->w << " height: " << surface->h << std::endl;

	Image* image = new Image(surface->w, surface->h, surface->pixels);

	SDL_FreeSurface(surface);

	return  image;
}

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
void Raster::drawTriangle(const Point2i* points,const Rgba* colors)
{
	// if ( !isInRect(points[0]) && !isInRect(points[1]) && !isInRect(points[2])) 
		// return;

	Edge edges[3] = {
		Edge(points[0].x(), points[0].y(), colors[0], points[1].x(), points[1].y(), colors[1]),
		Edge(points[1].x(), points[1].y(), colors[1], points[2].x(), points[2].y(), colors[2]),
		Edge(points[2].x(), points[2].y(), colors[2], points[0].x(), points[0].y(), colors[0]),
	};

	int32 iMax = 0;
	int32 lMax = 0;
	for(int32_t i = 0; i < 3; ++i) {
		if ( edges[i]._y2 - edges[i]._y1 > lMax ) {
			lMax = edges[i]._y2 - edges[i]._y1;
			iMax = i;
		}
	}

	int32 iShort1 = (iMax + 1) % 3;
	int32 iShort2 = (iMax + 2) % 3;

	drawEdge(edges[iMax], edges[iShort1]);
	drawEdge(edges[iMax], edges[iShort2]);
}
void Raster::drawEdge(const Edge& e1, const Edge& e2)
{
	float xOffset1 = e1._x2 - e1._x1;
	float yOffset1 = e1._y2 - e1._y1;

	float xOffset2 = e2._x2 - e2._x1;
	float yOffset2 = e2._y2 - e2._y1;

	if ( yOffset1 == 0 || yOffset2 == 0 )
		return;
		
	float colorStep1 = 1.f / yOffset1; 
	float colorScale1 = (e2._y1 - e1._y1) * colorStep1;

	float xStep1 = xOffset1 / yOffset1; 
	float xScale1 = (e2._y1 - e1._y1) * xStep1;

	int32 startY1 = std::max(e1._y1, 0);
	int32 endY1 = std::min(e1._y2, _height);

	colorScale1 += (startY1 - e1._y1) * colorStep1; 
	xScale1 += (startY1 - e1._y1) * xStep1;

	float colorStep2 = 1.f / yOffset2; 
	float colorScale2 = 0;

	float xStep2 = xOffset2 / yOffset2; 
	float xScale2 = 0;

	int32 startY2 = std::max(e2._y1, 0);
	int32 endY2 = std::min(e2._y2, _height);

	colorScale2 += (startY2 - e2._y1) * colorStep1; 
	xScale2 += (startY2 - e2._y1) * xStep1;

	for(int32 y = startY2; y < endY2; ++y) {
		int32 x1 = e1._x1 + (int32)(xScale1);
		int32 x2 = e2._x1 + (int32)(xScale2);

		Rgba color1 = colorLerp(e1._color1, e1._color2, colorScale1);
		Rgba color2 = colorLerp(e2._color1, e2._color2, colorScale2);

		Span span(x1, x2, color1, color2, y);
		drawSpan(span);

		colorScale1 += colorStep1;
		colorScale2 += colorStep2;

		xScale1 += xStep1;
		xScale2 += xStep2;
	} 
}
void Raster::drawSpan(const Span& span)
{
	float length = span._xEnd - span._xStart;

	float step = 1.f / length;
	float scale = 0;
	
	int32 startX = std::max(span._xStart, 0);
	int32 endX = std::min(span._xEnd, _width);
	scale += (startX - span._xStart) * step;

	for(int32 x = startX; x <= endX; ++x) {
		Rgba color = colorLerp(span._colorStart, span._colorEnd, scale );
		setPixelEx(x, span._y, color);

		scale += step;
	}
}
void Raster::drawImage(int32 startX, int32 startY, const Image* image) 
{
	int32 left = std::max(startX, 0);
	int32 top = std::max(startY, 0);

	int32 right = std::min(startX + image->width(), _width);
	int32 bottom = std::min(startY + image->height(), _height);

	for(int32 x = left; x < right; ++x) 
	{
		for(int32 y = top; y < bottom; ++y)
		{
			Rgba color = image->pixelAt(x - left,y - top);
			setPixelEx(x, y, color);
		}
	}
}
void Raster::drawImageWithColorKey(int32 startX, int32 startY, const Image* image, Rgba key) 
{
	int32 left = std::max(startX, 0);
	int32 top = std::max(startY, 0);

	int32 right = std::min(startX + image->width(), _width);
	int32 bottom = std::min(startY + image->height(), _height);

	for(int32 x = left; x < right; ++x) 
	{
		for(int32 y = top; y < bottom; ++y)
		{
			Rgba color = image->pixelAt(x - left,y - top);
			if ( color != key )
				setPixelEx(x, y, color);
		}
	}
}
void Raster::drawImageWithAlphaTest(int32 startX, int32 startY, const Image* image, uint8 alpha) 
{
	int32 left = std::max(startX, 0);
	int32 top = std::max(startY, 0);

	int32 right = std::min(startX + image->width(), _width);
	int32 bottom = std::min(startY + image->height(), _height);

	for(int32 x = left; x < right; ++x) 
	{
		for(int32 y = top; y < bottom; ++y)
		{
			Rgba color = image->pixelAt(x - left,y - top);
			if ( color._a < alpha )
				setPixelEx(x, y, color);
		}
	}
}
