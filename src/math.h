#ifndef RENDER_MATH_H 
#define RENDER_MATH_H

#include "config.h"

namespace render {

class Rgba4Byte {
public:
	Rgba4Byte(
			uint8_t r = 255,
			uint8_t g = 255,
			uint8_t b = 255,
			uint8_t a = 255
			)
	{
		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}
	friend bool operator = (const Rgba4Byte& left, const Rgba4Byte& right) 
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
	uint8_t _r;
	uint8_t _g;
	uint8_t _b;
	uint8_t _a;
};
typedef Rgba4Byte Rgba;
}
#endif
