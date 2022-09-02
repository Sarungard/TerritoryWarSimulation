#pragma once
#include "Shape.h"
#include "Square.h"
#include "Collision.h"
#include <math.h>
#include <limits>

class Circle :
    public Shape
{
private:
	float radius;

public:
	bool Intersects(Square other, Collision* collision) const
	{
		constexpr float shortestDist = std::numeric_limits<float>::max();
	}

	bool Intersects(Circle other, Collision* collision) const
	{
		const float tr = other.radius + this->radius;
		const float d = sqrt(pow(this->center.X - other.center.X, 2) + pow(this->center.Y - other.center.Y, 2));
		if (d > tr) return false;
		collision = new Collision(other, *this, d, tr, Vector2(this->center.X - other.center.X, this->center.Y - other.center.Y));
		return true;
	}
};

