#include "../include/arc.h"

arc::arc(){}

arc::~arc()
{
    /* if (geometry != nullptr)
    {
        delete[] geometry;
        geometry = nullptr;
    }*/
}

arc::arc(string noeudDep, string noeudAr, string js)
{
    idNoeudD = noeudDep;
    idNoeudA = noeudAr;
    
    json j = j.parse(js);

    if (j.contains("name"))
    {
        //Traite le cas ou il y à plusieurs noms de rue
        if (j["name"].is_array())
        {
            for (int i = 0; i < j["name"].size(); i++)
            {
                id += j["name"][i].get<string>() += " ";
            }
        }

        else if (j["name"].is_string()) {id = j["name"];}

        else
        {
            string sid;

            for (int i = 0; i < j["name"].size(); i++)
            {
                sid += j["name"][i].get<string>() +  ", ";
            }
            
            id = sid;
        }
    }

    //S'il n'y a pas de nom dans le fichier on donne comme nom une chaine de caractères correspondant au couple de noeuds constituant l’arc
    else 
    {
        id = noeudDep + noeudAr;
    }

    if (j.contains("highway")) 
    {
        if (j["highway"].is_array()) 
        {
            for (int i = 0; i < j["highway"].size(); i++)
            {
                highway += j["highway"][i].get<string>() += " ";
            }
        }
        
        else {highway = j["highway"];}
    }

    if (j.contains("oneway")) {oneWay = j["oneway"];}
    
    if (j.contains("reversed")) 
    {
        if (j["reversed"].is_array()) {reversed = j["reversed"][0];}
        else {reversed = j["reversed"];}
    }
    
    if (j.contains("length")) 
    {
        if (j["length"].is_string()) {length = stoi(j["length"].get<string>());}
        else {length = j["length"];}
    }

    if (j.contains("speed_kph"))
    {
        double s = j["speed_kph"];
        int di = s;

        //détermine si c'est une limite de vitesse ou une moyenne 
        if (di % 10 == 0) 
        {
            maxspeed = s;
            moyspeed = -1;
        }
        else 
        {
            moyspeed = j["speed_kph"];
            maxspeed = -1;
        }
    }

    if (j.contains("travel_time")) 
    {
        if (j["travel_time"].is_string()) {travel_time = stoi(j["travel_time"].get<string>());}
        else {travel_time = j["travel_time"];}
    }
    
    if (j.contains("lanes")) 
    {
        int x = 0;;

        if (j["lanes"].is_array())
        {
            for (int i = 0; i < j["lanes"].size(); i++)
            {
                string la = j["lanes"][i].get<string>();
                x += stoi(la);
            }
            lane = x;
        }
        
        else 
        {
            string la = j["lanes"].get<string>();
            lane = stoi(la);
        }
    }
    else {lane = 1;}

    /*
    if (j.contains("geometry"))
    {                    
        geoSize = j["geometry"].size();
        geometry = new point[geoSize];
        
        for (int i = 0; i < geoSize; i++)
        {
            geometry[i].x = j["geometry"][i][0].get<double>();
            geometry[i].y = j["geometry"][i][1].get<double>();
        }                    
    }
    */
}

void arc::affiche()
{
    cout<<endl<<"Id : "<<id<<endl;
    cout<<"Id noeud départ : "<<idNoeudD<<endl;
    cout<<"Id noeud arrivée : "<<idNoeudA<<endl;
    cout<<"Type de route : "<<highway<<endl;
    cout<<"Nombre de voies : "<<lane<<endl;
    
    if(oneWay){cout<<"Route à sens unique "<<endl;}
    else {cout<<"Route à double sens "<<endl;}

    cout<<"Longueur : "<<length<<" m"<<endl;

    if (maxspeed > 0) 
    {
        cout<<"Vitesse maximale autorisée : "<<maxspeed<<"km/h"<<endl;
        cout<<"Temps de trajet en roulant à la vitesse maximale autorisée : "<<travel_time<<" min"<<endl;
    }
    else 
    {
        cout<<"Vitesse moyenne : "<<moyspeed<<"km/h"<<endl;
        cout<<"Temps de trajet moyen : "<<travel_time<<" min"<<endl;
    }
/*
    cout<<"Suite de points constituants la route : ";

    for (int i = 0; i < geoSize; i++)
    {
        geometry[i].affichage();
    }*/
    cout<<endl;
}