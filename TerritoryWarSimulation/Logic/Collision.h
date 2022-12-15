#ifndef includeCollision
#define includeCollision

#include <Vector2.h>

class Collision
{

private:

	int _id;
	Vector2 _newVelocity;

public:

	Collision()
	{

	}

	Collision(int id, Vector2 v)
	{
		_id = id;
		_newVelocity = v;
	}

	int GetId() const
	{
		return _id;
	}

	Vector2 GetVelocity() const
	{
		return _newVelocity;
	}
};
#endif