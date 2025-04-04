#include "arc.h"

#include <limits>
#include <unordered_map>
#include <string>

using namespace std;

class arcE
{
    friend class graphe;
    friend class noeud;
    
    unordered_map<string,arc> arcs;

    public :
        void ajoutArc(arc a);
        arc rechercheArc(string idd);
        bool rechercheArcBool(string idd);
        void afficher();
        int getSize();
};