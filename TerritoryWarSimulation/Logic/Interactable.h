#pragma once
#include <Vector2.h>
#include <Shape.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Interactable
{
public:
	Vector2 Position;
	Vector2 Velocity;
	Shape Shape;

	Interactable(SDL_Renderer* rend, int id)
	{
		_id = id;
		SDL_Surface* surface = NULL;
		surface = IMG_Load("test.jpg");
		std::cout << IMG_GetError() << std::endl << SDL_GetError() << std::endl;
		//_texture = IMG_LoadTexture(rend,"D:\\_Gamer1_adatai\\Desktop\\Projects\\Szakdolgozat\\Simulation\\TerritoryWarSimulation\\Debug\\test.jpg");
		_texture = SDL_CreateTextureFromSurface(rend, surface);
		_destination.w = 40;
		_destination.h = 40;
		_destination.x = 400;
		_destination.y = 400;
		SDL_FreeSurface(surface);
		SDL_QueryTexture(_texture, NULL, NULL, &_destination.w, &_destination.h);
		SDL_RenderPresent(rend);
	}

	~Interactable()
	{
		SDL_DestroyTexture(_texture);
	}

	void Render(SDL_Renderer* rend)
	{
		_destination.x = Position.X;
		_destination.y = Position.Y;

		SDL_RenderCopy(rend, _texture, NULL, &_destination);
	}

	int GetID() const
	{
		return _id;
	}

	friend bool operator == (const Interactable& A, const Interactable& B);

private:
	SDL_Rect _destination;
	SDL_Texture* _texture;
	int _id;
};

bool operator == (const Interactable& A, const Interactable& B)
{
	return A.GetID() == B.GetID();
}

struct Transform
{
	Vector2 Position;
	Vector2 Scale;
	float Rotation;
};

