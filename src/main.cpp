#include <iostream>
#include "json.hpp"
#include "graphe.h"

using namespace std;
using json = nlohmann::json;

int main()
{
    //Tâches 1 à 3
    graphe g("nodes.csv", "arcs.csv"); //Le constructeur met egalement à jour la liste d'incidence 
    //g.afficher();
    
    //Tâche 4 - Degrés 
    g.degre(3);

    //Tâche 5 - Chemin 
    //g.chemin("657449", "1035435421");
    
    //Tâche 6 - Chemin le plus court
    g.plusCourtChemin("657449", "1035435421");

    //Tâche 7 - Itinéraire 

        //Version test
        g.itineraire("Avenue Anne dAutriche", "Rue de lOuvèze");

        //Version utilisateur 
        /*string o,d;
        cout<<"Entrez la route d'origine : ";
        cin>>o;
        cout<<"Entrez la route de destination : ";
        cin>>d;

        g.itineraire(o,d);*/

    return 0;
}