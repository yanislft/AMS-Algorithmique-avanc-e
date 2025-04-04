#include "arcE.h"

using namespace std;

class noeud 
{
    friend class noeudV;
    friend class graphe;

    string id;
    point geo;
    int street_count;
    arcE arcsE;
    arcE arcsS;
    bool visite;
    int distance;

    public :
        noeud();
        noeud(string i, string jso);
        ~noeud();
        void afficher();
        void addArcE(arc a);
        void addArcS(arc a);
        int getNbArcs();
        arc rechercheArc(noeud n);
};