#pragma once
#include <math.h>
#include <string>

struct Vector2
{
private:

	float _x, _y;

public:

	inline Vector2(void) { _x = 0; _y = 0; }
	inline Vector2(const float x, const float y)
	{
		_x = x;
		_y = y;
	}

	inline Vector2(std::string s)
	{
		size_t pos = s.find(",");
		_x = std::stof(s.substr(0, pos)) * 20;
		_y = std::stof(s.erase(0, pos + 1)) * 20;
	}

	inline float X() const
	{
		return _x;
	}

	inline float Y() const
	{
		return _y;
	}

	inline float Dot(const Vector2& A) const
	{
		return (_x* A.X()) + (_y* A.Y());
	}

	inline float Cross(const Vector2& A) const
	{
		return (this->_x* A._y- this->_y* A.X());
	}

	inline float Length() const
	{
		return sqrt((_x * _x + _y * _y));
	}

	inline Vector2 Normalize() const
	{
		float magnitude = this->Length();
		return magnitude > 0 ? Vector2(_x/ magnitude, _y/ magnitude) : Vector2(_x, _y);
	}

	std::string ToString() const
	{
		return "(" + std::to_string(_x) + "," + std::to_string(_y) + ")";
	}

	inline Vector2 operator + (const Vector2& A) const
	{
		return Vector2(_x+ A.X(), _y+ A.Y());
	}

	inline Vector2 operator + (const float A) const
	{
		return Vector2(_x+ A, _y+ A);
	}

	inline Vector2 operator - (const Vector2& A) const
	{
		return Vector2(_x- A.X(), _y- A.Y());
	}

	inline Vector2 operator - (const float A) const
	{
		return Vector2(_x- A, _y- A);
	}
	
	inline float operator * (const Vector2& A) const
	{
		return this->Dot(A);
	}

	inline Vector2 operator * (const float A) const
	{
		return Vector2(_x* A, _y* A);
	}

	inline Vector2 operator / (const float A) const
	{
		return Vector2(_x/ A, _y/ A);
	}

	inline Vector2& operator += (const Vector2& A) 
	{
		this->_x+= A.X();
		this->_y+= A.Y();
		return *this;
	}

	inline Vector2& operator += (const float A)
	{
		this->_x+= A;
		this->_y+= A;
		return *this;
	}

	inline Vector2& operator -= (const Vector2& A)
	{
		this->_x-= A.X();
		this->_y-= A.Y();
		return *this;
	}

	inline Vector2& operator -= (const float A)
	{
		this->_x-= A;
		this->_y-= A;
		return *this;
	}

	inline Vector2& operator *= (const float A)
	{
		this->_x*= A;
		this->_y*= A;
		return *this;
	}

	inline bool operator == (const Vector2& A) const
	{
		return this->_x== A._x&& this->_y== A.Y();
	}

	inline bool operator != (const Vector2& A) const
	{
		return this->_x!= A._x&& this->_y!= A.Y();
	}

	inline bool operator > (const Vector2& A) const
	{
		return this->Length() > A.Length();
	}

	inline bool operator >= (const Vector2& A) const
	{
		return this->Length() >= A.Length();
	}

	inline bool operator < (const Vector2& A) const
	{
		return this->Length() < A.Length();
	}

	inline bool operator <= (const Vector2& A) const
	{
		return this->Length() <= A.Length();
	}
};



