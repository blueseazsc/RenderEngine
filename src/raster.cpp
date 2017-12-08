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
void Raster::drawTriangle(const Point2i* points,const Rgba* colors)
{
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
		
	float scale1 = (e2._y1 - e1._y1) / yOffset1;
	float step1 = 1.f / yOffset1; 

	float scale2 = 0;
	float step2 = 1.f / yOffset2; 

	for(int32 y = e2._y1; y < e2._y2; ++y) {
		int32 x1 = e1._x1 + (int32)(scale1 * xOffset1);
		int32 x2 = e2._x1 + (int32)(scale2 * xOffset2);

		Rgba color1 = colorLerp(e1._color1, e1._color2, scale1);
		Rgba color2 = colorLerp(e2._color1, e2._color2, scale2);

		Span span(x1, x2, color1, color2, y);
		drawSpan(span);

		scale1 += step1;
		scale2 += step2;
	} 
}
void Raster::drawSpan(const Span& span)
{
	float length = span._xEnd - span._xStart;
	for(int32 x = span._xStart; x <= span._xEnd; ++x) {
		Rgba color = colorLerp(span._colorStart, span._colorEnd, ( x - span._xStart ) / length );
		setPixel(x, span._y, color);
	}
}
