#pragma once
#include <vector>
#include <Vector2.h>
#include <Interactable.h>
#include <Speed.h>
#include <Form.h>
#include <Controller.h>

class World
{
private:
	std::vector<std::reference_wrapper<Interactable> > staticWorldObjects;
	std::vector<std::reference_wrapper<Interactable> > dynamicWorldObjects;
	std::vector<std::reference_wrapper<Controller> > controllers;
	SDL_Renderer* _rend;
	int _id;
	int _cid;

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
			Controller* obj = new Controller(i, Color(15 + i * 25, 15 + i * 25, 15 + i * 25));
			std::reference_wrapper<Controller> cont = *obj;
			controllers.push_back(cont);
		}
		for (Controller& obj : controllers)
		{
			if (obj.GetID() != 0)
			AddDynamicObject(new Interactable(_rend, ++_id, obj, circle));
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

	float Tick(Speed dt, float fps)
	{
		//std::cout << "Tick" << fps << std::endl;
		SDL_RenderClear(_rend);
		/*for (Interactable& obj : staticWorldObjects)
		{
			obj.GetShape().Render(_rend);
		}*/
		for (Interactable& obj : dynamicWorldObjects)
		{
			obj.Step(_rend);
		}
		SDL_RenderPresent(_rend);
		return fps++;
	}
};

