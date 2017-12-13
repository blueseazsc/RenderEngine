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
		// _image2 =  render::Image::loadFromFile(_gFormat, "/Users/zhangsc/Downloads/image/colorKey.png");
		_image2 =  render::Image::loadFromFile(_gFormat, "/Users/zhangsc/Downloads/image/grass.png");
		if ( _image2 == nullptr ) 
		{
			std::cerr << "image load failed!" << std::endl;
			return false;
		}

		return true;
	}
	virtual void render() 
    {
		_gRaster.drawImage(0, 0, _image);
		// _gRaster.drawImageWithColorKey(100, 100, _image2, render::Rgba(255,0,0));
		_gRaster.drawImageWithAlphaTest(100, 100, _image2, 100);
		_gRaster.drawImageWithAlphaBlend(250, 250, _image2);
    }
	virtual void shutdown() 
	{
		delete _image;
		delete _image2;
	}
protected:
	render::Image *_image 	= nullptr;
	render::Image *_image2	= nullptr;
};

DECLARE_MAIN(Test);
