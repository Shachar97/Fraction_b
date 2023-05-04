/**
 * Demo file for the exercise on Fractions
 *
 * @author Shachar Ketz
 * @since 2023-05
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/Fraction.hpp"

using namespace ariel;


int main() {

    cout<<"Slicing a cake!" << endl;
    float friends;
    cout<<"Danny have a birthday party, his mother baked cake" << endl;

    do{
        cout << ">Enter positive number (recommend 0-5)represent how many friends come to the party: "<<endl;
        cin >> friends;
    }while((friends<0)||friends>5);
    
    cout << "to the party showed up "<< friends << " of Danny's friends. so his mother should slice theno cake to "<<friends+1<<" pieces"<<endl;
    Fraction cake(1,1);
    Fraction child_piece;
    for(size_t i=1 ; i<=friends; i++){
        cout << "for kid number "<<i<<": "<<endl;
        cin >> child_piece;
        while(((cake-child_piece)<=0) || (child_piece<0)){
            cout<<"{"<<cake<< " - " <<child_piece<<" = "<<cake-child_piece<<"}"<<endl;
            cout<<">illegal slice, try to choose smaller piece: ";
            cin >> child_piece;
        }
        cout << "mother slice "<<child_piece<<" of the whole cake."<<endl;
        cout<<"from the whole cake "<<cake<< " - " <<child_piece<<" = "<<cake-child_piece<<" had left"<<endl;
        cake -= child_piece;
    }
    cout <<"Danny got what left of the cake which mean he got "<<cake << " of the cake"<<endl;

    cout<<"~~~~~~~~~~~~"<<endl<<endl;
    cout<<"mother cooked another cake, now she ask each kid what size he want from the left part of the cake"<<endl;
    cake.setNumerator(1);
    cake.setDenominator(1);
    for(size_t i=1 ; i<=friends; i++){
        cout << "for kid number "<<i<<": "<<endl;
        cin >> child_piece;
        while(child_piece<0){
            cout<<"{"<<cake<< " - " <<child_piece<<" = "<<cake-child_piece<<"}"<<endl;
            cout<<">illegal slice, try to choose smaller piece: ";
            cin >> child_piece;
        }
        cout << "mother slice "<<child_piece<<" of from what left."<<endl;
        cout<<child_piece<< " of " <<cake<<" cake "<<" is "<<cake*child_piece<<" had left"<<endl;
        child_piece *=cake;
        cout<<"from the cake "<<cake<< " - " <<child_piece<<" = "<<cake-child_piece<<" had left"<<endl;
        cake -= child_piece;
    }
    cout <<"Danny got what left of the cake which mean he got "<<cake << " of the cake"<<endl;

}
