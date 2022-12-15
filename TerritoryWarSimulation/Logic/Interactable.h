#pragma once
#include <Controller.h>
#include <Form.h>
#include <Collision.h>
#include <SDL.h>
#include <string>
#include <math.h>
#include <cmath>

class Interactable
{

private:

	int _id;
	float _radius;
	bool _core;
	float _speed;
	SDL_Rect* _destination;
	Vector2 _position;
	Vector2 _velocity;
	Controller* _controller;
	SDL_Renderer* _rend;
	Color _color;
	Form _form;

	void _renderSquare()
	{
		_destination->x = _position.X();
		_destination->y = _position.Y();
		_destination->h = _radius;
		_destination->w = _radius;

		if (_core)
		{
			SDL_SetRenderDrawColor(_rend, 0.8 * _color.r, 0.8 * _color.g, 0.8 * _color.b, 100);
		}
		else
		{
			SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, _color.a);
		}

		SDL_RenderFillRect(_rend, _destination);
		SDL_SetRenderDrawColor(_rend, 80, 80, 80, 200);
		SDL_RenderDrawRect(_rend, _destination);
		SDL_SetRenderDrawColor(_rend, 0, 0, 0, 255);
	}

	void _renderCircle()
	{
		float r = _radius;
		while (r > 0)
		{
			const int32_t diameter = (r * 2);

			int32_t x = (r - 1);
			int32_t y = 0;
			int32_t tx = 1;
			int32_t ty = 1;
			int32_t error = (tx - diameter);

			r == _radius ? SDL_SetRenderDrawColor(_rend, 0, 0, 0, 255) : SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, 255);

			while (x >= y)
			{
				//  Each of the following renders an octant of the circle
				SDL_RenderDrawPoint(_rend, _position.X() + x, _position.Y() - y);
				SDL_RenderDrawPoint(_rend, _position.X() + x, _position.Y() + y);
				SDL_RenderDrawPoint(_rend, _position.X() - x, _position.Y() - y);
				SDL_RenderDrawPoint(_rend, _position.X() - x, _position.Y() + y);
				SDL_RenderDrawPoint(_rend, _position.X() + y, _position.Y() - x);
				SDL_RenderDrawPoint(_rend, _position.X() + y, _position.Y() + x);
				SDL_RenderDrawPoint(_rend, _position.X() - y, _position.Y() - x);
				SDL_RenderDrawPoint(_rend, _position.X() - y, _position.Y() + x);

				if (error <= 0)
				{
					++y;
					error += ty;
					ty += 2;
				}

				if (error > 0)
				{
					--x;
					tx += 2;
					error += (tx - diameter);
				}
			}
			--r;
		}
		SDL_SetRenderDrawColor(_rend, 0, 0, 0, 255);
	}

	bool _intersectsSquare(Interactable other, Collision& collision) const
	{
		const float tr = other._radius / 2 + this->_radius;
		const float d = (this->_position - other._position).Length();
		if (d > tr) return false;
		Vector2 separation = Vector2(this->_position - other._position).Normalize() * _speed;
		collision = Collision(this->GetID(), separation);
		return true;
	}

	bool _intersectsCircle(Interactable other, Collision& collision) const
	{
		const float tr = other._radius + this->_radius;
		const float d = sqrt(pow(this->_position.X() - other._position.X(), 2) + pow(this->_position.Y() - other._position.Y(), 2));
		if (d > tr) return false;
		Vector2 separation = Vector2(this->_position - other._position).Normalize() * _speed;
		collision = Collision(this->GetID(), separation);
		return true;
	}

public:

	Interactable(SDL_Renderer* rend, int id, Vector2 pos, Controller& controller, Form form, float radius, bool core = false)
	{
		_rend = rend;
		_id = id;
		_position = pos;
		_controller = &controller;
		_form = form;
		_radius = radius;
		_color = _controller->GetColor();
		_core = core;
		switch (_form)
		{
		case circle:
		{
			_speed = 5.0;
			_velocity = Vector2(_speed * sin(rand() % time(NULL) + SDL_GetTicks()), _speed * sin(rand() % time(NULL) + SDL_GetTicks()));
			break;
		}
		case square:
		{
			_destination = new SDL_Rect();
			_velocity = Vector2(NULL, NULL);
			break;
		}
		}
		Render();
	}

	Interactable(int id, Vector2 pos, Controller& controller, Form form, float radius, bool core = false)
	{
		_id = id;
		_position = pos;
		_controller = &controller;
		_form = form;
		_radius = radius;
		_color = _controller->GetColor();
		_core = core;
		switch (_form)
		{
		case circle:
		{
			_speed = 5.0;
			_velocity = Vector2(_speed * sin(rand() % time(NULL) + SDL_GetTicks()), _speed * sin(rand() % time(NULL) + SDL_GetTicks()));
			break;
		}
		case square:
		{
			_destination = new SDL_Rect();
			_velocity = Vector2(NULL, NULL);
			break;
		}
		}
		Render();
	}

	~Interactable()
	{

	}

	void Step(float bottom, float right)
	{
		_position += _velocity;
		// right boundary
		if (_position.X() > bottom)
		{
			_velocity = Vector2( - 0.5 * Vector2(_position - Vector2(bottom, 0)).X() * _speed, _velocity.Y());
			_position = Vector2(bottom - _radius, _position.Y());
		}

		// left boundary
		if (_position.X() < 0)
		{
			_velocity = Vector2( - 0.5 * _position.X() * _speed, _velocity.Y());
			_position = Vector2(0 + _radius, _position.Y());
		}

		// bottom boundary
		if (_position.Y() > right)
		{
			_velocity = Vector2(_velocity.X(), - 0.5 * Vector2(_position - Vector2(0, right)).Y() * _speed);
			_position = Vector2(_position.X(), right - _radius);
		}

		// upper boundary
		if (_position.Y() < 0)
		{
			_velocity = Vector2(_velocity.X(), - 0.5 * _position.Y() * _speed);
			_position = Vector2(_position.X(), 0 + _radius);
		}

		Render();
	}

	void SolveCollision(Vector2 velocity)
	{
		_velocity = velocity;
	}

	void Render()
	{
		if (_form == circle)
		{
			_renderCircle();
		}
		else
		{
			_renderSquare();
		}
	}

	void ChangeController(Controller* _new)
	{
		if (this->_form == square)
		{
			if (this->_core)
			{
				this->_controller->LoseACore();
				this->_core = false;
			}
			else
			{
				this->_controller->LoseATile();
			}
			this->_controller = _new;
			this->_color = _controller->GetColor();
		}
	}

	bool Intersects(Interactable& other, Collision& collision)
	{
		switch (other.GetForm())
		{
		case 0:
			return _intersectsSquare(other, collision);
		case 1:
			return _intersectsCircle(other, collision);
		default:
			return NULL;
		}
	}

	Form GetForm() const
	{
		return _form;
	}

	int GetID() const
	{
		return _id;
	}

	float GetSize() const
	{
		if (_form == circle)
		{
			return _radius;
		}
		else
		{
			return sqrt(2*pow(_radius,2));
		}
	}

	Vector2 GetPosition() const
	{
		return _position;
	}

	Controller* GetController() const
	{
		return _controller;
	}

	friend bool operator == (const Interactable& A, const Interactable& B);

	friend bool operator == (const Interactable& A, const Interactable& B);

};

bool operator == (const Interactable& A, const Interactable& B)
{
	return A.GetID() == B.GetID();
}

bool operator != (const Interactable& A, const Interactable& B)
{
	return A.GetID() != B.GetID();
}

