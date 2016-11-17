#ifndef _COLOR_H
#define _COLOR_H

struct Colour
{
	float r;
	float g;
	float b;
	float a;

	Colour()
		: r(0)
		, g(0)
		, b(0)
		, a(0)
	{}

	Colour(float r, float g, float b, float a = 1.0f)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{}

	Colour(const Colour& c)
		:r(c.r)
		, g(c.r)
		, b(c.b)
		, a(c.a)
	{}
};

#endif //_COLOR_H