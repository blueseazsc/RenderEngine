#include "app.h"
#include "math.h"

class Test:	public Application
{
public:
	virtual void render() 
    {
		for (int32 i = 0; i < 100; ++i)
		{
			_gRaster.drawPoint(rand()%_info.winWidth,rand()%_info.winHeight,render::Rgba(255,0,0),2);
		}
    }
};

DECLARE_MAIN(Test);
