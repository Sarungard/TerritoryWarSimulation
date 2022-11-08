#pragma once
#include <vector>
#include <Vector2.h>

class Core
{
public:
	int Controller;
	Vector2 Start;
	std::vector<Vector2> Positions;

	Core()
	{}

	Core(int c)
	{
		Controller = c;
	}

	inline Core operator + (const Vector2& A)
	{
		this->Positions.push_back(A);
		return *this;
	}

	inline Core operator += (const Vector2& A)
	{
		this->Positions.push_back(A);
		this->Start = A;
		return *this;
	}

	inline Core operator = (const Vector2& A)
	{
		this->Start = A;
		return *this;
	}

private:
};

