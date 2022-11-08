#pragma once
#include <SDL.h>
#include <Color.h>

class Controller
{
private:
	int _id;
	int _numberOfCores;
	bool _isOut;
	Color _color;

public:
	Controller()
	{
		_id = 0;
		_color = Color(128, 128, 128, 0);
	}

	Controller(int id, Color color) : _id(id), _color(color), _numberOfCores(4), _isOut(false) {}

	void LoseACore()
	{
		_numberOfCores--;
		if (_numberOfCores <= 0)
		{
			_isOut = true;
		}
		std::cout << _id << " lost a core, " << _numberOfCores << " remaining" << std::endl;
	}

	bool Lost()
	{
		return _isOut;
	}

	int GetID() const
	{
		return _id;
	}

	int GetNumberOfCores()
	{
		return _numberOfCores;
	}

	Color GetColor() const
	{
		return _color;
	}

	friend bool operator == (const Controller& A, const Controller& B);
	friend bool operator != (const Controller& A, const Controller& B);
};

bool operator == (const Controller& A, const Controller& B)
{
	return A.GetID() == B.GetID();
}

bool operator != (const Controller& A, const Controller& B)
{
	return A.GetID() != B.GetID();
}