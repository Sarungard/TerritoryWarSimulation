#pragma once
#include <Vector2.h>
#include <Shape.h>

struct Interactable
{
	Vector2 Position;
	Vector2 Velocity;
	Shape shape;
};

struct Transform
{
	Vector2 Position;
	Vector2 Scale;
	float Rotation;
};