#include "../include/noeud.h"

noeud::noeud()
{
    id = "";
    geo.x = 0;
    geo.y = 0;
    street_count = 0;
    arcsE = arcE();
    arcsS = arcE();
    visite = false;
}

noeud::noeud(string i, string jso)
{
    id = i;

    json j = j.parse(jso);

    if (j.contains("x")) {geo.x = j["x"];}
    if (j.contains("y")) {geo.y = j["y"];}
    if (j.contains("street_count")) {street_count = j["street_count"];}
}

void noeud::afficher()
{
    cout<<"Noeud n° : "<<id<<endl<<"Nombre d'arcs entrants : "<<arcsE.getSize()<<endl<<
    "Nombre d'arcs sortants : "<<arcsS.getSize()<<endl<<
    "Liste de noeuds entrants :"<<endl;
    arcsE.afficher();
    cout<<endl<<"Liste des noeuds sortants :"<<endl<<endl;
    arcsS.afficher();
}

void noeud::addArcE(arc a)
{
    arcsE.ajoutArc(a);
}

void noeud::addArcS(arc a)
{
    arcsS.ajoutArc(a);
}

int noeud::getNbArcs()
{
    return arcsE.getSize() + arcsS.getSize();
}

arc noeud::rechercheArc(noeud n)
{
    for (unordered_map<string, arc>::iterator it = arcsS.arcs.begin(); it != arcsS.arcs.end(); it++)
    {
        if (it->second.idNoeudA == n.id) {return it->second;}
    }

    return arc();
}