//
//  main.cpp
//  Project 5
//
//  Created by Quentin Truong on 11/10/16.
//  Copyright © 2016 QT. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[],
                   int nRules);
int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[],
                          int nRules,
                          const char document[]);
void print2D(char a[][MAX_WORD_LENGTH+1], int n);
void print1D(int a[], int n);
void print1DC(char a[], int n);

int main() {
    const int NRULES = 10;
    char w1[NRULES][MAX_WORD_LENGTH + 1] =  {"L",  "",   "1A",  "CA",  "DA",  "AA",  "BB",  "BB",  "BB", "L"};
    char w2[NRULES][MAX_WORD_LENGTH + 1] =  {"L",  "AA", "AA",  "AA",  "AA",  "DA",  "FF",  "FF",  "FF", "L"};
    int dist[NRULES] =                      {2,    1,    1,     -1,    2,     1,     2,     1,     1,    1};
    assert(normalizeRules(w1, w2, dist, NRULES) == 3);//checks empty word1, bad word1, bad dist, cross multiples, parallel multiples, distant multiples
    char doc[201] = "l       da l aa bb z ff";
    assert(calculateSatisfaction(w1, w2, dist, 3, doc) == 3);//checks multiple spaces
    
    const int NRULESB = 10;
    char w1B[NRULESB][MAX_WORD_LENGTH + 1] =  {"mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have"};
    char w2B[NRULESB][MAX_WORD_LENGTH + 1] =  {"scientist", "robot",  "plot", "assistant", "deranged", "Nefarious", "mad"};
    int distB[NRULESB] =                      {2, 4, 1, 3, 2, 1, 13};
    assert(normalizeRules(w1B, w2B, distB, NRULESB) == 4);//checks caps multiples
    assert(calculateSatisfaction(w1B, w2B, distB, 4, "") == 0);//checks empty doc
    
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"mad", "deranged", "nefarious", "have"};
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"scientist", "robot", "plot", "mad"};
    int test1dist[TEST1_NRULES] = {2, 4, 1, 13};
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES, "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES, "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES, "**** 2016 ****") == 0);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES, "  That plot: NEFARIOUS!") == 1);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES, "deranged deranged robot deranged robot robot") == 1);
    assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES, "That scientist said two mad scientists suffer from deranged-robot fever.") == 0);
    
    const int maxRule = 201;
    char maxWord1[maxRule][MAX_WORD_LENGTH+1] = {"A", "AA", "AAA", "AAAA", "AAAAA", "AAAAAA", "AAAAAAA", "AAAAAAAA", "AAAAAAAAA", "AAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAAA", "AAAAAAAAAAAAA", "AAAAAAAAAAAAAA", "AAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "B", "BB", "BBB", "BBBB", "BBBBB", "BBBBBB", "BBBBBBB", "BBBBBBBB", "BBBBBBBBB", "BBBBBBBBBB", "BBBBBBBBBBB", "BBBBBBBBBBBB", "BBBBBBBBBBBBB", "BBBBBBBBBBBBBB", "BBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBBBBB", "C", "CC", "CCC", "CCCC", "CCCCC", "CCCCCC", "CCCCCCC", "CCCCCCCC", "CCCCCCCCC", "CCCCCCCCCC", "CCCCCCCCCCC", "CCCCCCCCCCCC", "CCCCCCCCCCCCC", "CCCCCCCCCCCCCC", "CCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCCCCC", "D", "DD", "DDD", "DDDD", "DDDDD", "DDDDDD", "DDDDDDD", "DDDDDDDD", "DDDDDDDDD", "DDDDDDDDDD", "DDDDDDDDDDD", "DDDDDDDDDDDD", "DDDDDDDDDDDDD", "DDDDDDDDDDDDDD", "DDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDDDDD", "E", "EE", "EEE", "EEEE", "EEEEE", "EEEEEE", "EEEEEEE", "EEEEEEEE", "EEEEEEEEE", "EEEEEEEEEE", "EEEEEEEEEEE", "EEEEEEEEEEEE", "EEEEEEEEEEEEE", "EEEEEEEEEEEEEE", "EEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEEEEE", "F", "FF", "FFF", "FFFF", "FFFFF", "FFFFFF", "FFFFFFF", "FFFFFFFF", "FFFFFFFFF", "FFFFFFFFFF", "FFFFFFFFFFF", "FFFFFFFFFFFF", "FFFFFFFFFFFFF", "FFFFFFFFFFFFFF", "FFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFF", "G", "GG", "GGG", "GGGG", "GGGGG", "GGGGGG", "GGGGGGG", "GGGGGGGG", "GGGGGGGGG", "GGGGGGGGGG", "GGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGGG", "GGGGGGGGGGGGGG", "GGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGGGGG", "H", "HH", "HHH", "HHHH", "HHHHH", "HHHHHH", "HHHHHHH", "HHHHHHHH", "HHHHHHHHH", "HHHHHHHHHH", "HHHHHHHHHHH", "HHHHHHHHHHHH", "HHHHHHHHHHHHH", "HHHHHHHHHHHHHH", "HHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHHHHH", "I", "II", "III", "IIII", "IIIII", "IIIIII", "IIIIIII", "IIIIIIII", "IIIIIIIII", "IIIIIIIIII", "IIIIIIIIIII", "IIIIIIIIIIII", "IIIIIIIIIIIII", "IIIIIIIIIIIIII", "IIIIIIIIIIIIIII", "IIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIIIIII", "J", "JJ", "JJJ", "JJJJ", "JJJJJ", "JJJJJJ", "JJJJJJJ", "JJJJJJJJ", "JJJJJJJJJ", "JJJJJJJJJJ", "JJJJJJJJJJJ", "JJJJJJJJJJJJ", "JJJJJJJJJJJJJ", "JJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJJJJ"};
    char maxWord2[maxRule][MAX_WORD_LENGTH+1] = {"A", "AA", "AAA", "AAAA", "AAAAA", "AAAAAA", "AAAAAAA", "AAAAAAAA", "AAAAAAAAA", "AAAAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAAA", "AAAAAAAAAAAAA", "AAAAAAAAAAAAAA", "AAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "B", "BB", "BBB", "BBBB", "BBBBB", "BBBBBB", "BBBBBBB", "BBBBBBBB", "BBBBBBBBB", "BBBBBBBBBB", "BBBBBBBBBBB", "BBBBBBBBBBBB", "BBBBBBBBBBBBB", "BBBBBBBBBBBBBB", "BBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBBBB", "BBBBBBBBBBBBBBBBBBBB", "C", "CC", "CCC", "CCCC", "CCCCC", "CCCCCC", "CCCCCCC", "CCCCCCCC", "CCCCCCCCC", "CCCCCCCCCC", "CCCCCCCCCCC", "CCCCCCCCCCCC", "CCCCCCCCCCCCC", "CCCCCCCCCCCCCC", "CCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCCCCCCC", "D", "DD", "DDD", "DDDD", "DDDDD", "DDDDDD", "DDDDDDD", "DDDDDDDD", "DDDDDDDDD", "DDDDDDDDDD", "DDDDDDDDDDD", "DDDDDDDDDDDD", "DDDDDDDDDDDDD", "DDDDDDDDDDDDDD", "DDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDDDD", "DDDDDDDDDDDDDDDDDDDD", "E", "EE", "EEE", "EEEE", "EEEEE", "EEEEEE", "EEEEEEE", "EEEEEEEE", "EEEEEEEEE", "EEEEEEEEEE", "EEEEEEEEEEE", "EEEEEEEEEEEE", "EEEEEEEEEEEEE", "EEEEEEEEEEEEEE", "EEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEEEE", "EEEEEEEEEEEEEEEEEEEE", "F", "FF", "FFF", "FFFF", "FFFFF", "FFFFFF", "FFFFFFF", "FFFFFFFF", "FFFFFFFFF", "FFFFFFFFFF", "FFFFFFFFFFF", "FFFFFFFFFFFF", "FFFFFFFFFFFFF", "FFFFFFFFFFFFFF", "FFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFF", "G", "GG", "GGG", "GGGG", "GGGGG", "GGGGGG", "GGGGGGG", "GGGGGGGG", "GGGGGGGGG", "GGGGGGGGGG", "GGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGGG", "GGGGGGGGGGGGGG", "GGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGGGG", "GGGGGGGGGGGGGGGGGGGG", "H", "HH", "HHH", "HHHH", "HHHHH", "HHHHHH", "HHHHHHH", "HHHHHHHH", "HHHHHHHHH", "HHHHHHHHHH", "HHHHHHHHHHH", "HHHHHHHHHHHH", "HHHHHHHHHHHHH", "HHHHHHHHHHHHHH", "HHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHHHH", "HHHHHHHHHHHHHHHHHHHH", "I", "II", "III", "IIII", "IIIII", "IIIIII", "IIIIIII", "IIIIIIII", "IIIIIIIII", "IIIIIIIIII", "IIIIIIIIIII", "IIIIIIIIIIII", "IIIIIIIIIIIII", "IIIIIIIIIIIIII", "IIIIIIIIIIIIIII", "IIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIIIII", "IIIIIIIIIIIIIIIIIIII", "J", "JJ", "JJJ", "JJJJ", "JJJJJ", "JJJJJJ", "JJJJJJJ", "JJJJJJJJ", "JJJJJJJJJ", "JJJJJJJJJJ", "JJJJJJJJJJJ", "JJJJJJJJJJJJ", "JJJJJJJJJJJJJ", "JJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJJJ", "JJJJJJJJJJJJJJJJJJJJ"};
    int maxDist[maxRule] = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200};
    int maxR = normalizeRules(maxWord1, maxWord2, maxDist, maxRule);//checks large number of rules
    assert(calculateSatisfaction(maxWord1, maxWord2, maxDist, maxR, "A A A A A A A A A A B B B B B B B B B B C C C C C C C C C C D D D D D D D D D D E E E E E E E E E E F F F F F F F F F F G G G G G G G G G G H H H H H H H H H H I I I I I I I I I I J J J J J J J J J J ") == 10);//checks many word document
    assert(calculateSatisfaction(maxWord1, maxWord2, maxDist, maxR, "AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCDDDDDDDDDDDDDDDDDDDDEEEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFFFFFFFGGGGGGGGGGGGGGGGGGGGHHHHHHHHHHHHHHHHHHHHIIIIIIIIIIIIIIIIIIIIJJJJJJJJJJJJJJJJJJJJ") == 0);//checks many character one word document
    //print2D(maxWord1, maxRule);
    
    const int minRule = 0;
    char minWord1[minRule][MAX_WORD_LENGTH+1] = {};
    char minWord2[minRule][MAX_WORD_LENGTH+1] = {};
    int minDist[minRule] = {};
    int minR = normalizeRules(minWord1, minWord2, minDist, minRule);
    assert(calculateSatisfaction(minWord1, minWord2, minDist, minR, "") == 0);//checks no rules with empty doc
    assert(calculateSatisfaction(minWord1, minWord2, minDist, minR, " ") == 0);//checks no rules with space doc
    assert(calculateSatisfaction(minWord1, minWord2, minDist, minR, "should return zero still") == 0);//checks no rules against normal doc
    
    const int badRule = 1;
    char badWord1[badRule][MAX_WORD_LENGTH+1] = {"1"};
    char badWord2[badRule][MAX_WORD_LENGTH+1] = {"!"};
    int badDist[badRule] = {1};
    assert(normalizeRules(badWord1, badWord2, badDist, badRule) == 0);//checks one bad/no rule
    assert(calculateSatisfaction(badWord1, badWord2, badDist, 0, "") == 0);//checks no rule against empty doc
    
    const int zRule = 8;
    char zWord1[zRule][MAX_WORD_LENGTH+1] = {"", "deranged", "!", "plot", "have", "mad", "plot", ""};
    char zWord2[zRule][MAX_WORD_LENGTH+1] = {"scientist", "robot", "wRong", "nefarious", "mad", "have", "nefaRious", "badrule"};
    int zDist[zRule] = {2, -4, 2, 5, 13, 4, 5, 4};
    assert(normalizeRules(zWord1, zWord2, zDist, -1) == 0);//negative
    assert(calculateSatisfaction(zWord1, zWord2, zDist, -1, "DERANGED ROBOT PLOT NEFARIOUS MAD HAVE") == 0);//negative
    assert(normalizeRules(zWord1, zWord2, zDist, zRule) == 2);//various
    assert(calculateSatisfaction(zWord1, zWord2, zDist, 2, "1") == 0);
    assert(calculateSatisfaction(zWord1, zWord2, zDist, 2, " 1") == 0);
    assert(calculateSatisfaction(zWord1, zWord2, zDist, 2, "DERANGED ROBOT PLOT NEFARIOUS MAD HAVE") == 2);
    
    cout << "All tests succeeded" << endl;
}

int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[],
                   int nRules){
    int r = 0;
    if (nRules < 0)//"Treat a negative nRules parameter as if it were 0"
        nRules = 0;
    bool keep = true;
    
    for (int i = 0; i < nRules; i++){
        keep = true;
        if (strlen(word1[i]) < 1 || strlen(word2[i]) < 1)//"Every word is at least one letter long"
            keep = false;
        
        for (int m = 0; word1[i][m] != '\0'; m++){
            if (isalpha(word1[i][m]) == false)//"contains no characters other than lower case letters"
                keep = false;
            else
                word1[i][m] = tolower(word1[i][m]);
        }
        for (int m = 0; word2[i][m] != '\0'; m++){
            if (isalpha(word2[i][m]) == false)
                keep = false;
            else
                word2[i][m] = tolower(word2[i][m]);
                
        }
        if (keep == false){
            for (int w = i; w < nRules - 1; w++){
                strcpy(word1[w], word1[w + 1]);
                strcpy(word2[w], word2[w + 1]);
                distance[w] = distance[w + 1];
            }
            strcpy(word1[nRules - 1], "");
            strcpy(word2[nRules - 1], "");
            
            nRules--;
            i--;
        }
    }
    
    for (int i = 0; i < nRules; i++){
        int remove = i;
        keep = true;
        
        if (distance[i] <= 0)//"Every distance is positive"
            keep = false;
        
        for (int k = i + 1; k < nRules; k++){//"No two rules in the collection have both the same w1 words and the same w2 words, in either order"
            if ((strcmp(word1[i], word1[k]) == 0 && strcmp(word2[i], word2[k]) == 0) ||
                (strcmp(word1[i], word2[k]) == 0 && strcmp(word2[i], word1[k]) == 0)){
                keep = false;
                if (distance[i] > distance[k]){//"distance value is the lesser of the two distance values"
                    remove = k;
                }
            }
        }
        if (keep == false){//"remove"
            for (;remove < nRules - 1; remove++){
                strcpy(word1[remove], word1[remove + 1]);
                strcpy(word2[remove], word2[remove + 1]);
                distance[remove] = distance[remove + 1];
            }
            strcpy(word1[nRules - 1], "");
            strcpy(word2[nRules - 1], "");
            
            nRules--;
            i--;
        }
        else
            r++;
    }
    return r;
}

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[],
                          int nRules,
                          const char document[]){
    if (nRules < 0)//"Treat a negative nRules parameter as if it were 0"
        nRules = 0;
    int satis = 0;
    char myDoc[201][201];
    int dist[201];
    int wordPos = 0;
    int charPos = 0;
    for (int i = 0; document[i] != '\0'; i++){
        if (isalpha(document[i]) != 0){//"non-alphabetic characters other than spaces are to be ignored"
            myDoc[wordPos][charPos] = tolower(document[i]);//"upper case letters are to be treated as if they were lower case"
            charPos++;
            myDoc[wordPos][charPos] = '\0';
        }
        else if (document[i] == ' '){//"words are separated by one or more space characters"
            wordPos++;
            charPos = 0;
            while (document[i + 1] == ' '){
                i++;
            }
        }
    }
    
    for (int i = 0; i < nRules; i++)
        dist[i] = distance[i];
    
    for (int pos = 0; pos <= wordPos; pos++){
        for (int r = 0; r < nRules; r++){
            if (strcmp(word1[r], myDoc[pos]) == 0){
                for (int d = 1; d <= dist[r]; d++){
                    if (pos + d <= wordPos && strcmp(word2[r], myDoc[pos + d]) == 0){
                        satis++;
                        dist[r] = 0;
                    }
                }
            }
            else if (strcmp(word2[r], myDoc[pos]) == 0){
                for (int d = 1; d <= dist[r]; d++){
                    if (pos + d <= wordPos && strcmp(word1[r], myDoc[pos + d]) == 0){
                        satis++;
                        dist[r] = 0;
                    }
                }
            }
        }
    }
    return satis;//"function must return the number of rules that the document satisfies"
}

void print2D(char a[][MAX_WORD_LENGTH+1], int n){
    for (int i = 0; i < n; i++){
        for (int k = 0; a[i][k] != '\0'; k++){
            cout << a[i][k];
        }
        cout << " ";
    }
    cout << endl;
}

void print1D(int a[], int n){
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

void print1DC(char a[], int n){
    for (int i = 0; i < n; i++){
        cout << a[i];
    }
    cout << endl;
}
