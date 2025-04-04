#include "../include/point.h"

point::point()
{
    x = 0.0;
    y = 0.0;
}

point::point(double a, double b)
{
    x = a;
    y = b;
}

void point::affichage()
{
    cout<<"( "<<x<<" ; "<<y<<")";
}