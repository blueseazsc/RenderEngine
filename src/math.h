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

typedef Eigen::Vector4f Vector4f;
typedef Eigen::Vector3f Vector3f;
typedef Eigen::Vector2f Vector2f;

typedef Eigen::Vector4f Point4f;
typedef Eigen::Vector3f Point3f;
typedef Eigen::Vector2f Point2f;
typedef Eigen::Vector2i Point2i;

typedef Eigen::Matrix3f Matrix3f;
typedef Eigen::Matrix4f Matrix4f;

#define Matrix3fIdentity Eigen::Matrix3f::Identity()
#define Matrix4fIdentity Eigen::Matrix4f::Identity()
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
// 2D
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
// 3D
inline void genTranslate(Matrix4f& mat, float x, float y, float z)
{
	mat = Matrix4fIdentity;
	mat(0,3) = x;
	mat(1,3) = y;
	mat(2,3) = z;
}
inline void genRotateX(Matrix4f& mat, float angle)
{
	mat = Matrix4fIdentity;
	float   rad   =   DEG2RAD(angle);
	float   c     =   cos(rad);
	float   s     =   sin(rad);
	mat(1,1) = c;
	mat(1,2) = -s;
	mat(2,1) = s;
	mat(2,2) = c;
}
inline void genRotateY(Matrix4f& mat, float angle)
{
	mat = Matrix4fIdentity;
	float   rad   =   DEG2RAD(angle);
	float   c     =   cos(rad);
	float   s     =   sin(rad);
	mat(0,0) = c;
	mat(0,2) = s;
	mat(2,0) = -s;
	mat(2,2) = c;
}
inline void genRotateZ(Matrix4f& mat, float angle)
{
	mat = Matrix4fIdentity;
	float   rad   =   DEG2RAD(angle);
	float   c     =   cos(rad);
	float   s     =   sin(rad);
	mat(0,0) = c;
	mat(0,1) = -s;
	mat(1,0) = s;
	mat(1,1) = c;
}
inline void genScale(Matrix4f& mat, float scaleX, float scaleY, float scaleZ)
{
	mat = Matrix4fIdentity;
	mat(0,0) = scaleX;
	mat(1,1) = scaleY;
	mat(2,2) = scaleZ;
}
inline void genLookat(Matrix4f& mat, const Vector3f& eye, const Vector3f& center, const Vector3f& upRef)
{
	Vector3f forward = eye - center;
	forward.normalize();
	Vector3f up = upRef;
	up.normalize();
	Vector3f side = forward.cross(up);
	side.normalize();
	up = side.cross(forward);

	mat = Matrix4fIdentity;

	mat(0,0) = side.x();
	mat(0,1) = side.y();
	mat(0,2) = side.z();

	mat(1,0) = up.x();
	mat(1,1) = up.y();
	mat(1,2) = up.z();

	mat(2,0) = forward.x();
	mat(2,1) = forward.y();
	mat(2,2) = forward.z();

	mat(3,0) = -side.dot(eye);
	mat(3,1) = -up.dot(eye);
	mat(3,2) = forward.dot(eye);
}
inline void genProjection(Matrix4f& mat, float fovy, float aspect, float zNear, float zFar)
{
	float range   =   tan( DEG2RAD(fovy * 0.5f) ) * zNear;
	float left    =   - range * aspect;
	float right   =   range * aspect;
	float bottom  =   - range;
	float top     =   range;

	mat = Matrix4fIdentity;
	mat(0,0) = (2.f * zNear) / (right - left);
	mat(1,1) = (2.f * zNear) / (top - bottom);
	mat(2,2) = - (zFar + zNear) / (zFar - zNear);
	mat(3,3) = 0.f;

	mat(0,2) = (right + left) / (right - left);
	mat(1,2) = (top + bottom) / (top - bottom);

	mat(3,2) = - 1.f;
	mat(2,3) = - (2.f * zFar * zNear) / (zFar - zNear);
}
}
#endif
