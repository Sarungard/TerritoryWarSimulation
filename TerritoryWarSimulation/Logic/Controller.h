#pragma once
#include <SDL.h>
#include <Color.h>

class Controller
{

private:

	int _id;
	int _numberOfCores;
	int _numberOfTiles;
	Color _color;

public:

	Controller()
	{
		_id = 0;
		_numberOfTiles = 0;
		_color = Color(128, 128, 128, 0);
	}

	Controller(int id, Color color) : _id(id), _color(color), _numberOfCores(4), _numberOfTiles(4) {}

	void GainATile()
	{
		_numberOfTiles++;
	}

	void LoseATile()
	{
		_numberOfTiles--;
	}

	void LoseACore()
	{
		_numberOfCores--;
		_numberOfTiles--;
		//std::cout << _id << " lost a core, " << _numberOfCores << " remaining" << std::endl;
	}

	bool Lost() const
	{
		return _numberOfCores <= 0;
	}

	int GetID() const
	{
		return _id;
	}

	int GetNumberOfCores() const
	{
		return _numberOfCores;
	}

	int GetNumberOfTiles() const
	{
		return _numberOfTiles;
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