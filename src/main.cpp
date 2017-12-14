#include "app.h"
#include "math.h"
#include "tictoc.h"
#include "image.h"

#include <stdio.h>

class Test:	public Application
{
public:
	class Vertex
	{
	public:
		float       x,y;
		float       u,v;
		render::Rgba  color;
	};
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

		Vertex  vertexs[]   =
		{
			{10,    10,     0.0f,   0.0f,   render::Rgba(255,255,255,255)},
			{220,   220,    1.0f,   1.0f,   render::Rgba(255,255,255,255)},
			{220,   10,     1.0f,   0.0f,   render::Rgba(255,255,255,255)},

			{10,    10,     0.0f,   0.0f,   render::Rgba(255,255,255,255)},
			{220,   220,    1.0f,   1.0f,   render::Rgba(255,255,255,255)},
			{10,    220,    0.0f,   1.0f,   render::Rgba(255,255,255,255)},
		};

		// _image3->setWrapType(render::IWT_CLAMP);

		static  float   step   =   0;
		for (int i = 0 ;i < 6 ; ++ i )
		{
			vertexs[i].u    +=  step;
		}
		step    +=  0.01f;

		_gRaster.bindTexture(_image3);

		_gRaster.vertexPointer(2,render::DT_FLOAT,      sizeof(Vertex),&vertexs[0].x);
		_gRaster.textureCoordPointer(2,render::DT_FLOAT,sizeof(Vertex),&vertexs[0].u);
		// _gRaster.colorPointer(4,render::DT_UINT8,       sizeof(Vertex),&vertexs[0].color);

		_gRaster.drawArrays(render::DM_TRIANGLES,0,6);
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
