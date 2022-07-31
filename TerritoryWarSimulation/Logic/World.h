#pragma once
#include <vector>
#include <Vector2.h>
#include <Interactable.h>
class World
{
private:
	std::vector<std::reference_wrapper<Interactable> > staticWorldObjects;
	std::vector<std::reference_wrapper<Interactable> > dynamicWorldObjects;

public:
	void AddStaticObject(Interactable& object)
	{
		std::reference_wrapper<Interactable> obj = object;
		staticWorldObjects.push_back(obj);
	}

	void AddDynamicObject(Interactable& object)
	{
		std::reference_wrapper<Interactable> obj = object;
		dynamicWorldObjects.push_back(obj);
	}

	void RemoveObject(Interactable* object)
	{
		if (!object) return;
		auto itr = std::find(dynamicWorldObjects.begin(), dynamicWorldObjects.end(), object);
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

