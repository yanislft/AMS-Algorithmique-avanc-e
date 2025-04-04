#include "point.h"
#include "json.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using json = nlohmann::json;

class arc
{
    friend class arcE;
    friend class graphe;
    friend class noeud;

    string id; //Nom de la route 
    string idNoeudD; //ID du noeud de départ 
    string idNoeudA; //ID du noeud d'arrivée 
    bool oneWay; //Indique si la route est à sens unique oou non
    int lane; //Nombre de voies 
    string highway; //Type de la route 
    bool reversed; //Si oneway détermine le sens de la route
    double length; //Longueur de la route (en mètre)
    point *geometry;
    int geoSize;
    double maxspeed; 
    double moyspeed; //moyenne de vitesse sur toutes le routes du même type (highway)
    double travel_time; //Temps de trajet moyen

    public : 
        arc();
        arc(string noeudDep, string noeudAr, string js);
        ~arc();
        void affiche();
};