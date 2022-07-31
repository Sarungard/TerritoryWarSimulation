#pragma once
#include <Vector2.h>
#include <SDL.h>
#include <Collision.h>
#include <math.h>

class Shape
{
public:
	Vector2 center;
};

class Circle : Shape
{
	float radius;

	Collision* Intersects(Square other) const
	{

	}

	Collision* Intersects(Circle other) const
	{
		const float tr = other.radius + this->radius;
		const float d = sqrt(pow(this->center.X - other.center.X, 2) + pow(this->center.Y - other.center.Y, 2));
		if (d > tr) return NULL;
		Collision c;
		Collision* result = &c;
		result->shapeA = other;
		result->shapeB = *this;
		result->vector = Vector2(this->center.X - other.center.X, this->center.Y - other.center.Y);
		result->distance = d;
		result->separation = Vector2(result->vector.X * tr - d, result->vector.Y * tr - d);
		return result;
	}
};

class Square : Shape
{
	float edge;
	Vector2 vertices[4];

	Square()
	{
		center = Vector2(0, 0);
		edge = 1;
		vertices[0] = center + Vector2(edge / 2, edge / 2);
		vertices[1] = center + Vector2(edge / 2, -1 * edge / 2);
		vertices[2] = center + Vector2(-1 * edge / 2, -1 * edge / 2);
		vertices[3] = center + Vector2(-1 * edge / 2, edge / 2);
	}

	Square(float e)
	{
		center = Vector2(0, 0);
		edge = e;
		vertices[0] = center + Vector2(edge / 2, edge / 2);
		vertices[1] = center + Vector2(edge / 2, -1 * edge / 2);
		vertices[2] = center + Vector2(-1 * edge / 2, -1 * edge / 2);
		vertices[3] = center + Vector2(-1 * edge / 2, edge / 2);
	}

	Square(Vector2 c)
	{
		center = c;
		edge = 1;
		vertices[0] = center + Vector2(edge / 2, edge / 2);
		vertices[1] = center + Vector2(edge / 2, -1 * edge / 2);
		vertices[2] = center + Vector2(-1 * edge / 2, -1 * edge / 2);
		vertices[3] = center + Vector2(-1 * edge / 2, edge / 2);
	}

	Square(Vector2 c, float e)
	{
		center = c;
		edge = e;
		vertices[0] = center + Vector2(edge / 2, edge / 2);
		vertices[1] = center + Vector2(edge / 2, -1 * edge / 2);
		vertices[2] = center + Vector2(-1 * edge / 2, -1 * edge / 2);
		vertices[3] = center + Vector2(-1 * edge / 2, edge / 2);
	}
};