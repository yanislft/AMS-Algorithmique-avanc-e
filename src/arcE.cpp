#include "../include/arcE.h"

void arcE::ajoutArc(arc a)
{
    //regarde si l'id associé a la chaine de caractère n'est pas attribué 
    if (arcs.find(a.id) == arcs.end()) {arcs.insert({a.id,a});}

    //sinon regarde l'id associé à la chiane de caractère + 1 
    else 
    {
        for (int i = 0; i < INT_MAX; i++)
        {
            string id = a.id + to_string(i);
            if (arcs.find(id) == arcs.end()) {arcs.insert({id,a}); break;}
        }
    }
}

void arcE::afficher()
{
    for(auto [id,arc] : arcs)
    {
        arc.affiche();
    }
}

arc arcE::rechercheArc(string idd)
{
    auto it = arcs.find(idd);
    
    if (it != arcs.end()) {return it->second;}
    else return arc();
}

bool arcE::rechercheArcBool(string idd)
{
    return arcs.find(idd) != arcs.end();
}

int arcE::getSize()
{
    return arcs.size();
}