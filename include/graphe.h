#include "noeudV.h"

#include <stack>
#include <vector>
#include <queue>

class graphe 
{
    noeudV gNoeuds;
    arcE gArcs;
    int nbNoeuds;
    int nbArcs;

    public :
        graphe();
        graphe(string fichierNoeud, string fichierArc);
        void afficher();
        int lectureArc(string fichierArc);
        int lectureNoeud(string fichierNoeud);
        void listeIncidence();
        void degre(int n);
        int chemin(string o, string d);
        int plusCourtChemin(string o, string d);
        int itineraire(string o, string d);

        int getNbNoeuds();
        int getNbArcs();
        bool valideJson(string s);
        void normalisationID(arc &a);
        void triRapide(noeud* l, int a, int b);
        int partitionnement(noeud* l, int a, int b, int m);
        void echange(noeud &a, noeud &b);
        void nonVisite();
};