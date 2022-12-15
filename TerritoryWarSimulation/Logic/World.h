#pragma once
#include <vector>
#include <Interactable.h>
#include <math.h>
#include <Layout.h>
#include <algorithm>

class World
{
private:
	std::vector<std::reference_wrapper<Interactable> > staticWorldObjects;
	std::vector<std::reference_wrapper<Interactable> > dynamicWorldObjects;
	std::vector<std::reference_wrapper<Controller> > controllers;
	std::vector<Core> cores;
	SDL_Renderer* _rend;
	Layout _layout;
	int _id;
	int _tiles;

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

	bool IsCore(int i, int j)
	{
		for (Core c : cores)
		{
			for (Vector2 _c : c.Positions())
			{
				if (_c.X() == i * 20 && _c.Y() == j * 20)
				{
					AddStaticObject(new Interactable(_rend, ++_id, Vector2(i * 20, j * 20), controllers.at(c.Controller()), square, 20, true));
					return true;
				}
			}
		}
		return false;
	}

public:

	World()
	{

	}

	World(Layout layout)
	{
		_layout = layout;
		_id = 0;
		_tiles = 0;
		cores = _layout.Cores();
		for (int i = 0; i <= _layout.Controllers(); ++i)
		{
			Controller* obj = new Controller(i, _colors[i]);
			std::reference_wrapper<Controller> cont = *obj;
			controllers.push_back(cont);
		}
		for (int i = 0; i < _layout.Width() / 20; ++i)
		{
			for (int j = 0; j < _layout.Height() / 20; ++j)
			{
				if (!IsCore(i, j))
				{
					AddStaticObject(new Interactable(_rend, ++_id, Vector2(i * 20, j * 20), controllers.front(), square, 20));
				}
				_tiles++;
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			SpawnNewBalls();
		}
	}

	World(SDL_Renderer* rend, Layout layout)
	{
		_layout = layout;
		_id = 0;
		_tiles = 0;
		_rend = rend;
		cores = _layout.Cores();
		SDL_RenderClear(_rend);
		SDL_SetRenderDrawColor(_rend, 0, 0, 0, 255);
		for (int i = 0; i <= _layout.Controllers(); ++i)
		{
			Controller* obj = new Controller(i, _colors[i]);
			std::reference_wrapper<Controller> cont = *obj;
			controllers.push_back(cont);
		}
		for (int i = 0; i < _layout.Width() / 20; ++i)
		{
			for (int j = 0; j < _layout.Height() / 20; ++j)
			{
				if (!IsCore(i,j))
				{
					AddStaticObject(new Interactable(_rend, ++_id, Vector2(i * 20, j * 20), controllers.front(), square, 20));
				}
				_tiles++;
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			SpawnNewBalls();
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

	void SpawnNewBalls()
	{
		for (Core c : cores)
		{
			AddDynamicObject(new Interactable(_rend, ++_id, c.Start(), controllers.at(c.Controller()), circle, 10));
		}
	}

	void CheckForCollisions(Interactable& obj)
	{
		Collision c;
		for (Interactable& _obj : staticWorldObjects)
		{
			if (obj.GetController()->GetID() != _obj.GetController()->GetID())
			{
				if (obj.Intersects(_obj, c))
				{
					_obj.ChangeController(obj.GetController());
					obj.SolveCollision(c.GetVelocity());
					obj.GetController()->GainATile();
					break;
				}
			}
		}
		for (Interactable& _obj : dynamicWorldObjects)
		{
			if (obj != _obj && obj.GetController() == _obj.GetController())
			{				
				if (obj.Intersects(_obj, c))
				{
					obj.SolveCollision(c.GetVelocity());
				}
			}
		}
	}

	void CheckControllers()
	{
		for (Controller& c : controllers)
		{
			if (c.Lost())
			{
				std::vector<std::reference_wrapper<Interactable> > newDynamicWorldObjects;
				std::vector<Core> newCores;
				for (Interactable& obj : dynamicWorldObjects)
				{
					if (obj.GetController() != &c)
					{
						newDynamicWorldObjects.push_back(obj);
					}
				}
				dynamicWorldObjects = newDynamicWorldObjects;
				for (Core _c : cores)
				{
					if (_c.Controller() != c.GetID())
					{
						newCores.push_back(_c);
					}
				}
				cores = newCores;
			}
		}
	}

	bool Ended()
	{
		return cores.size() == 1;
	}

	float Tick(float fps)
	{
		SDL_RenderClear(_rend);
		for (Interactable& obj : staticWorldObjects)
		{
			obj.Render();
		}
		for (Interactable& obj : dynamicWorldObjects)
		{
			obj.Step(_layout.Height(), _layout.Width());
			CheckForCollisions(obj);
		}
		CheckControllers();
		SDL_RenderPresent(_rend);
		return fps+1;
	}

	std::vector<std::reference_wrapper<Interactable> > GetStaticObjects()
	{
		return staticWorldObjects;
	}

	std::vector<std::reference_wrapper<Interactable> > GetDynamicObjects()
	{
		return dynamicWorldObjects;
	}

	std::vector<std::reference_wrapper<Controller> > GetControllers()
	{
		return controllers;
	}
	std::vector<Core> GetCores()
	{
		return cores;
	}
	int TileCount()
	{
		return _tiles;
	}

};