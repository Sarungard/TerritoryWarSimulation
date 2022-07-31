#pragma once
#include <Vector2.h>
#include <Shape.h>

class Collision
{
public:
	Shape shapeA;
	Shape shapeB;
	float distance;
	Vector2 vector;
	Vector2 separation;
};

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