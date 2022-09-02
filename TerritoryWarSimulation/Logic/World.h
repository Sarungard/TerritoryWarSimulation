#pragma once
#include <vector>
#include <Vector2.h>
#include <Interactable.h>

class World
{
private:
	std::vector<std::reference_wrapper<Interactable> > staticWorldObjects;
	std::vector<std::reference_wrapper<Interactable> > dynamicWorldObjects;
	SDL_Renderer* _rend;
	int _id;

public:
	World(SDL_Renderer* rend)
	{
		_id = 0;
		_rend = rend;
		AddDynamicObject(new Interactable(_rend, ++_id ));
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

	void Step(float dt)
	{
		for (Interactable& obj : dynamicWorldObjects)
		{
			obj.Position += obj.Velocity * dt;
		}
	}
};

