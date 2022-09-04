#pragma once
#include <SDL.h>
#include <Color.h>

class Controller
{
private:
	int _id;
	Color _color;

public:
	Controller()
	{
		_id = 0;
		_color = Color(128, 128, 128, 0);
	}

	Controller(int id, Color color) : _id(id), _color(color) {}

	int GetID() const
	{
		return _id;
	}

	Color GetColor() const
	{
		return _color;
	}

	friend bool operator == (const Controller& A, const Controller& B);
};

bool operator == (const Controller& A, const Controller& B)
{
	return A.GetID() == B.GetID();
}