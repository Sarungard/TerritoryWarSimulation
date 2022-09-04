#pragma once
#include <Shape.h>
#include <SDL.h>
class Square : public Shape
{
	float _edge;
	Vector2 _vertices[4];
	SDL_Rect _destination;

public:
	Square()
	{
		_center = Vector2(400, 400);
		_edge = 20;
		_vertices[0] = _center + Vector2(_edge / 2, _edge / 2);
		_vertices[1] = _center + Vector2(_edge / 2, -1 * _edge / 2);
		_vertices[2] = _center + Vector2(-1 * _edge / 2, -1 * _edge / 2);
		_vertices[3] = _center + Vector2(-1 * _edge / 2, _edge / 2);
	}

	Square(float e)
	{
		_center = Vector2(400, 400);
		_edge = e;
		_vertices[0] = _center + Vector2(_edge / 2, _edge / 2);
		_vertices[1] = _center + Vector2(_edge / 2, -1 * _edge / 2);
		_vertices[2] = _center + Vector2(-1 * _edge / 2, -1 * _edge / 2);
		_vertices[3] = _center + Vector2(-1 * _edge / 2, _edge / 2);
	}

	Square(Vector2 c)
	{
		_center = c;
		_edge = 20;
		_vertices[0] = _center + Vector2(_edge / 2, _edge / 2);
		_vertices[1] = _center + Vector2(_edge / 2, -1 * _edge / 2);
		_vertices[2] = _center + Vector2(-1 * _edge / 2, -1 * _edge / 2);
		_vertices[3] = _center + Vector2(-1 * _edge / 2, _edge / 2);
	}

	Square(Vector2 c, float e)
	{
		_center = c;
		_edge = e;
		_vertices[0] = _center + Vector2(_edge / 2, _edge / 2);
		_vertices[1] = _center + Vector2(_edge / 2, -1 * _edge / 2);
		_vertices[2] = _center + Vector2(-1 * _edge / 2, -1 * _edge / 2);
		_vertices[3] = _center + Vector2(-1 * _edge / 2, _edge / 2);
	}
};

