//
//  main.cpp
//  Project 3
//
//  Created by Quentin Truong on 10/22/16.
//  Copyright © 2016 QT. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <string>
#include <cassert>
using namespace std;

int countVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
bool isValidDigits(string digits);
bool isValidPartyCode(char partyCode);
bool isValidStateForecast(string stateForecast);
string stringToUpper(string s);
bool hasCorrectSyntax(string pollData);


int main() {
    //CHECKS THE TESTS
    if (isValidUppercaseStateCode("CA"))
        cout << "AY00" << endl;
    if (isValidUppercaseStateCode("AC"))
        cout << "AN0" << endl;
    
    if (isValidDigits("1"))
        cout << "BY1" << endl;
    if (isValidDigits("10"))
        cout << "BY2" << endl;
    if (isValidDigits("100"))
        cout << "BN3" << endl;
    if (isValidDigits("AA"))
        cout << "BN4" << endl;
    
    if (isValidPartyCode('D'))
        cout << "CY5" << endl;
    if (isValidPartyCode('1'))
        cout << "CN6" << endl;
    
    if (isValidStateForecast("TX38R"))
        cout << "DY7" << endl;
    if (isValidStateForecast("T3R"))
        cout << "DN8" << endl;
    if (isValidStateForecast("AA38R"))
        cout << "DN9" << endl;
    if (isValidStateForecast("TX3R"))
        cout << "DY10" << endl;
    if (isValidStateForecast("TXRRR"))
        cout << "DN11" << endl;
    if (isValidStateForecast("CA55D"))
        cout << "DY12" << endl;
    if (isValidStateForecast("HI 4D"))
        cout << "DN13" << endl;

    if (hasCorrectSyntax("hI4D"))
        cout << "EY14" << endl;
    if (hasCorrectSyntax("TX38RCA55DMS6RNY29DUT06L"))//SPECS
        cout << "EY15" << endl;
    if (hasCorrectSyntax("TX388RCA55DMS6RNY29DUT06L"))
        cout << "EN16" << endl;
    if (hasCorrectSyntax("TXRCA55DMS6RNY29DUT06L"))
        cout << "EN17" << endl;
    if (hasCorrectSyntax("TX38RRCA55DMS6RNY29DUT06L"))
        cout << "EN18" << endl;
    if (hasCorrectSyntax("TX38R CA55DMS6RNY29DUT06L"))
        cout << "EN19" << endl;
    if (hasCorrectSyntax("TX38RAA55DMS6RNY29DUT06L"))
        cout << "EN20" << endl;
    if (hasCorrectSyntax("TX38RCA55D"))//SPECS
        cout << "EY21" << endl;
    if (hasCorrectSyntax("MX38RCA55D"))//SPECS
        cout << "EN22" << endl;
    if (hasCorrectSyntax("MA38RCA55D"))
        cout << "EY23" << endl;
    if (hasCorrectSyntax(" MA38RCA55D"))
        cout << "EN24" << endl;
    if (hasCorrectSyntax(" MA38RCA55D "))
        cout << "EN25" << endl;
    if (hasCorrectSyntax("MA3MCA5M"))
        cout << "EY26" << endl;
    
    int votesR = -999;
    if (countVotes("TX0R", 'R', votesR) == 2 ){
        cout << "FY27: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("TX11RTX11R", 'R', votesR) == 0){
        cout << "FY28: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("TX38RCA55DMS6RNY29DUT06L", 'R', votesR) == 0){
        cout << "FY29: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("TX38RCA55DMS6RNY29DUT06L", 'L', votesR) == 0){
        cout << "FY30: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("TXAR", 'R', votesR) == 1 ){
        cout << "FY31: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("TX33R", '3', votesR) == 3 ){
        cout << "FY32: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("", 'd', votesR) == 0 ){
        cout << "FY33:" << votesR << endl;
    }
    votesR = -999;
    if (countVotes(" TX38RCA55DMs6rnY29dUT06L", 'd', votesR) == 0 ){
        cout << "FN34: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("TX38 RCA55DMs6rnY29dUT06L", 'd', votesR) == 0 ){
        cout << "FN35: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("tx38rCA55DMs6rnY29dUT06L", 'R', votesR) == 0 ){
        cout << "FY36: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("tx38CA55DMs6rnY29dUT06L", 'R', votesR) == 0 ){
        cout << "FN37: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("tx38rCA55DMs6rnY29dUT06L", '.', votesR) == 0 ){
        cout << "FN38: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("tx38rCA55DMs6rnY29dUT06LL", 'l', votesR) == 1 ){
        cout << "FY39: " << votesR << endl;
    }
    votesR = -999;
    if (countVotes("tx0rca55d", 'r', votesR) == 2 ){
        cout << "FY40: " << votesR << endl;
    }
    
    assert(hasCorrectSyntax("TX38RCA55D"));
    assert(!hasCorrectSyntax("MX38RCA55D"));
    int votes;
    votes = -999;    // so we can detect whether countVotes sets votes
    assert(countVotes("TX38RCA55DMs6rnY29dUT06L", 'd', votes) == 0  && votes == 84);
    votes = -999;    // so we can detect whether countVotes sets votes
    assert(countVotes("TX38RCA55D", '%', votes) == 3  &&  votes == -999);

    cout << "All tests succeeded" << endl;
    
    return 0;
}

bool isValidUppercaseStateCode(string stateCode){//CHECKS STATECODE
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
    "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
    "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isValidDigits(string digits){//CHECKS ELECTORAL VOTES
    if (digits.size() == 1){
        return isdigit(digits[0]);
    }
    if (digits.size() == 2){
        return (isdigit(digits[0]) && isdigit(digits[1]));
    }
    return false;
}

bool isValidPartyCode(char partyCode){//CHECKS PARTYCODE
    return (isalpha(partyCode));
}

bool isValidStateForecast(string stateForecast){//CHECKS ORDER, STATECODE, VOTES, AND PARTYCODE FOR ONE STATEFORECAST
    //CHECK SIZE
    if (stateForecast.size() < 4 || stateForecast.size() > 5)
        return false;
    
    //CHECK STATECODE
    if (isValidUppercaseStateCode(stateForecast.substr(0,2)) == false)
        return false;
    else
        stateForecast = stateForecast.substr(2);
    
    //CHECK DIGITS IF 1
    if (stateForecast.size() == 2){
        if (isValidDigits(stateForecast.substr(0,1)) == false)
            return false;
        else
            stateForecast = stateForecast.substr(1);
    }
    
    //CHECK DIGITS IF 2
    if (stateForecast.size() == 3){
        if (isValidDigits(stateForecast.substr(0,2)) == false)
            return false;
        else
            stateForecast = stateForecast.substr(2);
    }
    
    //CHECK PARTYCODE
    if (isValidPartyCode(stateForecast[0]) == false)
        return false;
    
    return true;
}

bool hasCorrectSyntax(string pollData){
    pollData = stringToUpper(pollData);
    
    while (pollData.size() > 0){
        if (pollData.size() < 4)
            return false;
        else if (isValidStateForecast(pollData.substr(0, 4)))
            pollData = pollData.substr(4);
        else if (isValidStateForecast(pollData.substr(0, 5)))
            pollData = pollData.substr(5);
        else
            return false;
    }
    return true;
}

string stringToUpper(string s){
    for (int i = 0; i < s.size(); i++){
        s[i] = toupper(s[i]);
    }
    return s;
}

int countVotes(string pollData, char party, int& voteCount){//take polldata, find first 4 or 5, depending which fits, look at that temp string. see how many votes. if equal to 0, return 2. else, see if party matches the temp strings party. if so, add votes to votecount. repeat.
    int oldVoteCount = voteCount;
    pollData = stringToUpper(pollData);
    if (hasCorrectSyntax(pollData) == false){
        return 1;
    }
    party = toupper(party);
    if (isValidPartyCode(party) == false){
        return 3;
    }
    
    voteCount = 0;
    while (pollData.size() > 0){
        string tempData = "";
        int votesLength = 1;
        if (isValidStateForecast(pollData.substr(0, 4))){
            tempData = pollData.substr(0, 4);
            pollData = pollData.substr(4);
        }
        else{
            tempData = pollData.substr(0, 5);
            pollData = pollData.substr(5);
            votesLength = 2;
        }
        if (stoi(tempData.substr(2, votesLength), nullptr, 10) == 0){
            voteCount = oldVoteCount;
            return 2;
        }
        int myVotes = stoi(tempData.substr(2, votesLength), nullptr, 10);
        char myParty = tempData[2+votesLength];
        if (myParty == party)
            voteCount += myVotes;
    }
    return 0;
}
