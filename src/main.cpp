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

		_image3 =  render::Image::loadFromFile(_gFormat, "/Users/zhangsc/Downloads/image/scale.jpg");
		if ( _image3 == nullptr ) 
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
		// _gRaster.drawImageWithAlphaTest(100, 100, _image2, 100);
		// _gRaster.drawImageWithAlphaBlend(250, 100, _image2);
		// _gRaster.drawImageWithAlpha(250, 250, _image2, 0.5f);
		// _gRaster.drawImage(200,300,_image3,50,50,30,50);
		// _gRaster.drawImageScale(100,100,50,50,_image3);
		render::Raster::Vertex    vertex  =
		{
			render::Point2i(10,10),      render::Point2f(0.0f,0.0f), render::Rgba(),
			render::Point2i(10,110),     render::Point2f(0.0f,1.0f), render::Rgba(),
			render::Point2i(110,110),    render::Point2f(1.0f,1.0f), render::Rgba(),
		};

		render::Raster::Vertex    vertex1  =
		{
			render::Point2i(10,10),      render::Point2f(0.0f,0.0f), render::Rgba(),
			render::Point2i(110,110),    render::Point2f(1.0f,1.0f), render::Rgba(),
			render::Point2i(110,10),     render::Point2f(1.0f,0.0f), render::Rgba(),
		};


		_gRaster.drawTriangle(vertex,_image3);
		_gRaster.drawTriangle(vertex1,_image3);
    }
	virtual void shutdown() 
	{
		delete _image;
		delete _image2;
		delete _image3;
	}
protected:
	render::Image *_image 	= nullptr;
	render::Image *_image2	= nullptr;
	render::Image *_image3	= nullptr;
};

DECLARE_MAIN(Test);
