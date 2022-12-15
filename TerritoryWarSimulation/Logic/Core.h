#pragma once
#include <vector>
#include <Vector2.h>

class Core
{

private:

	int _controller;
	Vector2 _start;
	std::vector<Vector2> _positions;

public:

	Core()
	{}

	Core(int c)
	{
		_controller = c;
	}

	int Controller() const
	{
		return _controller;
	}

	Vector2 Start() const
	{
		return _start;
	}

	std::vector<Vector2> Positions() const
	{
		return _positions;
	}

	inline Core operator + (const Vector2& A)
	{
		this->_positions.push_back(A);
		return *this;
	}

	inline Core operator += (const Vector2& A)
	{
		this->_positions.push_back(A);
		this->_start = A;
		return *this;
	}

	inline Core operator = (const Vector2& A)
	{
		this->_start = A;
		return *this;
	}
};

