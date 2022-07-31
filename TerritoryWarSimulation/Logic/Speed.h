class Speed
{
    int speed;

public:
    Speed()
    {
        speed = 300;
    }

    Speed(int value)
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

    int getSpeed()
    {
        return speed;
    }

    void setSpeed(int value)
    {
        if (value >= 0)
        {
            speed = value;
        }
    }

    friend int operator/(const Speed& a, const int& b)
    {
        return a.speed / b;
    }

    friend void operator+=(Speed& a, const int& b)
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

    friend void operator-=(Speed& a, const int& b)
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