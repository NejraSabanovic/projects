#include <iostream>
#include "CurrencyGraph.h"

using namespace std;


int main(){

    //CurrencyGraph G ;
    CurrencyGraph  G;
    G.addCurrency("USD","EUR",0.9238);
    G.addCurrency("USD","GBP",0.8200);
    G.addCurrency("INR","EUR",0.0113);
    G.addCurrency("EUR","TRY",20.3457);
    G.addCurrency("USD","TRY",18.7963);
    G.addCurrency("TRY","INR",4.3449);
    G.addCurrency("CAD","USD",0.7461);
    G.addCurrency("CAD","EUR",0.6893);
    G.addCurrency("CAD","GBP",0.6121);
    G.addCurrency("BAM","CAD",0.7415);
    G.addCurrency("EUR","BAM",1.9558);
    G.addCurrency("BAM","USD",0.5531);
    G.addCurrency("EUR","HRK",7.5345);
    G.addCurrency("GBP","BAM",2.2031);


    cout<<G.getConversion("BAM","TRY")<<endl;
    











}
