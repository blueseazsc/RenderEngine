#ifndef IMAGE_H
#define IMAGE_H

#include "config.h"
#include "math.h"
#include "SDL_image.h"

namespace render {

enum ImageWrapType {
	IWT_DUP,
	IWT_CLAMP,
};

class Image 
{
private:
	typedef Uint32 BufferType;
	int32 _width = 0;
	int32 _height = 0;
	BufferType* _buffer = nullptr;
	ImageWrapType _wrapType = IWT_DUP;
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

	void setWrapType(ImageWrapType type) {
		_wrapType = type;
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
		switch(_wrapType) {
			case IWT_CLAMP:
				{
					if ( x >= _width )
						x = _width - 1;
					if ( y >= _height )
						y = _height - 1;
					return pixelAt(x,y);
				}
				break;
			case IWT_DUP:
			default:
				{
					return pixelAt( uint32(x) % _width, uint32(y) % _height );
				}
				break;
		}
	}
public:
 	static Image* loadFromFile(SDL_PixelFormat* format, const char*);
};
}
#endif
