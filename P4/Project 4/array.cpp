//
//  main.cpp
//  Project 4
//
//  Created by Quentin Truong on 11/6/16.
//  Copyright © 2016 QT. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void printArray(string a[], int n);
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);
void insert(string a[], int newPos, int oldPos);

int main() {
    cout << "appendToAll()" << endl;
    string p1[5] = { "hillary", "gary", "donald", "jill", "evan" };
    assert(appendToAll(p1, 5, "!!!") == 5);//succeeds basic
    printArray(p1, 5);
    string p2[5] = { "hillary", "gary", "donald", "jill", "evan" };
    assert(appendToAll(p2, -2, "!!") == -1);//fails if invalid array size
    //printArray(p2, 5);
    string p3[5] = { "hillary", "gary", "donald", "jill", "evan" };
    assert(appendToAll(p3, 0, "!!") == 0);//succeeds 0 array
    printArray(p3, 5);
    cout << "~~~~~~" << endl << endl;
    
    cout << "lookup()" << endl;
    string h[8] = { "jill", "hillary", "donald", "tim", "", "evan", "gary", "jill" };
    assert(lookup(h, 7, "evan") == 5);//succeeds basic
    assert(lookup(h, 7, "not_a_name") == -1);//fails basic
    assert(lookup(h, -2, "donald") == -1);//fails if invalid array size
    assert(lookup(h, 3, "donald") == 2);//succeeds on boundary
    assert(lookup(h, 1, "jill") == 0);//succeeds on first
    assert(lookup(h, 7, "gary") == 6);//succeeds on last
    assert(lookup(h, 7, "") == 4);//succeeds on empty string
    assert(lookup(h, 7, "JILL") == -1);//fails if target not in array (case-sensitive)
    assert(lookup(h, 8, "jill") == 0);//succeeds on keeping lowest position string
    cout << "~~~~~~" << endl << endl;
    
    cout << "positionOfMax()" << endl;
    string p4[6] = { "A", "B", "C", "a", "b", "c" };
    assert(positionOfMax(p4, 6) == 5);//succeeds last element
    assert(positionOfMax(p4, -2) == -1);//fails if invalid array size
    string p5[6] = { "c", "B", "C", "a", "b", "A" };
    assert(positionOfMax(p5, 6) == 0);//succeeds on first element
    string p6[6] = { "c", "B", "C", "a", "b", "c" };
    assert(positionOfMax(p6, 6) == 0);//succeeds on keeping lowest position string
    cout << "~~~~~~" << endl << endl;
    
    cout << "rotateLeft()" << endl;
    string running[5] = { "evan", "donald", "gary", "jill", "hillary" };
    assert(rotateLeft(running, 5, 1) == 1);//succeeds basic
    printArray(running, 5);
    string p7[5] = { "evan", "donald", "gary", "jill", "hillary" };
    assert(rotateLeft(p7, 5, 0) == 0);//succeeds start boundary
    printArray(p7, 5);
    string pb7[5] = { "evan", "donald", "gary", "jill", "hillary" };
    assert(rotateLeft(pb7, 5, 4) == 4);//succeeds end boundary
    printArray(pb7, 5);
    assert(rotateLeft(p7, -2, 4) == -1);//fails if invalid array size
    cout << "~~~~~~" << endl << endl;
    
    cout << "countRuns()" << endl;
    string d[9] = {"tim", "ajamu", "mike", "mike", "donald", "donald", "donald", "mike", "mike"};
    assert(countRuns(d, 9) == 5);//succeeds basic
    string p8[1] = {"a"};
    assert(countRuns(p8, 1) == 1);//succeds on a one element array
    assert(countRuns(p8, -2) == -1);//fails if invalid array size
    cout << "~~~~~~" << endl << endl;
    
    cout << "flip()" << endl;
    string folks[6] = { "ajamu", "mike", "", "tim", "mindy", "bill" };
    assert(flip(folks, 4) == 4);//succeeds basic even
    printArray(folks, 6);
    string p9[5] = { "a", "b", "c", "d", "e"};
    assert(flip(p9, 5) == 5);//succeeds basic odd
    printArray(p9, 5);
    string p10[6] = { "ajamu", "mike", "", "tim", "mindy", "bill" };
    assert(flip(p10, -2) == -1);//fails if invalid array size
    //printArray(p10, 6);
    cout << "~~~~~~" << endl << endl;
    
    cout << "differ()" << endl;
    string p11[6] = { "ajamu", "mike", "", "tim", "mindy", "bill" };
    string p12[5] = { "ajamu", "mike", "bill", "", "tim" };
    assert(differ(p11, 6, p12, 5) == 2);//succeeds basic
    assert(differ(p11, 2, p12, 1) == 1);//succeeds when equal till end of interesting elements
    assert(differ(p11, -2, p12, 1) == -1);//fails if invalid array size
    assert(differ(p11, 2, p12, -2) == -1);//fails if invalid array size
    cout << "~~~~~~" << endl << endl;
    
    cout << "subsequence()" << endl;
    string p13[20] = {"a", "b", "c", "d", "e", "b", "c", "d", "f", "f"};
    string p14[20] = {"e", "b"};
    assert(subsequence(p13, 8, p14, 2) == 4);//succeeds basic
    string p15[20] = {"a"};
    assert(subsequence(p13, 8, p15, 1) == 0);//succeeds start boundary
    string p16[20] = {"no"};
    assert(subsequence(p13, 8, p16, 1) == -1);//fails basic
    string p17[20] = {"f"};
    assert(subsequence(p13, 9, p17, 1) == 8);//succeds end boundary
    string p18[20] = {"f", "f"};
    assert(subsequence(p13, 10, p18, 2) == 8);//succeds end boundary
    cout << "~~~~~~" << endl << endl;
    
    cout << "lookupAny()" << endl;
    string names[10] = { "evan", "hillary", "mindy", "jill", "ajamu", "gary", "jill", "end"};
    string set1[10] = { "bill", "ajamu", "jill", "hillary" };//succeeds basic
    assert(lookupAny(names, 6, set1, 4) == 1);
    string set2[10] = { "bill", "ajamu", "jill"};//succeeds on returning lowest
    assert(lookupAny(names, 7, set2, 3) == 3);
    string set3[10] = {"evan"};
    assert(lookupAny(names, 7, set3, 1) == 0);//succeds start boundary
    string set4[10] = {"end"};
    assert(lookupAny(names, 8, set4, 1) == 7);//succeds start boundary
    cout << "~~~~~~" << endl << endl;
    
    cout << "insert()" << endl;
    string test[5] = {"", "B", "C", "D", "E"};
    insert(test, 0, 1);
    printArray(test, 5);
    cout << "~~~~~~" << endl << endl;
    
    cout << "separate()" << endl;
    string cand[10] = {"d", "g", "b", "c", "e", "f", "a"};
    assert(separate(cand, 7, "d") == 3);//succeeds basic
    printArray(cand, 7);
    string p19[6] = { "donald", "jill", "hillary", "tim", "evan", "bill" };
    assert(separate(p19, 6, "gary") == 3);//succeeds when separator is not in array
    printArray(p19, 6);
    string p20[4] = { "gary", "hillary", "jill", "donald" };//succeeds basic
    assert(separate(p20, 4, "hillary") == 2);
    printArray(p20, 4);
    string p21[4] = { "a", "b", "c", "d" };
    assert(separate(p21, 4, "e") == 4);//succeeds end boundary
    printArray(p21, 4);
    string p22[4] = { "a", "b", "c", "d" };
    assert(separate(p22, 4, "A") == 0);//succeeds start boundary
    printArray(p22, 4);
    string p23[4] = { "", "b", "c", "d" };
    assert(separate(p23, 4, "A") == 1);//succeeds ""
    printArray(p23, 4);
    cout << "~~~~~~" << endl << endl;
    
    cout << "~~~mySuccess~~~" << endl;
    
    string hh[7] = { "jill", "hillary", "donald", "tim", "", "evan", "gary" };
    assert(lookup(hh, 7, "evan") == 5);
    assert(lookup(hh, 7, "donald") == 2);
    assert(lookup(hh, 2, "donald") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "jill", "hillary", "gary", "mindy" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "gary?" && g[3] == "hillary?");
    
    string e[4] = { "donald", "tim", "", "evan" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string dd[5] = { "hillary", "hillary", "hillary", "tim", "tim" };
    assert(countRuns(dd, 5) == 2);
    
    string f[3] = { "gary", "donald", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "gary");
    
    assert(separate(h, 7, "gary") == 3);
    
    cout << "All tests succeeded" << endl;
    
    string hhh[7] = { "jill", "hillary", "donald", "tim", "", "evan", "gary" };
    assert(separate(hhh, 7, "gary") == 3);
    printArray(hhh,7);
    
}

void printArray(string a[], int n){
    for (int inc = 0; inc < n; inc++)
        cout << a[inc] << endl;
    cout << endl << endl;
}

int appendToAll(string a[], int n, string value){
    if (n < 0)
        return -1;//if invalid array size
    
    for (int inc = 0; inc < n; inc++){
        a[inc] += value;
    }
    
    return n;//if successful, returns n
}

int lookup(const string a[], int n, string target){
    if (n < 0)
        return -1;//if invalid array size
    
    for (int inc = 0; inc < n; inc++){
        if (a[inc] == target)
            return inc;//if successful, returns position
    }
    
    return -1;//if target not found in a[]
}

int positionOfMax(const string a[], int n){
    if (n < 0)
        return -1;//if invalid array size
    
    int pos = 0;
    
    for (int inc = 1; inc < n; inc++){
        if (a[pos] < a[inc]){
            pos = inc;
        }
    }
    
    return pos;//if successful, returns pos
}

int rotateLeft(string a[], int n, int pos){
    if (n < 0)
        return -1;//if invalid array size
    
    string temp = a[pos];
    for (int inc = pos; inc < n - 1; inc++){
        a[inc] = a[inc + 1];
    }
    a[n - 1] = temp;
    
    return pos;//if successful, returns n
}

int countRuns(const string a[], int n){
    if (n < 0)
        return -1;//if invalid array size
    
    int runs = 1;
    for (int inc = 1; inc < n; inc++){
        if (a[inc] != a[inc - 1])
            runs++;
    }
    
    return runs;
}

int flip(string a[], int n){
    if (n < 0)
        return -1;//if invalid array size
    
    int fwd = 0;
    int bwd = n - 1;
    
    while (fwd < bwd){
        string temp = a[fwd];
        a[fwd] = a[bwd];
        a[bwd] = temp;
        fwd++;
        bwd--;
    }
    
    return n;//if successful, returns n
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0)
        return -1;//if invalid array size
    if (n2 < 0)
        return -1;//if invalid array size
    
    int n = n1;
    if (n2 < n1)
        n = n2;
    
    for (int inc = 0; inc < n; inc++){
        if (a1[inc] != a2[inc]){
            return inc;//return pos of difference
        }
    }
    return n;//return the lower of n1, n2
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0)
        return -1;//if invalid array size
    if (n2 < 0)
        return -1;//if invalid array size
    
    int pos = 0;//iterates a1
    int inc = 0;//iterates a2
    while (pos < n1 && inc < n1 && inc < n2){
        //cout << "inc:" << inc << ":END. " << "pos:" << pos << ":END. " << endl;
        if (a1[pos] == a2[inc]){
            //cout << "IN" << endl;
            if (inc == n2 - 1){
                return pos - inc;
            }
            else{
                pos++;
                inc++;
            }
        }
        else{
            pos++;
            inc = 0;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0)
        return -1;//if invalid array size
    if (n2 < 0)
        return -1;//if invalid array size
    
    for (int pos1 = 0; pos1 < n1; pos1++){
        for (int pos2 = 0; pos2 < n2; pos2++){
            if (a1[pos1] == a2[pos2])
                return pos1;
        }
    }
    return -1;
}

int separate(string a[], int n, string separator){
    if (n < 0)
        return -1;//if invalid array size
    
    int inc = 0;
    for (int pos = 0; pos < n; pos++){
        if (a[pos] < separator){
            insert(a, 0, pos);
            inc++;
        }
        if (a[pos] == separator){
            insert(a, inc, pos);
        }
    }
    return inc;
}

void insert(string a[], int newPos, int oldPos){
    if (newPos < oldPos)
    {
        string temp = a[oldPos];
        for (int inc = oldPos; inc > newPos; inc--){
            a[inc] = a[inc - 1];
        }
        a[newPos] = temp;
    }
    else if (newPos > oldPos){
        string temp = a[oldPos];
        for (int inc = oldPos; inc < newPos; inc++){
            a[inc] = a[inc + 1];
        }
        a[newPos] = temp;
    }
}













