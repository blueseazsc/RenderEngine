#ifndef RENDER_MATH_H 
#define RENDER_MATH_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "config.h"

namespace render {

#define PI                      3.14159265358979323
#define TWO_PI                  6.28318530717958647
#define HALF_PI                 1.57079632679489661
#define DEG2RAD(theta)          (0.01745329251994329 * (theta))

typedef Eigen::Vector3f Point3f;
typedef Eigen::Vector2f Point2f;
typedef Eigen::Vector2i Point2i;
typedef Eigen::Matrix3f Matrix3f;

#define Matrix3fIdentity Eigen::Matrix3f::Identity()
class Rgba4Byte {
public:
	Rgba4Byte(
			uint8 r = 255,
			uint8 g = 255,
			uint8 b = 255,
			uint8 a = 255
			)
	{
		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}
	Rgba4Byte(uint32 color)
	{
		_color = color;
	}
	friend bool operator == (const Rgba4Byte& left, const Rgba4Byte& right) 
	{
		return left._r == right._r
			&& left._g == right._g
			&& left._b == right._b
			&& left._a == right._a
			;
	}
	friend bool operator != (const Rgba4Byte& left, const Rgba4Byte& right) 
	{
		return left._r != right._r
			|| left._g != right._g
			|| left._b != right._b
			|| left._a != right._a
			;
	}
	friend Rgba4Byte operator + (const Rgba4Byte& left, const Rgba4Byte& right)
	{
		return Rgba4Byte(
				left._r + right._r,
				left._g + right._g,
				left._b + right._b,
				left._a + right._a
				);
	}
public:
	union {
		struct {
			uint8 _a;
			uint8 _b;
			uint8 _g;
			uint8 _r;
		};
		uint32 _color;
	};
};
typedef Rgba4Byte Rgba;

inline Rgba4Byte colorLerp(const Rgba4Byte& c1, const Rgba4Byte& c2, float s)
{
	Rgba4Byte color;
	color._r = (uint8)(c1._r + s * ( c2._r - c1._r ));
	color._g = (uint8)(c1._g + s * ( c2._g - c1._g ));
	color._b = (uint8)(c1._b + s * ( c2._b - c1._b ));
	color._a = (uint8)(c1._a + s * ( c2._a - c1._a ));
	return color;
}
inline Point2f uvLerp(const Point2f& p1, const Point2f& p2, float s)
{
	Point2f uv;
	uv.x() = (p1.x() + s * ( p2.x() - p1.x() ));
	uv.y() = (p1.y() + s * ( p2.y() - p1.y() ));
	return uv;
}

inline void genTranslate2D(Matrix3f& mat, float x, float y)
{
	mat = Matrix3fIdentity;
	mat(0,2) = x;
	mat(1,2) = y;
}
inline void genRotate2D(Matrix3f& mat, float angle)
{
	mat = Matrix3fIdentity;
	float   rad   =   DEG2RAD(angle);
	float   c     =   cos(rad);
	float   s     =   sin(rad);
	mat(0,0) = c;
	mat(0,1) = -s;
	mat(1,0) = s;
	mat(1,1) = c;
}
inline void genScale2D(Matrix3f& mat, float scaleX, float scaleY)
{
	mat = Matrix3fIdentity;
	mat(0,0) = scaleX;
	mat(1,1) = scaleY;
}

}
#endif
