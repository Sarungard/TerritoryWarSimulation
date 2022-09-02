#pragma once
#include "Shape.h"
class Square :
    public Shape
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

