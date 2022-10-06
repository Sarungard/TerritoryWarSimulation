#pragma once
#include <vector>
#include <Vector2.h>
#include <Interactable.h>
#include <Form.h>
#include <Controller.h>
#include <Collision.h>
#include <math.h>

class World
{
private:
	std::vector<std::reference_wrapper<Interactable> > staticWorldObjects;
	std::vector<std::reference_wrapper<Interactable> > dynamicWorldObjects;
	std::vector<std::reference_wrapper<Controller> > controllers;
	SDL_Renderer* _rend;
	int _id;
	int _cid;
	Color _colors[9] = {
		{100, 100, 100},
		{255, 0, 0},
		{0, 255, 0},
		{0, 0, 255},
		{255, 255, 0},
		{255, 0, 255},
		{0, 255, 255},
		{128, 0, 128},
		{0, 128, 128}
	};

public:

	World()
	{

	}

	World(SDL_Renderer* rend)
	{
		_id = 0;
		_cid = 8;
		_rend = rend;
		SDL_RenderClear(_rend);
		SDL_SetRenderDrawColor(_rend, 0, 0, 0, 255);
		for (int i = 0; i <= _cid; ++i)
		{
			Controller* obj = new Controller(i, _colors[i]);
			std::reference_wrapper<Controller> cont = *obj;
			controllers.push_back(cont);
		}
		for (int i = 0; i < 40; ++i)
		{
			for (int j = 0; j < 40; ++j)
			{
				if ((i * 20) % 100 == 0 && i == j)
				{
					std::cout << i << " ping " << j << std::endl;
					AddStaticObject(new Interactable(_rend, ++_id, Vector2(i * 20, j * 20), controllers[i / 5 + 1], square, 20));
				}
				AddStaticObject(new Interactable(_rend, ++_id, Vector2(i * 20, j * 20), controllers.front(), square, 20));
			}
		}
		for (Controller& obj : controllers)
		{
			if (obj.GetID() != 0)
			AddDynamicObject(new Interactable(_rend, ++_id, Vector2(obj.GetID() * 100, obj.GetID() * 100), obj, circle, 10));
		}
	}	

	void AddStaticObject(Interactable* object)
	{
		std::reference_wrapper<Interactable> obj = *object;
		staticWorldObjects.push_back(obj);
	}

	void AddDynamicObject(Interactable* object)
	{
		std::reference_wrapper<Interactable> obj = *object;
		dynamicWorldObjects.push_back(obj);
	}

	void RemoveObject(Interactable &object)
	{
		std::vector<std::reference_wrapper<Interactable>> :: iterator itr = std::find(dynamicWorldObjects.begin(), dynamicWorldObjects.end(), object);
		if (itr == dynamicWorldObjects.end()) return;
		dynamicWorldObjects.erase(itr);
	}

	void CheckForCollisions(Interactable& obj)
	{
		Collision* c = new Collision;
		for (Interactable& _obj : staticWorldObjects)
		{
			if (obj.GetController().GetID() != _obj.GetController().GetID())
			{
				if (obj.Intersects(_obj, c))
				{
					_obj.ChangeController(obj.GetController());
					obj.SolveCollision(*c);
					c = nullptr;
					delete c;
					return;
				}
			}
		}
		for (Interactable& _obj : dynamicWorldObjects)
		{
			if (obj != _obj)
			{				
				if (obj.Intersects(_obj, c))
				{
					obj.SolveCollision(*c);
					c = nullptr;
					delete c;
					return;
				}
			}
		}
	}

	float Tick(float fps)
	{
		//std::cout << "Tick" << fps << std::endl;
		SDL_RenderClear(_rend);
		/*for (Interactable& obj : staticWorldObjects)
		{
			obj.GetShape().Render(_rend);
		}*/
		for (Interactable& obj : staticWorldObjects)
		{
			obj.Render();
		}
		for (Interactable& obj : dynamicWorldObjects)
		{
			obj.Step(_rend);
			CheckForCollisions(obj);
		}
		SDL_RenderPresent(_rend);
		return fps++;
	}
};

