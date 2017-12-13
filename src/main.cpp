#include "app.h"
#include "math.h"
#include "tictoc.h"
#include "image.h"

#include <stdio.h>

class Test:	public Application
{
public:
	virtual bool startup() 
	{
	 	_image =  render::Image::loadFromFile(_gFormat, "/Users/zhangsc/Downloads/image/bg.png");
		if ( _image == nullptr ) 
		{
			std::cerr << "image load failed!" << std::endl;
			return false;
		}
	 	_colorKey =  render::Image::loadFromFile(_gFormat, "/Users/zhangsc/Downloads/image/colorKey.png");
		if ( _colorKey == nullptr ) 
		{
			std::cerr << "image load failed!" << std::endl;
			return false;
		}

		return true;
	}
	virtual void render() 
    {
		_gRaster.drawImage(0, 0, _image);
		_gRaster.drawImageWithColorKey(100, 100, _colorKey, render::Rgba(255,0,0));
    }
	virtual void shutdown() 
	{
		delete _image;
		delete _colorKey;
	}
protected:
	render::Image *_image = nullptr;
	render::Image *_colorKey = nullptr;
};

DECLARE_MAIN(Test);
