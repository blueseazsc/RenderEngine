#include "app.h"
#include "math.h"

class Test:	public Application
{
public:
	virtual void render() 
    {
		render::Point2i pt[]    =
		{
			render::Point2i(100,10),
			render::Point2i(10,100),
			render::Point2i(200,100),
		};

		render::Rgba  colors[]    =
		{
			render::Rgba(255,0,0),
			render::Rgba(0,255,0),
			render::Rgba(0,0,255),

		};

		_gRaster.drawTriangle(pt, colors);
    }
};

DECLARE_MAIN(Test);
