#include "../include/graphe.h"

//Constructeur vide
graphe::graphe() {}

//Constructeur qui créer le graphe avec les fichiers arcs.csv et nodes.csv
graphe::graphe(string fichierNoeud, string fichierArc)
{
    //Lecture et création des noeuds et des arcs 
    nbNoeuds = lectureNoeud(fichierNoeud);
    nbArcs = lectureArc(fichierArc);
  
    //Création  des relations entre les noeuds 
    listeIncidence();
}

int graphe::lectureArc(string fichierArc)
{
    ifstream fichier(fichierArc);
    string line;
    int cpt = 0;

    //Lis le fichier ligne par ligne 
    while (getline(fichier,line))
    {   
        //Séparation des 3 colonnes du fichier arc
        string s;
        string col[3];

        for (int i = 0, j = 0;i < line.length() && j <= 2; i++)
        {
            if (j < 2)
            {
                if (line[i] != ',') {s += line[i];}

                else 
                {
                    col[j] = s;
                    s = "";
                    j++;    
                }
            }

            else 
            {
                s += line[i];

                if (i == line.length() - 1) {col[j] = s;}
            }
        }
        
        //Si le format n'est pas un json valide, on le normalise 
        if (!valideJson(col[2])) 
        {
            string js;
        
            for (int i = 1, j = 0; i < col[2].size()-2; i++)
            {
                if (j == 1)
                {
                    if (col[2][i] == '>') {js += "[]"; j++;}
                    else {continue;}
                }

                else 
                {
                    if (col[2][i] == '"' && col[2][i+1] == '"') {js +="\'";}
                    else if (col[2][i] == '"' && col[2][i-1] == '"') {continue;}
                    else if (col[2][i] == '<') {j++;}
                    else {js += col[2][i];}
                }
            }

            for (char &c : js) 
            {
                if (c == '\'') {c = '"';}
                else if (c == 'F') {c = 'f';}
                else if (c == 'T') {c = 't';}
            }

            arc a(col[0], col[1],js);
            
            //Si c'est une route à doucle sens on crée un deuxième arc qui représente l'autre sens de
            if (!a.oneWay) 
            {
                arc b(col[1], col[0], js);
                
                normalisationID(a);
                gArcs.ajoutArc(a);
           
                normalisationID(b);
                gArcs.ajoutArc(b);

                cpt+=2;
                //a.affiche();
                //b.affiche();
            }

            else 
            {
                normalisationID(a);
                gArcs.ajoutArc(a);
                //a.affiche();
                cpt++;
            }
        }

        //Sinon on ne modifie uniquement les éléments qui doivent être modifiés dans tous les cas 
        else 
        {
            string js;
        
            for (int i = 1, j = 0; i < col[2].size()-2; i++)
            {
                if (j == 1)
                {
                    if (col[2][i] == '>') {js += "[]"; j++;}
                    else {continue;}
                }

                else 
                {
                    if (col[2][i] == '<') {j++;}
                    
                    else {js += col[2][i];}
                }
            }

            for (char &c : js) 
            {
                if (c == '\'') {c = '"';}
                else if (c == 'F') {c = 'f';}
                else if (c == 'T') {c = 't';}
            }

            arc a(col[0], col[1],js);
            
            if (!a.oneWay) 
            {
                arc b(col[1], col[0], js);
                
                normalisationID(a);
                gArcs.ajoutArc(a);
           
                normalisationID(b);
                gArcs.ajoutArc(b);

                cpt+=2;
                //a.affiche();
                //b.affiche();
            }

            else 
            {
                normalisationID(a);
                gArcs.ajoutArc(a);
                //a.affiche();
                cpt++;
            }
        }
    }

    return cpt;
}

int graphe::lectureNoeud(string fichierNoeud)
{
    ifstream fichier(fichierNoeud);
    string line;
    int cpt = 0;

    while (getline(fichier,line))
    {   
        //Séparation des 2 colonnes du fichier noeud
        string s;
        string col[2];

        for (int i = 0, j = 0;i < line.length() && j <= 1; i++)
        {
            if (line[i] != ',' && j == 0) {s += line[i];}

            else if (j > 0 && i < line.length() - 1) {s += line[i];}
            
            else
            {
                col[j] = s;
                s = "";
                j++;    
            }
        }

        gNoeuds.ajoutNoeud(noeud(col[0], col[1]));
        cpt++;
    }
    return cpt;
}

void graphe::listeIncidence()
{
    //On parcour la liste des arcs 
    for (unordered_map<string, arc>::iterator itA = gArcs.arcs.begin(); itA != gArcs.arcs.end(); itA++)
    {
        if (itA != gArcs.arcs.end())
        {
            //si on trouve dans la liste de noeud les noeuds qui constituent l'arc qu'on regarde, on ajoute l'arc a la liste d'arc correspondante du noeud (Arc Entrant ou arc Sortant)
            if (gNoeuds.noeuds.find(itA->second.idNoeudA) != gNoeuds.noeuds.end()) {gNoeuds.noeuds.find(itA->second.idNoeudA)->second.addArcE(itA->second);}

            if (gNoeuds.noeuds.find(itA->second.idNoeudD) != gNoeuds.noeuds.end()) {gNoeuds.noeuds.find(itA->second.idNoeudD)->second.addArcS(itA->second);}
        }
    }
}

/*
    L'algorithme degre que je propose à une complexité :
    
    Copie des noeuds : O(V)
    
    Tri rapide (pire des cas) : O(V^2)
    Tri rapide (moyenne) : O(VlogV)
    
    Affichage des noeuds : O(n)
    

    Au pire des cas : O(V^2)
    En moyenne : O(VlogV)
*/
void graphe::degre(int n)
{
    if (n >= 1 && n <= gNoeuds.getSize())
    {
        noeud *no = new noeud[gNoeuds.getSize()];
        int i = 0;

        //copie tous les noeuds dans un tableau 
        for (unordered_map<string, noeud>::iterator itN = gNoeuds.noeuds.begin(); itN != gNoeuds.noeuds.end(); itN++)
        {
            if (itN != gNoeuds.noeuds.end())
            {
                no[i] = itN->second;
                i++;
            }
        }

        //tri + affichage du tableau tableau 
        triRapide(no, 0, gNoeuds.getSize()-1);

        for (int i = 1; i <= n; i++)
        {
            cout<<"++++++++ "<<i<<" +++++++++++"<<endl;
            no[i].afficher();
        }

        delete[] no;
    }
}

int graphe::chemin(string o, string d)
{
    noeud nO = gNoeuds.rechercheNoeud(o);
    noeud nD = gNoeuds.rechercheNoeud(d);

    if (nO.id != "" && nD.id != "") 
    {
        stack<noeud> p; 
        vector<string> cheminEmpr; 

        nonVisite();

        p.push(nO);
        gNoeuds.noeuds[nO.id].visite = true; 

        while (!p.empty()) 
        {
            nO = p.top();
            p.pop();

            //si le noeud actuel est le noeud de destination on affiche le chemin
            if (nO.id == nD.id) 
            {
                cout<< "Routes utilisées : "<<endl;

                for (int i = 0; i < cheminEmpr.size(); i++) 
                {
                    cout << i << " : " << cheminEmpr[i] << endl;
                }

                return cheminEmpr.size();
            }

            //parcours les arcs sortants du noeud actuel
            for (unordered_map<string,arc>::iterator itA = nO.arcsS.arcs.begin(); itA != nO.arcsS.arcs.end(); ++itA) 
            {
                string idSuiv = itA->second.idNoeudA;
                noeud suiv = gNoeuds.rechercheNoeud(idSuiv);

                if (!gNoeuds.noeuds.find(idSuiv)->second.visite) 
                {
                    p.push(suiv);
                    cheminEmpr.push_back(itA->second.id);
                    gNoeuds.noeuds.find(idSuiv)->second.visite = true;
                }
            }
        }

        //si aucun chemin n'est trouvé 
        return 0;
    }

    return -1;
}

//pour cette fonction nous allons faire un parcous en largeur, nous allos donc utiliser une file au lieu d'une pile 
int graphe::plusCourtChemin(string o, string d)
{
    noeud nO = gNoeuds.rechercheNoeud(o);
    noeud nD = gNoeuds.rechercheNoeud(d);

    if (nO.id != "" && nD.id != "")
    {
        queue<noeud> q;
        unordered_map<string, string> parents;
        vector<string> cheminEmpr;

        nonVisite();

        q.push(nO);
        gNoeuds.noeuds.find(nO.id)->second.distance = 0;
        gNoeuds.noeuds.find(nO.id)->second.visite = true;

        while (!q.empty())
        {
            noeud nO = q.front();
            q.pop();

            //si le noeud actuel est le noeud de destination on affiche le chemin
            if (nO.id == nD.id)
            {
                string s = nD.id;
                while (s != o)
                {
                    cheminEmpr.push_back(s);
                    s = parents[s];
                }
                cheminEmpr.push_back(o);

                reverse(cheminEmpr.begin(), cheminEmpr.end());

                cout<<"Routes utilisées : "<<endl;
                for (int i = 0; i < cheminEmpr.size() - 1; i++)
                {
                    arc arcTrouve = gNoeuds.noeuds.find(cheminEmpr[i])->second.rechercheArc(gNoeuds.noeuds.find(cheminEmpr[i+1])->second);
                    cout<<i + 1<<" : "<<arcTrouve.id<<endl;
                }

                return cheminEmpr.size() - 1;
            }

            //parcourt les acrs sortant du noeurd actuel
            for (unordered_map<string, arc>::iterator itA = gNoeuds.noeuds.find(nO.id)->second.arcsS.arcs.begin(); itA != gNoeuds.noeuds.find(nO.id)->second.arcsS.arcs.end(); ++itA)
            {
                string idSuiv = itA->second.idNoeudA;

                if (!gNoeuds.noeuds.find(idSuiv)->second.visite)
                {
                    q.push(gNoeuds.rechercheNoeud(idSuiv));
                    gNoeuds.noeuds.find(idSuiv)->second.visite = true;

                    gNoeuds.noeuds.find(idSuiv)->second.distance = gNoeuds.noeuds.find(nO.id)->second.distance + 1;
                    parents.insert({idSuiv, nO.id});
                }
            }
        }

        return 0;
    }
    
    return -1;
}

int graphe::itineraire(string origine, string destination)
{
    string nO = "";
    string nD = "";
    
    //Recherche du noeud correspondant aux noms donnés par l'utilisateur 
    for (unordered_map<string, arc>::iterator itA = gArcs.arcs.begin(); itA != gArcs.arcs.end(); ++itA)
    {
        if (itA != gArcs.arcs.end())
        {
            if (itA->second.id == origine) {nO = itA->second.idNoeudA;}
            if (itA->second.id == destination) {nD = itA->second.idNoeudD;}

            if (!nO.empty() && !nD.empty()) {break;}
        }
    }

    if (nO.empty() || nD.empty()) {return -1;}

    return plusCourtChemin(nO, nD);
}

int graphe::getNbArcs()
{
    return nbArcs;
}

int graphe::getNbNoeuds()
{
    return nbNoeuds;
}

bool graphe::valideJson(string s)
{
    try
    {
        json::parse(s);
        return true;
    }
    catch (json::parse_error) {return false;}
}

void graphe::normalisationID(arc &a)
{
    if (gArcs.rechercheArcBool(a.id))
    {
        for (int i = 2; i < INT_MAX; i++)
        {
            string newid = a.id + to_string(i);  
            
            if(!gArcs.rechercheArcBool(newid))
            {
                a.id = newid;
                break;
            }
        }
    }
}

void graphe::afficher()
{
    cout<<"Nombre de noeuds dans le graphe : "<<nbNoeuds<<endl<<
    "Nombre d'arcs dans le graphe : "<<nbArcs<<endl<<endl<<
    "Liste des noeuds : "<<endl<<endl;

    gNoeuds.afficher();
}

void graphe::echange(noeud &a, noeud &b)
{
    noeud tmp;

    tmp = a;
    a = b;
    b = tmp;
}

void graphe::triRapide(noeud* l, int a, int b)
{
    if (a < b)
    {
        int m = 0;
        
        m = partitionnement(l, a, b, m);
        triRapide(l, a, m-1);
        triRapide(l, m+1, b);
    }
}

int graphe::partitionnement(noeud* l, int a, int b, int m)
	{
		int i = a + 1, j = b;
		
		while (i <= j)
		{
			while (i <= b && l[i].getNbArcs() > l[a].getNbArcs())
			{
				i++;
			}
			
			while (j > a && l[j].getNbArcs() <= l[a].getNbArcs())
			{
				j--;
			}
			
			if (i < j)
			{
                echange(l[i], l[j]);
				i++;
				j--;
			}
		}
		
		echange(l[a], l[j]);
		
		return j;
	}

    void graphe::nonVisite()
    {
        for (unordered_map<string, noeud>::iterator itN = gNoeuds.noeuds.begin(); itN != gNoeuds.noeuds.end(); itN++)
        {
            if (itN != gNoeuds.noeuds.end())
            {
                itN->second.visite = false;
                itN->second.distance = -1;
            }
        }
    }