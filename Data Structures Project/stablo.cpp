#ifndef STABLO_CPP
#define STABLO_CPP

#include "stablo.h"
#include<stack>
#include<vector>
#include<queue>
#include<stack>
#include<utility>
#include <iostream>
using namespace std;

template<typename Tip>
Stablo<Tip>::Stablo(){
    korijen = nullptr;
    broj_elemenata = 0;
}

template<typename Tip>
pair<typename Stablo<Tip>::Cvor*,bool> Stablo<Tip>::Insert(Tip element){

    //ako je prazno stablo
    if(korijen == nullptr){
        korijen = new Cvor(element);
        broj_elemenata = 1;
        return{korijen,true};
    }

    Cvor *trenutni = korijen;
    Cvor *prethodni = nullptr;

//moramo sacuvati prethodni jer cemo u jednom trenutku otici s trenutnim na nullptr i necemo moci spasiti roditelja
    while(trenutni != nullptr){

        if(element == trenutni->element){
            return{trenutni,false};
        }

        prethodni = trenutni;
        if(element < trenutni->element)
            trenutni = trenutni->ld;

        else
            trenutni = trenutni->dd;
    }

    broj_elemenata++;
    Cvor *novi = new Cvor(element,prethodni);

    if(element < prethodni->element)
        prethodni->ld = novi;

    else
        prethodni->dd = novi;

    return {novi,true};


}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(Tip element){

    Cvor *trenutni = korijen;

    while (trenutni != nullptr){

        if(element == trenutni->element)
            return trenutni;

        if(element < trenutni->element)
            trenutni = trenutni->ld;
        else
            trenutni = trenutni->dd;

    }

    return nullptr;

}


template<typename Tip>
void Stablo<Tip>::InOrderRek(Stablo<Tip>::Cvor *cvor){

    if(cvor == nullptr)
        return;

    InOrderRek(cvor->ld);
    cout<<cvor->element<<" ";
    InOrderRek(cvor->dd);
}

template<typename Tip>
void Stablo<Tip>::InOrder(){

    Cvor *trenutni = NadjiNajmanji(korijen);

    while(trenutni != nullptr){
        cout<<trenutni->element<<" ";
        trenutni = NadjiSljedbenika(trenutni);
    }
    cout<<endl;

}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiNajmanji(Cvor *cvor){

    if(cvor == nullptr)
        return nullptr;

    Cvor *trenutni = cvor;

    while(trenutni->ld != nullptr)
        trenutni = trenutni->ld;

    return trenutni;

}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiNajveci(Cvor *cvor){

    if(cvor == nullptr)
        return nullptr;

    Cvor *trenutni = cvor;

    while(trenutni->dd != nullptr)
        trenutni = trenutni->dd;

    return trenutni;

}


template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiSljedbenika(Cvor *cvor){

    if(cvor->dd != nullptr)  //ako ima desno dijete, onda je sljedbenik najmanje dijete koje je lijevo od trenutnog desnog djeteta
        return NadjiNajmanji(cvor->dd); //bukvalno trazi najmanji element u podstablu

    Cvor *trenutni = cvor;

    while(trenutni != korijen && trenutni == trenutni->rod->dd) //vracamo se gore
        trenutni = trenutni->rod;

        //sve dok trenutni nije lijevo dijete roditelja
        if(trenutni == korijen)
            return nullptr;
        else
            return trenutni->rod;


}

template<typename Tip>
void Stablo<Tip>::Erase(Cvor *za_brisanje){

    //I slucaj : ako cvor nema desno dijete

    if(za_brisanje->dd == nullptr){

        if(za_brisanje->ld == nullptr) {//ako nema ni lijevo dijete mozemo ga samo obrisati ali paziti
            if(za_brisanje->rod != nullptr){ //ako ima roditelja
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = nullptr;
                else
                    za_brisanje->rod->ld = nullptr;
            }
            else //ako nema roditelja, tada je korijen
                korijen = nullptr;
        }

        else{ //ako ima lijevo dijete
            if(za_brisanje->rod != nullptr){ //ako ima roditelja
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = za_brisanje->ld;
                else
                    za_brisanje->rod->ld = za_brisanje->ld;
            }
            else
                korijen = za_brisanje->ld; //
                za_brisanje->ld->rod = nullptr;
        }

    }

    //II slucaj: ako ima desno dijete

    else{

        Cvor *sljedbenik = NadjiSljedbenika(za_brisanje);
        if(sljedbenik->rod->dd == za_brisanje){ //ako je direktno njegovo desno dijete njegov sljedbenik
            sljedbenik->rod = za_brisanje->rod; //postavimo roditelj sljedbeniku, radi i za korijen
            if(za_brisanje->rod != nullptr) { //ako ima roditelja
                if(za_brisanje->rod->dd == za_brisanje)
                    za_brisanje->rod->dd = sljedbenik;
                else
                    za_brisanje->rod->ld = sljedbenik;

            }
            else
                korijen = sljedbenik;

            if(za_brisanje->ld != nullptr)
                za_brisanje->ld->rod = sljedbenik;
            sljedbenik->ld = za_brisanje->ld;
        }
        else{
            sljedbenik->rod->ld = sljedbenik->dd;
            if(sljedbenik->dd != nullptr)
                sljedbenik->dd->rod = sljedbenik->rod;

            sljedbenik->dd = za_brisanje->dd;
            za_brisanje->dd->rod = sljedbenik;
            sljedbenik->ld = za_brisanje->ld;

            if(za_brisanje->ld != nullptr)
                za_brisanje->ld->rod = sljedbenik;

            sljedbenik->rod = za_brisanje->rod;

            if(za_brisanje->rod != nullptr){
                if(za_brisanje->rod->ld == za_brisanje)
                    za_brisanje->rod->ld = sljedbenik;
                else
                    za_brisanje->rod->dd = sljedbenik;
            }
            else
                korijen = sljedbenik;


        }

    }

    //svakako se izvrsava u bilo kojem od slucajeva pa se moze napisati na kraj
    delete za_brisanje; //brisanje cvora ;
    broj_elemenata--;

}

template<typename Tip>
int Stablo<Tip>::Erase(const Tip &element){

    Cvor *za_brisanje = Find(element); //nadjemo cvor koji zelimo obrisati

    if(za_brisanje != nullptr){
        Erase(za_brisanje);
        return 1;
    }

    //ako ga ne nadje, znaci ne postoji pa se ne moze izbrisati, takodjer ako nije u pitanju multiset moze samo jednu vrijednost naci
    else
        return 0;
}



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!PROJEKAT IMPLEMENTACIJA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::TreeIterator::NadjiNajmanjiIterator(Cvor *cvor){

        if(cvor == nullptr)
            return nullptr;

        Cvor *trenutni = cvor;

        while(trenutni->ld != nullptr)
            trenutni = trenutni->ld;

        return trenutni;

}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Reverse_Iterator::NadjiNajveci(Cvor *cvor){

        if(cvor == nullptr)
            return nullptr;

        Cvor *trenutni = cvor;

        while(trenutni->dd != nullptr)
            trenutni = trenutni->dd;

        return trenutni;

}


template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::TreeIterator::NadjiSljedbenikaIterator(Cvor *cvor){
            if(cvor->dd != nullptr)  //ako ima desno dijete, onda je sljedbenik najmanje dijete koje je lijevo od trenutnog desnog djeteta
            return NadjiNajmanjiIterator(cvor->dd); //bukvalno trazi najmanji element u podstablu

        Cvor *trenutni = cvor;

        if(trenutni == nullptr)
            return nullptr;
        //trenutni->rod != nullptr 

            while(trenutni->rod != nullptr && trenutni == trenutni->rod->dd) //vracamo se gore  //kljucna promjena, jer nemamo pristup korijenu 
                trenutni = trenutni->rod;

        //sve dok trenutni nije lijevo dijete roditelja
        if(trenutni->rod  == nullptr)
            return nullptr;
        else
            return trenutni->rod;

}

template<typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Reverse_Iterator::NadjiPrethodnikaIterator(Cvor *cvor){

        if(cvor->ld != nullptr)  //ako lijevo dijete nije null, naci najveci broj na toj strani
            return NadjiNajveci(cvor->ld); 

            Cvor *trenutni = cvor;

            if(trenutni == nullptr) //ako mi je prosljedjeni cvor nullptr, radi nista
                return nullptr;
            //trenutni->rod != nullptr 


            while(trenutni->rod != nullptr && trenutni == trenutni->rod->ld) //vracamo se gore
                    trenutni = trenutni->rod;

            if(trenutni->rod == nullptr)
                return nullptr;
            else
                return trenutni->rod;

}

template<typename Tip>
int Stablo<Tip>::heightRek(Cvor *cvor){
    if(cvor == nullptr) //!cvor
        return 0;

    return 1+ max(heightRek(cvor->ld),heightRek(cvor->dd));

}

template<typename Tip>
Tip Stablo<Tip>::operator[](int k){

    Cvor *trenutni = korijen;

    Cvor *najmanji = NadjiNajmanji(trenutni);

     if(k == 0)
        return najmanji->element;
     

     if (k > getBrojElemenata())
        return -1;

     Cvor *sljedbenik = NadjiSljedbenika(najmanji);
     Cvor *novi;
     int i = 1;
     
     while(sljedbenik != nullptr){

        if(k == i)
            return sljedbenik -> element;
        else
            novi = NadjiSljedbenika(sljedbenik);

        sljedbenik = novi;
        i++;

     }
     
}



#endif
