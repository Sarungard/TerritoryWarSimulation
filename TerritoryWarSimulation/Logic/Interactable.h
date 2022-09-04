#pragma once
#include <Vector2.h>
#include <Shape.h>
#include <Circle.h>
#include <Square.h>
#include <Controller.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Interactable
{
public:
	Interactable(SDL_Renderer* rend, int id, Controller controller, int form)
	{
		_id = id;

		_position = Vector2(200+rand() % (controller.GetID()+1) + _id, 200 + rand() % (controller.GetID() + 1) + _id);
		_velocity = Vector2(9, 11);
		_controller = controller;
		if (form == 1)
		{
			_shape = new Circle(rend, _position, 20, _controller.GetColor());
		}
		else
		{
			_shape = new Square(_position, 20);
		}
		_shape->Render(rend, _position);
	}

	~Interactable()
	{
		
	}


	void Step(SDL_Renderer* rend)
	{
		_position += _velocity;
		// right boundary
		if (_position.X + 20 >= 800)
		{
			_position.X = 780;
			_velocity = Vector2(-1 * (_velocity.X + rand() % 10 - 5), _velocity.Y);
		}

		// left boundary
		if (_position.X - 20 <= 0)
		{
			_position.X = 20;
			_velocity = Vector2(-1 * (_velocity.X + rand() % 10 - 5), _velocity.Y);
		}

		// bottom boundary
		if (_position.Y + 20 >= 800)
		{
			_position.Y = 780;
			_velocity = Vector2(_velocity.X, -1 * (_velocity.Y + rand() % 10 - 5));
		}

		// upper boundary
		if (_position.Y - 20 <= 0)
		{
			_position.Y = 20;
			_velocity = Vector2(_velocity.X, -1 * (_velocity.Y + rand() % 10 - 5));
		}
		std::cout << _id << ": (" << _position.X << "," << _position.Y << ")" << std::endl;
		_shape->Render(rend, _position);
	}

	int GetID() const
	{
		return _id;
	}

	Shape* GetShape() const
	{
		return _shape;
	}

	friend bool operator == (const Interactable& A, const Interactable& B);

private:
	int _id;
	Vector2 _position;
	Vector2 _velocity;
	Shape* _shape;
	Controller _controller;
};

bool operator == (const Interactable& A, const Interactable& B)
{
	return A.GetID() == B.GetID();
}

struct Transform
{
	Vector2 _position;
	Vector2 Scale;
	float Rotation;
};

