#include "../include/noeudV.h"

void noeudV::ajoutNoeud(noeud n)
{
    //regarde si l'id associé a la chaine de caractère n'est pas attribué 
    if (noeuds.find(n.id) == noeuds.end()) {noeuds.insert({n.id,n});}

    //sinon regarde l'id associé à la chiane de caractère + 1 
    else 
    {
        for (int i = 0; i < numeric_limits<int>::max(); i++)
        {
            string id = n.id + to_string(i);
            if (noeuds.find(id) == noeuds.end()) {noeuds.insert({id,n}); break;}
        }
    }
}

void noeudV::afficher()
{
    int i = 0;
    for(auto [id,noeud] : noeuds)
    {
        //if (i >= 5)break;
        noeud.afficher();
        i++;
    }
}

noeud noeudV::rechercheNoeud(string idd)
{
    auto it = noeuds.find(idd);

    if (it != noeuds.end()) {return it->second;}
    else return noeud();
}

int noeudV::getSize()
{
    return noeuds.size();
}