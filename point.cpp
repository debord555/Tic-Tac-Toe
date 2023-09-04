class Point
{
    int x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int getX();
    int getY();
    int setX(int x);
    int setY(int y);
    bool isValid();
};

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

int Point::setX(int x)
{
    this->x = x;
    return 0;
}

int Point::setY(int y)
{
    this->y = y;
    return 0;
}

bool Point::isValid()
{
    if (x < 4 && x > -1)
    {
        if (y < 4 && y > -1)
            return true;
        else
            return false;
    }
    else
        return false;
}