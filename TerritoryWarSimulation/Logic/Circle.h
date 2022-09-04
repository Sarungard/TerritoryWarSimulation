#pragma once
#include <Shape.h>
#include <Square.h>
#include <Collision.h>
#include <SDL.h>
#include <math.h>
#include <limits>
#include <Color.h>

class Circle :
    public Shape
{
private:
    float _radius;
    Color _color;
    SDL_Renderer* _rend;

public:
    Circle()
    {
        _center = Vector2(0, 0);
        _radius = 20;
    }

    Circle(SDL_Renderer* rend, Vector2 center, float radius, Color color)
    {
        _rend = rend;
        _center = center;
        _radius = radius;
        _color = color;
    }

    bool Intersects(Square other, Collision* collision) const
    {
        constexpr float shortestDist = std::numeric_limits<float>::max();
    }

    bool Intersects(Circle other, Collision* collision) const
    {
        const float tr = other._radius + this->_radius;
        const float d = sqrt(pow(this->_center.X - other._center.X, 2) + pow(this->_center.Y - other._center.Y, 2));
        if (d > tr) return false;
        collision = new Collision(other, *this, d, tr, Vector2(this->_center.X - other._center.X, this->_center.Y - other._center.Y));
        return true;
    }

    void Render(SDL_Renderer* rend, Vector2 position)
    {
        _center = position;
        const int32_t diameter = (_radius * 2);

        int32_t x = (_radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        SDL_SetRenderDrawColor(_rend, _color.r, _color.g, _color.b, _color.a);

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(rend, _center.X + x, _center.Y - y);
            SDL_RenderDrawPoint(rend, _center.X + x, _center.Y + y);
            SDL_RenderDrawPoint(rend, _center.X - x, _center.Y - y);
            SDL_RenderDrawPoint(rend, _center.X - x, _center.Y + y);
            SDL_RenderDrawPoint(rend, _center.X + y, _center.Y - x);
            SDL_RenderDrawPoint(rend, _center.X + y, _center.Y + x);
            SDL_RenderDrawPoint(rend, _center.X - y, _center.Y - x);
            SDL_RenderDrawPoint(rend, _center.X - y, _center.Y + x);

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

        SDL_SetRenderDrawColor(_rend, 0, 0, 0, 255);
    }
};
