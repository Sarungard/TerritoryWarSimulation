#pragma once
#include <Vector2.h>
#include <Controller.h>
#include <Form.h>
#include <Collision.h>
#include <Color.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <math.h>
#include <cmath>

class Interactable
{
public:
	Interactable(SDL_Renderer* rend, int id, Vector2 pos, Controller controller, Form form, float radius)
	{
		_rend = rend;
		_id = id;
		_position = pos;
		_controller = controller;
		_form = form;
		_radius = radius;
		_color = _controller.GetColor();
		switch (_form)
		{
		case circle:
			_velocity = Vector2(5, 5);
			break;
		case square:
			_destination = new SDL_Rect();
			_velocity = Vector2(NULL, NULL);
			_vertices[0] = _position + Vector2(_radius / 2, _radius / 2);
			_vertices[1] = _position + Vector2(_radius / 2, -1 * _radius / 2);
			_vertices[2] = _position + Vector2(-1 * _radius / 2, -1 * _radius / 2);
			_vertices[3] = _position + Vector2(-1 * _radius / 2, _radius / 2);
			break;
		}
		Render();
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
			_velocity = Vector2(-1 * _velocity.X, _velocity.Y);
		}

		// left boundary
		if (_position.X - 20 <= 0)
		{
			_position.X = 20;
			_velocity = Vector2(-1 * _velocity.X, _velocity.Y);
		}

		// bottom boundary
		if (_position.Y + 20 >= 800)
		{
			_position.Y = 780;
			_velocity = Vector2(_velocity.X, -1 * _velocity.Y);
		}

		// upper boundary
		if (_position.Y - 20 <= 0)
		{
			_position.Y = 20;
			_velocity = Vector2(_velocity.X, -1 * _velocity.Y);
		}
		//std::cout << _id << ": (" << _position.X << "," << _position.Y << ")" << std::endl;
		Render();
	}

	void SolveCollision(Collision c)
	{
		//std::cout << "(" << _velocity.X << "," << _velocity.Y << ")" << std::endl;
		_velocity -= c._separation;
		_velocity.Rotate();
		//std::cout << "(" << _position.X << "," << _position.Y << ")" << std::endl;
		//std::cout << "(" << _velocity.X << "," << _velocity.Y << ")" << std::endl;
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

	bool Intersects(Interactable& other, Collision* collision)
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

	Vector2* GetVertices() const
	{
		static Vector2 vertices[4];
		vertices[0] = _vertices[0];
		vertices[1] = _vertices[1];
		vertices[2] = _vertices[2];
		vertices[3] = _vertices[3];
		return vertices;
	}

	Controller GetController()
	{
		return _controller;
	}

	void ChangeController(Controller _new)
	{
		if (this->_form == square)
		{
			this->_controller = _new;
			this->_color = _controller.GetColor();
		}
	}

	friend bool operator == (const Interactable& A, const Interactable& B);

	friend bool operator == (const Interactable& A, const Interactable& B);

private:
	int _id;
	float _radius;
	Vector2 _vertices[4];
	SDL_Rect* _destination;
	Vector2 _position;
	Vector2 _velocity;
	Controller _controller;
	SDL_Renderer* _rend;
	Color _color;
	Form _form;

	void _renderSquare()
	{	
		_destination->x = _position.X;
		_destination->y = _position.Y;
		_destination->h = _radius;
		_destination->w = _radius;

		SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, _color.a);
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
				SDL_RenderDrawPoint(_rend, _position.X + x, _position.Y - y);
				SDL_RenderDrawPoint(_rend, _position.X + x, _position.Y + y);
				SDL_RenderDrawPoint(_rend, _position.X - x, _position.Y - y);
				SDL_RenderDrawPoint(_rend, _position.X - x, _position.Y + y);
				SDL_RenderDrawPoint(_rend, _position.X + y, _position.Y - x);
				SDL_RenderDrawPoint(_rend, _position.X + y, _position.Y + x);
				SDL_RenderDrawPoint(_rend, _position.X - y, _position.Y - x);
				SDL_RenderDrawPoint(_rend, _position.X - y, _position.Y + x);

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
	/*
	bool _intersectsSquare(Interactable other, Collision* collision) const
	{
		float shortestDist = std::numeric_limits<float>::max();
		Vector2* verts = other.GetVertices();
		Vector2 vOffset = Vector2(other.GetPosition().X - this->_position.X, other.GetPosition().Y - this->_position.Y);
		Vector2 closest = Vector2(0,0);

		for (int i = 0; i < 4; ++i)
		{
			//std::cout << verts[i].ToString();
			float dist = sqrt(pow(this->_position.X - (other.GetPosition().X + verts[i].X), 2) + pow(this->_position.Y - (other.GetPosition().Y + verts[i].Y), 2));
			if (dist < shortestDist)
			{
				shortestDist = dist;
				closest = Vector2(verts[i] + other.GetPosition());
			}
		}		
		Vector2 axis = Vector2(closest.X - this->_position.X, closest.Y - this->_position.Y);

		float pMin = axis.Dot(verts[0]);
		float pMax = pMin;
		for (int i = 1; i < 4; ++i)
		{
			float tmp = axis.Dot(verts[i]);
			if (tmp < pMin) pMin = tmp;
			if (tmp > pMax) pMax = tmp;
		}

		float sOffset = axis.Dot(vOffset);
		pMin += sOffset;
		pMax += sOffset;

		float projection = axis.Dot(Vector2(0,0));
		float cMin = projection - this->_radius;
		float cMax = projection + this->_radius;

		if ((pMin - cMax > 0) || (cMin - pMax > 0))
		{
			return false;
		}
		
		float distMin = cMax - pMin;


		shortestDist = abs(distMin);

		collision->_distance = distMin;
		collision->_vector = axis;

		for (int i = 0; i < 4; ++i)
		{
			Vector2 pt1 = verts[i];
			Vector2 pt2 = i >= 3 ? verts[0] : verts[i+1];

			axis = Vector2(-1*(pt2.Y - pt1.Y), pt2.X - pt1.X);

			for (int i = 0; i < 4; ++i)
			{
				float tmp = axis.Dot(verts[i]);
				if (tmp < pMin) pMin = tmp;
				if (tmp > pMax) pMax = tmp;
			}

			sOffset = axis.Dot(vOffset);
			pMin += sOffset;
			pMax += sOffset;

			cMin = projection - this->_radius;
			cMax = projection + this->_radius;

			if ((pMin - cMax > 0) || (cMin - pMax > 0))
			{
				return false;
			}

			distMin = (cMax - pMin);
			float distMinAbs = abs(distMin);
			if (distMinAbs < shortestDist)
			{
				shortestDist = abs(distMin);

				collision->_distance = distMin;
				collision->_vector = axis;
			}
		}
		collision->_separation = Vector2(collision->_vector.X * collision->_distance/100000, collision->_vector.Y * collision->_distance/100000);
		//std::cout << collision->_separation.Length() << std::endl;
		
		return true;
	}
	*/
	bool _intersectsSquare(Interactable other, Collision* collision) const
	{
		const float tr = other._radius/2 + this->_radius;
		const float d = sqrt(pow(this->_position.X - other._position.X, 2) + pow(this->_position.Y - other._position.Y, 2));
		if (d > tr) return false;
		collision = new Collision(d, tr, Vector2(this->_position.X - other._position.X, this->_position.Y - other._position.Y));
		return true;
	}

	bool _intersectsCircle(Interactable other, Collision* collision) const
	{
		const float tr = other._radius + this->_radius;
		const float d = sqrt(pow(this->_position.X - other._position.X, 2) + pow(this->_position.Y - other._position.Y, 2));
		if (d > tr) return false;
		collision = new Collision(d, tr, Vector2(this->_position.X - other._position.X, this->_position.Y - other._position.Y));
		return true;
	}
};

bool operator == (const Interactable& A, const Interactable& B)
{
	return A.GetID() == B.GetID();
}

bool operator != (const Interactable& A, const Interactable& B)
{
	return A.GetID() != B.GetID();
}

struct Transform
{
	Vector2 _position;
	Vector2 Scale;
	float Rotation;
};

