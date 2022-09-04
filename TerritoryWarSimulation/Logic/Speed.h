class Speed
{
    float speed;

public:
    Speed()
    {
        speed = 300;
    }

    Speed(float value)
    {
        if (value < 0)
        {
            speed = 300;
        }
        else
        {
            speed = value;
        }
    }

    float getSpeed()
    {
        return speed;
    }

    void setSpeed(float value)
    {
        if (value >= 0)
        {
            speed = value;
        }
    }

    friend int operator/(const Speed& a, const float& b)
    {
        return a.speed / b;
    }

    friend void operator+=(Speed& a, const float& b)
    {
        if (a.speed + b > 3000)
        {
            a.speed = 3000;
        }
        else
        {
            a.speed += b;
        }
    }

    friend void operator-=(Speed& a, const float& b)
    {
        if (a.speed - b < 0)
        {
            a.speed = 0;
        }
        else
        {
            a.speed -= b;
        }
    }
};