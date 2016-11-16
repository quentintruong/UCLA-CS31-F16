//
//  main.cpp
//  Project 2
//
//  Created by Quentin Truong on 10/7/16.
//  Copyright © 2016 CS31. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    //declare variables for user input
    
    string ident;
    double expRev;
    string country;
    
    //gather user input
    
    cout << "Identification: ";
    getline(cin, ident);
    
    cout << "Expected revenue (in millions): ";
    cin >> expRev;
    cin.ignore(10000, '\n');
    
    cout << "Country: ";
    getline(cin, country);
    
    //calculate amount
    
    double amount = 0;
    if (expRev > 50)
    {
        amount += (expRev - 50) * 0.23;
        expRev = 50;
    }
    if (expRev > 20)
    {
        if (country == "UAE" || country == "Turkey")
        {
            amount += (expRev - 20) * 0.217;
        }
        else
        {
            amount += (expRev - 20) * 0.203;
        }
        expRev = 20;
    }
    if (expRev > 0)
        amount += (expRev * 0.181);
    
    //output dashes to signal results of the program
    
    cout << "---" << endl;
    
    //output some result
    
    if (ident == "")
        cout << "You must enter a property identification.";
    else if (expRev < 0)
        cout << "The expected revenue must be nonnegative.";
    else if (country == "")
        cout << "You must enter a country.";
    else
    {
        cout.setf(ios::fixed);
        cout.precision(3);
        cout << "The license fee for " << ident << " is $" << amount << " million.";
    }
}
