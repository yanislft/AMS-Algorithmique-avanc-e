#include "noeud.h"

#include <unordered_map>
#include <string>

using namespace std;

class noeudV
{
    friend class graphe;

    unordered_map<string,noeud> noeuds;

    public :
        void ajoutNoeud(noeud n);
        noeud rechercheNoeud(string idd); //comment rechercher ? On retourne le premier qu'on trouve avec ce nom ? Un ensemble d'arc ?
        void afficher();
        int getSize();
};