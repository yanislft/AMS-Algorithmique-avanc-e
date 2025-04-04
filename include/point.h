#include <iostream>

using namespace std;

class point
{
    friend class arc;
    friend class noeud;

    double x;
    double y;

    public :
        point();
        point(double a, double b);
        void affichage();
};