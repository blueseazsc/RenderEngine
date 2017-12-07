#include "app.h"
#include "math.h"

class Test:	public Application
{
public:
	virtual void render() 
    {
		_gRaster.drawFilleRect(700,550,200,200);
		render::Point2i pt[]    =
		{
			render::Point2i(10,10),
			render::Point2i(110,10),
			render::Point2i(110,110),
			render::Point2i(10,110),
		};

		render::Rgba  colors[]    =
		{
			render::Rgba (255,0,0),
			render::Rgba (0,255,0),
			render::Rgba (0,0,255),
			render::Rgba (255,255,255),

		};

		_gRaster.drawRect(pt,colors);
    }
};

DECLARE_MAIN(Test);
