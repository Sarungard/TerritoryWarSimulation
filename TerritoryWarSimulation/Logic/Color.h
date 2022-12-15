#pragma once
#include <SDL.h>

struct Color
{

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

	Color() : r(0), g(0), b(0), a(255) {}

	Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b), a(255) {}

	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}
};