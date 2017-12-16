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
	DM_TRIANGLES 	= 4,
};

enum DataType {
	DT_UINT8, 
	DT_FLOAT, 
	DT_DOUBLE, 
};

class DataElementDes {
public:
	int32       _size;
	DataType	_type;
	int32       _stride;
	const void* _data;
};

class Span {
public:
	int32 _xStart;
	int32 _xEnd;

	Rgba _colorStart;
	Rgba _colorEnd;

	Point2f _uvStart;
	Point2f _uvEnd;

	int32 _y;
public:
	Span(int32 xStart, int32 xEnd, int32 y, Rgba colorStart, Rgba colorEnd, const Point2f& uvStart, const Point2f uvEnd)
	{
		if ( xStart < xEnd ) {
			_xStart = xStart;
			_xEnd = xEnd;

			_colorStart = colorStart;
			_colorEnd = colorEnd;

			_uvStart = uvStart;
			_uvEnd = uvEnd;

			_y = y;
		}
		else
		{
			_xStart = xEnd;
			_xEnd = xStart;

			_colorStart = colorEnd;
			_colorEnd = colorStart;

			_uvStart = uvEnd;
			_uvEnd = uvStart;

			_y = y;
		}
	}
};

class Edge {
public:
	int32 _x1;
	int32 _y1;
	Point2f _uv1;
	Rgba _color1;

	int32 _x2;
	int32 _y2;
	Point2f _uv2;
	Rgba _color2;
public:
	Edge(int32 x1, int32 y1, Rgba color1, const Point2f& uv1, int32 x2, int32 y2, Rgba color2, const Point2f& uv2)
	{
		if ( y1 < y2 ) {
			_x1 	= x1;
			_y1		= y1;
			_uv1 	= uv1;
			_color1	= color1;

			_x2		= x2;
			_y2		= y2;
			_uv2 	= uv2;
			_color2	= color2;
		}
		else {
			_x1 	= x2;
			_y1		= y2;
			_uv1 	= uv2;
			_color1	= color2;

			_x2		= x1;
			_y2		= y1;
			_uv2 	= uv1;
			_color2	= color1;
		}
	}
};

class Raster {
public:
	class Vertex {
	public:
		Point2i point0;
		Point2f uv0;
		Rgba c0;

		Point2i point1;
		Point2f uv1;
		Rgba c1;

		Point2i point2;
		Point2f uv2;
		Rgba c2;
	};
public:
	typedef Uint32 BufferType;
	int32 _width;
	int32 _height;
private:
	BufferType* _buffer;
	SDL_PixelFormat* _colorFormat;
	Rgba _color;
private:
	Image* _texture;
	Matrix4f _matModel;
	Matrix4f _matView;
	Matrix4f _matProj;
	Matrix4f _matProjView;
	Vector2f _viewPort;
	Frustum _frust;

	DataElementDes 	_positionPointer;
	DataElementDes 	_colorPointer;
	DataElementDes 	_uvPointer;

	DataElementDes 	_defaultColorPointer;
	DataElementDes 	_defaultUVPointer;

	Rgba           	_defaultColorArray[3];
	float 			_defaultUVArray[3 * 2];
public:
	Raster();
	void clear();
	inline void setInfo(int32 width, int32 height, SDL_PixelFormat* colorFormat) { _width = width; _height = height; _colorFormat = colorFormat; }
	inline void setBuffer(void* buffer) { _buffer = (BufferType*)buffer;}

	void vertexPointer(int32 size, DataType type, int32 stride, const void* data)
	{
		_positionPointer._size   =   size;
		_positionPointer._type   =   type;
		_positionPointer._stride =   stride;
		_positionPointer._data   =   data;
	}

	void colorPointer(int32 size, DataType type, int32 stride, const void* data)
	{
		_colorPointer._size     =   size;
		_colorPointer._type     =   type;
		_colorPointer._stride   =   stride;
		_colorPointer._data     =   data;
	}

	void textureCoordPointer(int32 size, DataType type, int32 stride, const void* data)
	{
		_uvPointer._size        =   size;
		_uvPointer._type        =   type;
		_uvPointer._stride      =   stride;
		_uvPointer._data        =   data;
	}

	void bindTexture(Image* image)
	{
		_texture    =   image;
	}

	void loadModelMatrix(const Matrix4f& mat)
	{
		_matModel = mat;
	}
	void loadModelIdentity()
	{
		_matModel = Matrix4fIdentity;
	}
	void loadViewMatrix(const Matrix4f& mat)
	{
		_matView =   mat;
	}
	void loadViewIdentity()
	{
		_matView = Matrix4fIdentity;
	}
	void loadProjMatrix(const Matrix4f& mat)
	{
		_matProj =   mat;
	}
	void loadProjIdentity()
	{
		_matProj = Matrix4fIdentity;
	}

	void setPerspective( float fovy, float aspect, float zNear, float zFar )
	{
		genProjection(_matProj, fovy, aspect, zNear, zFar);
	}
	void lookat( const Vector3f& eye, const Vector3f& center,const Vector3f& up )
	{
		genLookat(_matView, eye, center, up);
	}
	void setViewPort( int32 x, int32 y, int32 w, int32 h )
	{
		_viewPort.x() = w;
		_viewPort.y() = h;
	}

	void drawArrays(DrawMode mode, const Point2f* points, int32 count);

	void drawArrays(DrawMode mode, int32 start, int32 count);

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

	void drawTriangle(const Vertex& vertex, Image* image);

	void drawTriangle(Edge edges[3]);

	// |y2 - y1| in e1 >= |y2 - y1| in e2
	void drawEdge(const Edge& e1, const Edge& e2, Image* image);

	void drawSpan(const Span& span, Image* image);

	void drawImage(int32 startX, int32 startY, const Image* image);

	void drawImageWithColorKey(int32 startX, int32 startY, const Image* image, Rgba key);

	void drawImageWithAlphaTest(int32 startX, int32 startY, const Image* image, uint8 alpha); 

	void drawImageWithAlphaBlend(int32 startX, int32 startY, const Image* image);

	void drawImageWithAlpha(int32 startX, int32 startY, const Image* image, float alpha);

	void drawImage(int32 startX, int32 startY, const Image* image, int32 ix, int32 iy, int32 iw, int32 ih);

	void drawImageScale(int32 dstX, int32 dstY, int32 dstW, int32 dstH, const Image* image);
private:
	bool piplineTrasform(Vector4f& pos);
	void drawPoint(const Point2f& p, Rgba color) { drawPoint(p.x(), p.y(), color, 1); }
	void drawLine(const Point2f& p1, const Point2f& p2, Rgba color1, Rgba color2);
	inline Rgba getPixel(uint32 x,uint32 y)
	{
		return  Rgba(_buffer[y * _width + x]);
	}
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
