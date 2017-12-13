#ifndef IMAGE_H
#define IMAGE_H

#include "config.h"
#include "math.h"
#include "SDL_image.h"

namespace render {

class Image 
{
private:
	typedef Uint32 BufferType;
	int32 _width = 0;
	int32 _height = 0;
	BufferType* _buffer = nullptr;
public:
	Image(int32 w, int32 h, void* data) 
	{
		if (w == 0 || h == 0 || data == nullptr)
			return;
		_width  =   w;
		_height =   h;
		_buffer =   new BufferType[w * h];
		memcpy(_buffer, data, w * h * sizeof(BufferType));
	}
	~Image()
	{
		delete []_buffer;
	}

	int32 width() const
	{
		return _width;
	}
	int32 height() const
	{
		return _height;
	}

	Rgba pixelAt(int32 x, int32 y) const
	{
		return Rgba(_buffer[y * _width + x]);
	}
	Rgba pixelUV(float u, float v) const
	{
		float x = u * _width;
		float y = v * _height;
		return pixelAt(x,y);
	}
public:
 	static Image* loadFromFile(SDL_PixelFormat* format, const char*);
};
}
#endif
