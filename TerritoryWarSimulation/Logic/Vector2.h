#pragma once
#include <math.h>
struct Vector2
{
	float X, Y;
	inline Vector2(void) { X = 0; Y = 0; }
	inline Vector2(const float x, const float y)
	{
		X = x;
		Y = y;
	}

	inline Vector2 operator + (const Vector2& A) const
	{
		return Vector2(X + A.X, Y + A.Y);
	}

	inline Vector2 operator + (const float A) const
	{
		return Vector2(X + A, Y + A);
	}

	inline Vector2 operator * (const float A) const
	{
		return Vector2(X * A, Y * A);
	}

	inline Vector2 operator / (const float A) const
	{
		return Vector2(X / A, Y / A);
	}

	inline Vector2& operator += (const Vector2& A) 
	{
		this->X += A.X;
		this->Y += A.X;
		return *this;
	}

	inline Vector2& operator += (const float A)
	{
		this->X += A;
		this->Y += A;
		return *this;
	}

	inline bool operator == (const Vector2& A)
	{
		return this->X == A.X && this->Y == A.Y;
	}

	inline bool operator > (const Vector2& A)
	{
		return this->Length() > A.Length();
	}

	inline bool operator >= (const Vector2& A)
	{
		return this->Length() >= A.Length();
	}

	inline bool operator < (const Vector2& A)
	{
		return this->Length() < A.Length();
	}

	inline bool operator <= (const Vector2& A)
	{
		return this->Length() <= A.Length();
	}

	inline float Dot(const Vector2& A) const
	{
		return X * A.X + Y * A.Y;
	}

	inline float Length() const
	{
		return sqrt((X*X + Y*Y));
	}
};



