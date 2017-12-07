#include "app.h"
#include "math.h"

class Test:	public Application
{
public:
	virtual void render() 
    {
		// draw normal line
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
		_gRaster.drawArrays(render::DM_LINE_STRIP,arPoints,7);

		// draw circle
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

		// draw bezier curve 
		render::Point2f    points[]  =
		{
			render::Point2f(50,50),
			render::Point2f(200,50),
			render::Point2f(33,88),
			render::Point2f(159,100),
		};

		render::Point2f prev[2];
		for (float t = 0.f; t < 1.f; t += 0.01f)
		{
			float x = points[0].x() * pow(1.f - t, 3)
				+ 3 * points[1].x() * pow(1.f - t, 2) * t
				+ 3 * points[2].x() * (1.f - t) * pow(t,2)
				+ points[3].x() * pow(t,3);

			float y = points[0].x() * pow(1.f - t, 3)
				+ 3 * points[1].y() * pow(1.f - t, 2) * t
				+ 3 * points[2].y() * (1.f - t) * pow(t,2)
				+ points[3].y() * pow(t,3);

			if ( t == 0 )
			{
				prev[0] = render::Point2f(x,y);	
			}
			else 
			{
				prev[1] = render::Point2f(x,y);	
				_gRaster.drawArrays(render::DM_LINES, prev, 2);
				prev[0] = prev[1];
			}
				
		}
    }
};

DECLARE_MAIN(Test);
