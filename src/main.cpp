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
	 	_image =  render::Image::loadFromFile(_gFormat, "/Users/zhangsc/Downloads/image/1.jpg");
		if ( _image == nullptr ) 
		{
			std::cerr << "image load failed!" << std::endl;
			return false;
		}

		return true;
	}
	virtual void render() 
    {
		_gRaster.drawImage(100, 100, _image);
    }
	virtual void shutdown() 
	{
		delete _image;
	}
protected:
	render::Image *_image = nullptr;
};

DECLARE_MAIN(Test);
