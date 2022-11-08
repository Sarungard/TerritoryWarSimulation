#ifndef includeCollision
#define includeCollision

class Collision
{

public:

	float _distance;
	Vector2 _vector;
	Vector2 _separation;

	Collision()
	{

	}

	Collision(float d, float tr, Vector2 v)
	{
		_distance = d;
		_vector = v;
		_separation = Vector2(_vector.X * (tr - d), _vector.Y * (tr - d));
	}
};
#endif // !includeCollision
/*
struct CollisionPoints
{
	Vector2 A;
	Vector2 B;
	Vector2 normal;
	float Depth;
	bool hasCollision;
};

struct ContactPoint
{
	Vector2 Position;
	float Penetration;
};

struct ContactManifold
{
	int PointCount;
	ContactPoint Points[2];
	Vector2 Normal;
};
*/