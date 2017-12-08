#include "app.h"
#include "math.h"
#include "tictoc.h"

#include <stdio.h>

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

		framework::Timestamp ts;

		ts.update();

		for(int32 i = 0; i < 1000; ++i)
			_gRaster.drawTriangle(pt, colors);

		printf("%lld\n", ts.getElapsedMicroSec());
    }
};

DECLARE_MAIN(Test);
