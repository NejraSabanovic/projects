#include "stablo.h"
#include<iostream>
using namespace std;


int main(){

  //TESTNI PROGRAM//

    Stablo<int> S;
     S.Insert(20);
     S.Insert(10);
     S.Insert(30);
     S.Insert(9);
     S.Insert(8);
     S.Insert(25);
     S.Insert(35);
     S.Insert(8);
     S.Insert(40);


        /*
          20
          / \
        10   30
        / \  / \
       9    25 35
      / \      /\
     8           40
    
    */

    
    Stablo<int> T;
    T.Insert(20);
    //T.Insert(90);
    T.Insert(10);
    T.Insert(30);
    T.Insert(35);
    //T.Insert(1);

    /*

      20
      / \
    10   30
         /\
           35
      
    */

    if(daLiJePodstablo(S,T))
      cout<<"Stablo T jeste podstablo stabla S"<<endl;
    else
      cout<<"Stablo T nije podstablo stabla S"<<endl;

    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"Ispis stabla S preko iteratora"<<endl;

    for(auto it = S.Begin(); it != S.End(); it++)
      cout<<*it << " ";

    cout<<endl<<endl;

    cout<<"Ispis stabla T unazad preko reverse iteratora"<<endl;
    for(auto rev_it = T.rBegin(); rev_it != T.rEnd(); rev_it++)
      cout<<*rev_it << " ";

    cout<<endl<<endl;

    int k;
    cout<<"Unesite broj k " ;
    cin>>k;
    cout<<"Ispis elementa na "<< k <<"-tom mjestu stabla S"<<endl;
    cout<<S[k]<<endl;


    if(daLiJePodskup(S,T))
      cout<<"Stablo T jeste podskup stabla S"<<endl;
    else
      cout<<"Stablo T nije podskup stabla S"<<endl;




  
   

    



}
