#include "app.h"
#include "math.h"

class Test:	public Application
{
public:
	virtual void render() 
    {
		render::Point2f arPoints[]  =
		{
			render::Point2f(11,534),
			render::Point2f(311,534),
			render::Point2f(311,35),
			render::Point2f(33,1),
			render::Point2f(1,100),
			render::Point2f(22,88),
			render::Point2f(100,1),
		};
		// _gRaster.drawArrays(render::DM_POINTS,arPoints,3);
		_gRaster.drawArrays(render::DM_LINE_STRIP,arPoints,7);

		render::Point2f center(200,200);

		float           radius  =   80;

		render::Point2f arCircle[360];
		for (int i = 0 ;i < 360 ; ++ i)
		{
			float   rad     =   DEG2RAD(i);
			arCircle[i].x()   =   radius * cos(rad) + center.x();
			arCircle[i].y()   =   radius * sin(rad) + center.y();
		}
		_gRaster.drawArrays(render::DM_LINE_LOOP,arCircle,360);
    }
};

DECLARE_MAIN(Test);
