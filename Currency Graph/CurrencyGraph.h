#ifndef CURRENCYGRAPH_H
#define CURRENCYGRAPH_H
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <list>
#include <unordered_map>
#include<iostream>

using namespace std;

class CurrencyGraph{


    struct Node{ //cvor koji mi predstavlja svaku pojedinacnu valutu
        string currency; //naziv valute
        list<pair<string,double>> connections; //lista susjedstva
        Node(string name):currency(name){}  //konstruktor
    };

    private:

    unordered_map<string,Node*> mainCurrencyMap;
    void Upper(string& s);

    public:

    void addCurrency(string firstNode,string secondNode,double rate){ //dodavanje uredjene trojke

        Node *from;
        Node *to;

            if(mainCurrencyMap.find(firstNode) == mainCurrencyMap.end()){ //ako ne postoji u mapi valuta to znaci da find ne vraca nista
                //dodavanje u mapu 

                from = new Node(firstNode);
                mainCurrencyMap[firstNode] = from;
               
            }

            else{  //ako vec postoji onda ga samo pridruzim cvoru from jer mi treba za dodavanje u listu susjedstva
                from = mainCurrencyMap[firstNode];
            }

            //ista provjera za drugu valutu

            if(mainCurrencyMap.find(secondNode) == mainCurrencyMap.end()){

                to= new Node(secondNode);
                mainCurrencyMap[secondNode] = to;
              
            }

            else{
                to = mainCurrencyMap[secondNode];
            }

            //dodavanje u listu susjedstva
            from->connections.push_back({secondNode,rate});
            to->connections.push_back({firstNode,1/rate});

        }


    double getConversion(string fromNode,string toNode){

            Upper(fromNode); //ako nisu napisane velikim da ne dolazi do problema
            Upper(toNode); 

            //provjera ako uopce ne postoji ta valuta u mapi 

            if(mainCurrencyMap.find(fromNode) == mainCurrencyMap.end())
                return -1;
            
            if(mainCurrencyMap.find(toNode) == mainCurrencyMap.end())
                return -1;


            unordered_map<string,double> distances; //udaljenosti izmedju cvorova 

            distances[fromNode] = 1;

            //DJIKSTRA ALGORITAM

            set<pair<double,string>> tree;

            tree.insert({1,fromNode}); //trenutni cvor s kojim pocinje djikstra

            while(!tree.empty()){

                auto firstEl = *tree.begin();

                tree.erase(tree.begin()); //posjecen je znaci

                string current = firstEl.second;  //radi lakseg snalazenja 
                double d = firstEl.first;

                if(current == toNode)
                    return d;

                for(auto &el : mainCurrencyMap[current]->connections){ //prolazimo kroz listu susjedstva

                    auto v = el.first;
                    double r = el.second; 

                    if(distances.find(v) == distances.end() || distances[v] > r * d ){ //ako je ova udaljenost
                        tree.erase({distances[v],v});   //promijenimo udaljenost
                        distances[v] = round((d * r)*1000.0)/1000.0;
                        tree.insert({distances[v],v});
                    }
                }

                auto e = mainCurrencyMap.find(current);
                if(e != mainCurrencyMap.end()){ //vrsim provjeru za svaki element u listi susjedstva, da li je to zeljeeni konacni node
                    
                    for(auto k : e->second->connections){
                        if(k.first == toNode)
                            return round((d * k.second)*1000.0)/1000.0;
                    }

                }


            }

            return 0;

        }

        




};


void CurrencyGraph::Upper(string& s){

    for(int i = 0;i < s.size();i++){
        s[i] = toupper(s[i]);
    }
}


    

#endif

