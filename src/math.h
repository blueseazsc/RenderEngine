#ifndef RENDER_MATH_H 
#define RENDER_MATH_H

#include "config.h"

namespace render {

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
	uint32_t toUint32() const 
	{
		return (_b) | (_g << 8) | (_r << 16) | (_a << 24);
	}
public:
	uint8 _r;
	uint8 _g;
	uint8 _b;
	uint8 _a;
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
}
#endif
