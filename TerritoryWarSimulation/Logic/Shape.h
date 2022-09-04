#pragma once
#include <Vector2.h>
#include <math.h>

class Shape
{
protected:
	Vector2 _center;

public:
	virtual void Render(SDL_Renderer* rend, Vector2 position)
	{
		std::cout << "Wrong";
	}
};