#ifndef STABLO_H
#define STABLO_H
#include<utility>
#include<stack>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;


template<typename Tip>
class Stablo{

    public:
    struct Cvor{
        Tip element;
        Cvor *ld; //lijevo dijete
        Cvor *dd; //desno dijete
        Cvor *rod; //roditelj
        Cvor(Tip el,Cvor *r = nullptr,Cvor *ld = nullptr,Cvor *dd = nullptr):element(el),rod(r),ld(ld),dd(dd){}
    };

    private:

    Cvor *korijen;
    int broj_elemenata;
    void InOrderRek(Cvor*);
    int heightRek(Cvor *korijen);

    public:

    Stablo();
    pair<Cvor*,bool> Insert(Tip element);
    //void Insert(Tip element);
    Cvor* Find(Tip element);
    void InOrderRek(){InOrderRek(korijen);}
    void InOrder();
    void Erase(Cvor *za_brisanje);
    int Erase(const Tip &element);
    Cvor *getRoot() {return korijen;}
    int getBrojElemenata(){return broj_elemenata;}
    Cvor *NadjiNajmanji(Cvor *cvor);
    Cvor *NadjiSljedbenika(Cvor *cvor);
    Cvor *NadjiNajveci(Cvor *cvor);

    //!!!!!!!!!!!!!!!!! PROJEKAT !!!!!!!!!!!!!!!!!!!!!!!!!!! //

    class TreeIterator{  //klasa iterator 

        protected:

        Cvor *pok;   

        public:

        Cvor *NadjiNajmanjiIterator(Cvor *cvor);  //implementirana u stablo.cpp
        
        Cvor *NadjiSljedbenikaIterator(Cvor *cvor); //implementirana u stablo.cpp

        TreeIterator(Cvor *cvor):pok(cvor){} //konstruktor

        Tip& operator*(){return pok->element;} //trenutni element cvora na kojem se iterator nalazi; dereferenciranje

        TreeIterator operator++() {pok = NadjiSljedbenikaIterator(pok); return *this;}

        TreeIterator operator++(int){TreeIterator novi_cvor(*this); pok =  NadjiSljedbenikaIterator(pok); return novi_cvor;}
        
        friend bool operator==(TreeIterator it1,TreeIterator it2){return it1.pok == it2.pok;}  // poredi adrese
        
        friend bool operator!=(TreeIterator it1,TreeIterator it2){return it1.pok != it2.pok;}
        
        friend class Stablo<Tip>;
    };

    class Reverse_Iterator: public TreeIterator{  //nasljedjuje osnovnu klasu iterator

        public:

        Cvor *NadjiNajveci(Cvor *cvor);  //implementirana u stablo.cpp 

        Cvor *NadjiPrethodnikaIterator(Cvor *cvor); //implementirana u stablo.cpp

        Reverse_Iterator(Cvor *cvor ):TreeIterator(cvor){}

        Tip& operator*(){return this->pok->element;} 
        
        Reverse_Iterator operator++() {this->pok = NadjiPrethodnikaIterator(this->pok); return *this;}
        
        Reverse_Iterator operator++(int){Reverse_Iterator novi_cvor(*this); this->pok =  NadjiPrethodnikaIterator(this->pok); return novi_cvor;}
        
        friend bool operator==(Reverse_Iterator it1,Reverse_Iterator it2){return it1.pok == it2.pok;} 
        
        friend bool operator!=(Reverse_Iterator it1,Reverse_Iterator it2){return it1.pok != it2.pok;}
        
        friend class Stablo<Tip>;

    };
    

    TreeIterator Begin() {return TreeIterator(NadjiNajmanji(korijen));} //vraca iterator na prvi element

    TreeIterator End() {return TreeIterator(nullptr);}//vraca iterator na iza posljednjeg elementa

    Reverse_Iterator rBegin() {return Reverse_Iterator(NadjiNajveci(korijen));}

    Reverse_Iterator rEnd() {return Reverse_Iterator(nullptr);}
    
    //!!!!!!!!!!!! Operator [] koji vraća k-ti element po velicini !!!!!!!!!!!!!!!!!!! //

    int Height() {return heightRek(korijen);} //visina stabla

    Tip operator[](int k);


    //!!!!!!!!!!!!!!!!!!!!!! Da li je stablo podskup drugog stabla !!!!!!!!!!!!!!!!!!!!!!!!!//

    friend bool daLiJePodskup(Stablo<Tip> s1,Stablo<Tip> s2){

        auto t1 = s1.Begin();
        auto t2 = s2.Begin();

        while(t1 != s1.End() && t2 != s2.End()){

            if(*t1 < *t2) 
                t1++;
            
            else if(*t1 > *t2) //bukvalno nasao element koji ne postoji u stablu s1, odmah false
                return false;

            else{  //kad naidje na isti element onda pomjera oba i nastavlja gledati dalje 

                t1++;
                t2++;
            }
        }

        if(t2!=s2.End()) //ako je obisao prvi graf a drugi jos nije, to znaci da postoje elementi koji se ne nalaze u s1 i samim tim nije onda podskup
            return false;

        //inace vrati true ako je sve zadovoljeno

        return true;
       
    }


 //nije dio projekta//
    // !!!!!!!!!!!!! Da li je stablo podstablo prvog !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //

    friend bool bfsStablo(Stablo<Tip>::Cvor *root1, Stablo<Tip>::Cvor *root2){

        stack<pair<Stablo<Tip>::Cvor*, Stablo<Tip>::Cvor*>> stack;
        stack.push({root1, root2});


        while (!stack.empty()) {
            auto [node1, node2] = stack.top();  // structured binding  za parove, umjesto stack.first stavi se ime npr node1

            stack.pop();
            
            if(node2->ld == nullptr && node2->dd == nullptr) //ako je samo jedan cvor;
                return true;
            
            if (node1->dd != nullptr || node2->dd !=nullptr) {  

                if(node1->dd == nullptr && node2->dd != nullptr)
                    return false;
                
                if(node1->dd != nullptr && node2->dd !=nullptr){
                    if(node1->dd->element !=  node2->dd->element){
                        return false;
                    }
                    else
                        stack.push({node1->dd, node2->dd});

                }

                if(node1->dd != nullptr && node2->dd == nullptr){
                        stack.push({node1->dd, nullptr}); 
                        //continue;
                        
                }    
                                                
            }
                
                    
        if (node1->ld != nullptr || node2->ld !=nullptr) 
            {                   
                if(node1->ld == nullptr && node2->ld != nullptr)
                    return false;
                
                if(node1->ld != nullptr && node2->ld !=nullptr){
                    if(node1->ld->element !=  node2->ld->element){
                        return false;
                    }
                    else
                        stack.push({node1->ld, node2->ld});
                }

                if(node1->ld != nullptr && node2->ld == nullptr){
                    stack.push({node1->dd, nullptr});  
                        
                }    
                        
            }
            
        }
        return true;

    }

    friend bool daLiJePodstablo(Stablo<Tip> s1,Stablo<Tip> s2){

        Stablo<Tip>::Cvor *root1 = s1.korijen;
        Stablo<Tip>::Cvor *root2 = s2.korijen;

        if(root2 == nullptr )  //nullptr ce uvijek biti podstablo
            return true;

        if(root1 == nullptr)
            return false;

        queue<Stablo<Tip>::Cvor*> red;

        red.push(root1);
        

        while(!red.empty()){

            Stablo<Tip>::Cvor *trenutni = red.front();

            red.pop();
            
            if(trenutni->element == root2->element ){
              
                return bfsStablo(trenutni,root2);
            }
        
            if(trenutni->ld != nullptr)
                red.push(trenutni->ld);
            if(trenutni->dd != nullptr)
                red.push(trenutni->dd);

        }

        return false;
    }
    


};





#include "stablo.cpp"
#endif
