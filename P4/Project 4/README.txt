Fall 2016 CS 31
Programming Assignment 4
Ask Your Boss for Arrays

Time due: 9:00 PM Monday, November 7

Before you ask questions about this specification, see if your question has already been addressed by the Project 4 FAQ. And read the FAQ before you turn in this project, to be sure you didn't misinterpret anything.

As you gain experience with arrays, you'll discover that many applications do the same kinds of things with them (e.g., find where an item is in an array, or check whether two arrays differ). You'll find that it's helpful to have a library of useful functions that manipulate arrays. (For our purposes now, a library is a collection of functions that developers can call instead of having to write them themselves. For a library to be most useful, the functions in it should be related and organized around a central theme. For example, a screen graphics library might have functions that allow you to draw shapes like lines and circles on the screen, move them around, fill them with color, etc. In this view, the Standard C++ library is really a collection of libraries: a string library, a math library, an input/output library, and much more.)

Your assignment is to produce a library that provides functions for many common manipulations of arrays of strings. For example, one function will find where a string occurs in an unordered array of strings. Another will change the order of strings in an array. For each function you must write, this specification will tell you its interface (what parameters it takes, what it returns, and what it must do). It's up to you to decide on the implementation (how it will do it).

The source file you turn in will contain all the functions and a main routine. You can have the main routine do whatever you want, because we will rename it to something harmless, never call it, and append our own main routine to your file. Our main routine will thoroughly test your functions. You'll probably want your main routine to do the same. If you wish, you may write functions in addition to those required here. We will not directly call any such additional functions. If you wish, your implementation of a function required here may call other functions required here.

The program you turn in must build successfully, and during execution, no function (other than main) may read anything from cin or write anything to cout. If you want to print things out for debugging purposes, write to cerr instead of cout. When we test your program, we will cause everything written to cerr to be discarded instead — we will never see that output, so you may leave those debugging output statements in your program if you wish.

All of the functions you must write take at least two parameters: an array of strings, and the number of items the function will consider in the array, starting from the beginning. For example, in

string people[5] = { "hillary", "gary", "donald", "jill", "evan" };
int i = lookup(people, 3, "evan");  // should return -1 (not found)
even though the array has 5 elements, only the first 3 had values we were interested in for this call to the function; the function must not examine the others.

Notwithstanding each function's behavior described below, all functions that return an int must return −1 if they are passed any bad arguments (e.g. a negative array size, or a position that would require looking at the contents of an element past the last element we're interested in). Unless otherwise noted, passing 0 to the function as the array size is not itself an error; it merely indicates the function should examine no elements of the array.

The one error your function implementations don't have to handle, because they can't, is when the caller of the function lies and says the array is bigger than it really is. For example, in this situation, the function lookup can't possibly know that the caller is lying about the number of interesting items in the array:

string people[5] = { "hillary", "gary", "donald", "jill", "evan" };
int i = lookup(people, 25, "tim");  // Bad call of function, but
		// your lookup implementation doesn't have to check for
		// this, because it can't.
To make your life easier, whenever this specification talks about strings being equal or about one string being less than or greater than another, the case of letters matters. This means that you can simply use comparison operators like == or < to compare strings. Because of the character collating sequence, all upper case letters come before all lower case letters, so don't be surprised. The FAQ has a note about string comparisons.

Here are the functions you must implement:

int appendToAll(string a[], int n, string value);
Append value to the end of each of the n elements of the array and return n. [Of course, in this and other functions, if n is negative, the paragraph above that starts "Notwithstanding" trumps this by requiring that the function return −1. Also, in the description of this function and the others, when we say "the array", we mean the n elements that the function is aware of.] For example:
string people[5] = { "hillary", "gary", "donald", "jill", "evan" };
int j = appendToAll(people, 5, "!!!");  // returns 5
    // now cand[0] is "hillary!!!", cand[1] is "gary!!!", ...,
    // and cand[4] is "evan!!!"
int lookup(const string a[], int n, string target);
Return the position of a string in the array that is equal to target; if there is more than one such string, return the smallest position number of such a matching string. Return −1 if there is no such string. As noted above, case matters: Do not consider "TIm" to be equal to "tIM". 

int positionOfMax(const string a[], int n);
Return the position of a string in the array such that that string is >= every string in the array. If there is more than one such string, return the smallest position in the array of such a string. Return −1 if the array has no elements. For example:
string cand[6] = { "jill", "hillary", "donald", "tim", "evan", "mike" };
int k = positionOfMax(cand, 6);   // returns 3, since  tim  is latest
                                  // in alphabetic order
int rotateLeft(string a[], int n, int pos);
Eliminate the item at position pos by copying all elements after it one place to the left. Put the item that was thus eliminated into the last position of the array. Return the original position of the item that was moved to the end. Here's an example:
string running[5] = { "evan", "donald", "gary", "jill", "hillary" };
int m = rotateLeft(running, 5, 1);  // returns 1
    // running now contains:  "evan", "gary", "jill", "hillary", "donald"
int countRuns(const string a[], int n);
Return the number of sequences of one or more consecutive identical items in a.
string d[9] = {
    "tim", "ajamu", "mike", "mike", "donald", "donald", "donald", "mike", "mike"
};
int p = countRuns(d, 9);  //  returns 5
	   //  The five sequences of consecutive identical items are
	   //    "tim"
	   //    "ajamu"
	   //    "mike", "mike"
	   //    "donald", "donald", "donald"
	   //    "mike", "mike"
int flip(string a[], int n);
Reverse the order of the elements of the array and return n. For example,
string folks[6] = { "ajamu", "mike", "", "tim", "mindy", "bill" };
int q = flip(folks, 4);  // returns 4
    // folks now contains:  "tim"  ""  "mike"  "ajamu"  "mindy"  "bill"
int differ(const string a1[], int n1, const string a2[], int n2);
Return the position of the first corresponding elements of a1 and a2 that are not equal. n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2. If the arrays are equal up to the point where one or both runs out, return whichever value of n1 and n2 is less than or equal to the other. For example,
string folks[6] = { "ajamu", "mike", "", "tim", "mindy", "bill" };
string group[5] = { "ajamu", "mike", "bill", "", "tim" };
int r = differ(folks, 6, group, 5);  //  returns 2
int s = differ(folks, 2, group, 1);  //  returns 1
int subsequence(const string a1[], int n1, const string a2[], int n2);
If all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins. If the subsequence appears more than once in a1, return the smallest such beginning position in the array. Return −1 if a1 does not contain a2 as a contiguous subsequence. (Consider a sequence of 0 elements to be a subsequence of any sequence, even one with no elements, starting at position 0.) For example,
string names[10] = { "evan", "hillary", "mindy", "jill", "ajamu", "gary" };
string names1[10] = { "hillary", "mindy", "jill" };
int t = subsequence(names, 6, names1, 3);  // returns 1
string names2[10] = { "evan", "jill" };
int u = subsequence(names, 5, names2, 2);  // returns -1
int lookupAny(const string a1[], int n1, const string a2[], int n2);
Return the smallest position in a1 of an element that is equal to any of the elements in a2. Return −1 if no element of a1 is equal to any element of a2. For example,
string names[10] = { "evan", "hillary", "mindy", "jill", "ajamu", "gary" };
string set1[10] = { "bill", "ajamu", "jill", "hillary" };
int v = lookupAny(names, 6, set1, 4);  // returns 1 (a1 has "hillary" there)
string set2[10] = { "tim", "donald" };
int w = lookupAny(names, 6, set2, 2);  // returns -1 (a1 has none)
int separate(string a[], int n, string separator);
Rearrange the elements of the array so that all the elements whose value is < separator come before all the other elements, and all the elements whose value is > separator come after all the other elements. Return the position of the first element that, after the rearrangement, is not < separator, or n if there are no such elements. For example,
string cand[6] = { "donald", "jill", "hillary", "tim", "evan", "bill" };
int x = separate(cand, 6, "gary");  //  returns 3
	// cand must now be
	//      "donald"  "evan"  "bill"  "jill"  "tim"  "hillary"
	// or   "evan"  "bill"  "donald"  "hillary"  "jill"  "tim"
	// or one of several other orderings.
	// All elements < "gary" (i.e., "evan", "bill", and "donald")
	//   come before all others
	// All elements > "gary" (i.e., "tim", "jill", and "hillary")
	//   come after all others
string cand2[4] = { "gary", "hillary", "jill", "donald" };
int y = separate(cand2, 4, "hillary");  //  returns 2
	// cand2 must now be either
	//      "gary"  "donald"  "hillary"  "jill"
	// or   "donald"  "gary"  "hillary"  "jill"
	// All elements < "hillary" (i.e., "donald" and "gary") come
        // before all others.
	// All elements > "hillary" (i.e., "jill") come after all others.
For each of the functions rotateLeft, flip, and separate, if the function is correctly implemented, you will earn one bonus point for that function if it does its job without creating any additional array.

Your program must not use any function templates from the algorithms portion of the Standard C++ library. If you don't know what the previous sentence is talking about, you have nothing to worry about. If you do know, and you violate this requirement, you will be required to take an oral examination to test your understanding of the concepts and architecture of the STL.

Your implementations must not use any global variables whose values may be changed during execution.

Your program must build successfully under both g++ with Linux and either Visual C++ or clang++.

The correctness of your program must not depend on undefined program behavior. Your program could not, for example, assume anything about t's value in the following, or even whether or not the program crashes:

	int main()
	{
	    string top[3] = { "hillary", "gary", "donald" };
	    string t = top[3];   // position 3 is out of range
	    …
What you will turn in for this assignment is a zip file containing these two files and nothing more:

A text file named array.cpp that contains the source code for your C++ program. Your source code should have helpful comments that explain any non-obvious code.

A file named report.doc or report.docx (in Microsoft Word format), or report.txt (an ordinary text file) that contains:
A brief description of notable obstacles you overcame.
A list of the test data that could be used to thoroughly test your functions, along with the reason for each test. You must note which test cases your program does not handle correctly. (This could happen if you didn't have time to write a complete solution, or if you ran out of time while still debugging a supposedly complete solution.) Notice that most of this portion of your report can be written just after you read the requirements in this specification, before you even start designing your program.
How nice! Your report this time doesn't have to contain any design documentation.

As with Project 3, a nice way to test your functions is to use the assert facility from the standard library. As an example, here's a very incomplete set of tests for Project 4:

	#include <iostream>
	#include <string>
	#include <cassert>
	using namespace std;

	int main()
	{
	    string h[7] = { "jill", "hillary", "donald", "tim", "", "evan", "gary" };
	    assert(lookup(h, 7, "evan") == 5);
	    assert(lookup(h, 7, "donald") == 2);
	    assert(lookup(h, 2, "donald") == -1);
	    assert(positionOfMax(h, 7) == 3);

	    string g[4] = { "jill", "hillary", "gary", "mindy" };
	    assert(differ(h, 4, g, 4) == 2);
	    assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?");
	    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "gary?" && g[3] == "hillary?");

	    string e[4] = { "donald", "tim", "", "evan" };
	    assert(subsequence(h, 7, e, 4) == 2);

	    string d[5] = { "hillary", "hillary", "hillary", "tim", "tim" };
	    assert(countRuns(d, 5) == 2);
	
	    string f[3] = { "gary", "donald", "mike" };
	    assert(lookupAny(h, 7, f, 3) == 2);
	    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "gary");
	
	    assert(separate(h, 7, "gary") == 3);
	
	    cout << "All tests succeeded" << endl;
	}
The reason for the one line of output at the end is to ensure that you can distinguish the situation of all tests succeeding from the case where one test silently crashes the program.

Make sure that if you were to replace your main routine with the one above, your program would build successfully under both g++ with Linux and either Visual C++ or clang++. (This means that even if you haven't figured out how to implement some of the functions, you must still have some kind of implementations for them, even if those implementations do nothing more than immediately return, say, 42.) If the program built with that main routine happens to run successfully, you'll probably get a pretty good correctness score.

By November 6, there will be links on the class webpage that will enable you to turn in your zip file electronically. Turn in the file by the due time above. Give yourself enough time to be sure you can turn something in, because we will not accept excuses like "My network connection at home was down, and I didn't have a way to copy my files and bring them to a SEASnet machine." There's a lot to be said for turning in a preliminary version of your program and report early (You can always overwrite it with a later submission). That way you have something submitted in case there's a problem later.

Project 4 Test Data

There were 84 test cases. The first 64 were worth 1.11 point each; the next 17 were worth .82 points each; the last three, worth one point each, were the bonuses you earned for certain functions that passed all tests but did not use an additional array. To run the test cases:

Remove the main routine from your array.cpp file.
Append the following text to the end of your array.cpp file, and build the resulting program.
For any test case you wish to try, run the program, providing as input the test number.
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

string c[6] = {
	"alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool separatecheck(const string a[], int n, int p, string separator)
{
	for (int k = 0; k < p; k++)
		if (a[k] >= separator)
			return false;
	for ( ; p < n  &&  a[p] == separator; p++)
		;
	for (int k = p; k < n; k++)
		if (a[k] <= separator)
			return false;
	string b[100];
	copy(a, a+n, b);
	sort(b, b+n);
	return equal(b, b+n, c);
}

void testone(int n)
{
	const int N = 6;

      // Act as if  a  were declared:
      //   string a[N] = {
      //       "alpha", "beta", "gamma", "gamma", "beta", "delta"
      //   };
      // This is done in a way that will probably cause a crash if
      // a[-1] or a[N] is accessed:  We place garbage in those positions.
	string aa[1+N+1] = {
		"", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
	};
	string* a = &aa[1];
	string* z = aa;
	a[-1].string::~string();
	a[N].string::~string();
	fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
	fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

	string b[N] = {
		"alpha", "beta", "gamma", "delta", "beta", "delta"
	};

	string d[9] = {
		"alpha", "beta",  "beta", "beta", "alpha",
		"alpha", "delta", "beta", "beta"
	};

	switch (n)
	{
			         case  1: {
		assert(appendToAll(z, -1, "rho") == -1 && a[0] == "alpha");
			} break; case  2: {
		assert(appendToAll(z, 0, "rho") == 0 && a[0] == "alpha");
			} break; case  3: {
		assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
							a[1] == "beta");
			} break; case  4: {
		assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
			a[1] == "betarho" && a[2] == "gammarho" &&
			a[3] == "gammarho" && a[4] == "betarho" &&
			a[5] == "deltarho");
			} break; case  5: {
		assert(lookup(z, -1, "alpha") == -1);
			} break; case  6: {
		assert(lookup(z, 0, "alpha") == -1);
			} break; case  7: {
		assert(lookup(a, 1, "alpha") == 0);
			} break; case  8: {
		assert(lookup(a, 6, "delta") == 5);
			} break; case  9: {
		assert(lookup(a, 6, "beta") == 1);
			} break; case 10: {
		assert(lookup(a, 6, "zeta") == -1);
			} break; case 11: {
		assert(positionOfMax(z, -1) == -1);
			} break; case 12: {
		assert(positionOfMax(z, 0) == -1);
			} break; case 13: {
		assert(positionOfMax(a, 1) == 0);
			} break; case 14: {
		assert(positionOfMax(a, 3) == 2);
			} break; case 15: {
		assert(positionOfMax(a, 6) == 2);
			} break; case 16: {
		assert(positionOfMax(a+3, 3) == 0);
			} break; case 17: {
		a[0] = "";
		a[1] = " ";
		a[2] = "";
		assert(positionOfMax(a, 3) == 1);
			} break; case 18: {
		assert(rotateLeft(z, -1, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 19: {
		assert(rotateLeft(a, 6, -1) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 20: {
		assert(rotateLeft(a, 6, 6) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 21: {
		assert(rotateLeft(z, 0, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 22: {
		assert(rotateLeft(a, 1, 0) == 0 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 23: {
		assert(rotateLeft(a, 6, 0) == 0 &&
			a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
			} break; case 24: {
		assert(rotateLeft(a, 6, 5) == 5 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 25: {
		assert(rotateLeft(a, 6, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
			} break; case 26: {
		assert(rotateLeft(a, 5, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
			} break; case 27: {
		assert(countRuns(z, -1) == -1);
			} break; case 28: {
		assert(countRuns(z, 0) == 0);
			} break; case 29: {
		assert(countRuns(a, 1) == 1);
			} break; case 30: {
		assert(countRuns(a, 3) == 3);
			} break; case 31: {
		assert(countRuns(a, 4) == 3);
			} break; case 32: {
		assert(countRuns(a+2, 4) == 3);
			} break; case 33: {
		assert(countRuns(d, 9) == 5);
			} break; case 34: {
		assert(flip(z, -1) == -1 && a[0] == "alpha");
			} break; case 35: {
		assert(flip(z, 0) == 0 && a[0] == "alpha");
			} break; case 36: {
		assert(flip(a, 1) == 1 && a[0] == "alpha" &&
					a[1] == "beta");
			} break; case 37: {
		assert(flip(a, 2) == 2 && a[0] == "beta" &&
					a[1] == "alpha" && a[2] == "gamma");
			} break; case 38: {
		assert(flip(a, 5) == 5 && a[0] == "beta" &&
			a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
			a[4] == "alpha" && a[5] == "delta");
			} break; case 39: {
		a[2] = "zeta";
		assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
			a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
			a[5] == "alpha");
			} break; case 40: {
		assert(differ(z, -1, b, 6) == -1);
			} break; case 41: {
		assert(differ(a, 6, z, -1) == -1);
			} break; case 42: {
		assert(differ(z, 0, b, 0) == 0);
			} break; case 43: {
		assert(differ(a, 3, b, 3) == 3);
			} break; case 44: {
		assert(differ(a, 3, b, 2) == 2);
			} break; case 45: {
		assert(differ(a, 2, b, 3) == 2);
			} break; case 46: {
		assert(differ(a, 6, b, 6) == 3);
			} break; case 47: {
		assert(subsequence(z, -1, b, 6) == -1);
			} break; case 48: {
		assert(subsequence(a, 6, z, -1) == -1);
			} break; case 49: {
		assert(subsequence(z, 0, b, 6) == -1);
			} break; case 50: {
		assert(subsequence(a, 6, z, 0) == 0);
			} break; case 51: {
		assert(subsequence(a, 6, b, 1) == 0);
			} break; case 52: {
		assert(subsequence(a, 6, b+4, 2) == 4);
			} break; case 53: {
		assert(subsequence(a, 6, b+3, 1) == 5);
			} break; case 54: {
		assert(subsequence(a, 6, b+3, 2) == -1);
			} break; case 55: {
		assert(subsequence(a, 6, b+2, 2) == -1);
			} break; case 56: {
		assert(subsequence(a, 6, a, 6) == 0);
			} break; case 57: {
		assert(lookupAny(a, 6, z, -1) == -1);
			} break; case 58: {
		assert(lookupAny(z, -1, b, 6) == -1);
			} break; case 59: {
		assert(lookupAny(z, 0, b, 1) == -1);
			} break; case 60: {
		assert(lookupAny(a, 6, z, 0) == -1);
			} break; case 61: {
		assert(lookupAny(a, 1, b, 1) == 0);
			} break; case 62: {
		assert(lookupAny(a, 6, b+3, 3) == 1);
			} break; case 63: {
		assert(lookupAny(a, 4, b+3, 3) == 1);
			} break; case 64: {
		assert(lookupAny(a, 2, b+2, 2) == -1);
			} break; case 65: {
		assert(separate(z, -1, "beta") == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 66: {
		assert(separate(z, 0, "beta") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 67: {
		assert(separate(a, 1, "aaa") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 68: {
		assert(separate(a, 1, "alpha") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 69: {
		assert(separate(a, 1, "zeta") == 1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 70: {
		assert(separate(a, 2, "aaa") == 0 &&
			separatecheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 71: {
		assert(separate(a, 2, "alpha") == 0 &&
			separatecheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 72: {
		assert(separate(a, 2, "beta") == 1 &&
			separatecheck(a, 2, 1, "beta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 73: {
		assert(separate(a, 2, "zeta") == 2 &&
			separatecheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 74: {
		assert(separate(a, 6, "aaa") == 0 && separatecheck(a, 6, 0, "aaa"));
			} break; case 75: {
		assert(separate(a, 6, "alpha") == 0 &&
			separatecheck(a, 6, 0, "alpha"));
			} break; case 76: {
		assert(separate(a, 6, "beta") == 1 &&
			separatecheck(a, 6, 1, "beta"));
			} break; case 77: {
		assert(separate(a, 6, "delta") == 3 &&
			separatecheck(a, 6, 3, "delta"));
			} break; case 78: {
		assert(separate(a, 6, "gamma") == 4 &&
			separatecheck(a, 6, 4, "gamma"));
			} break; case 79: {
		assert(separate(a, 6, "zeta") == 6 &&
			separatecheck(a, 6, 6, "zeta"));
			} break; case 80: {
		a[2] = "mu";
		c[5] = "mu";
		assert(separate(a, 6, "mu") == 5 && separatecheck(a, 6, 5, "mu"));
			} break; case 81: {
		assert(separate(a, 6, "chi") == 3 && separatecheck(a, 6, 3, "chi"));
			} break; case 82: {
                // This case tested whether rotateLeft used an extra array
                        } break; case 83: {
                // This case tested whether flip used an extra array
                        } break; case 84: {
                // This case tested whether separate used an extra array
			} break;
	}

	new (&a[-1]) string;
	new (&a[N]) string;
}

int main()
{
    cout << "Enter a test number (1 to 81): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 81)
    {
	cout << "Bad test number" << endl;
	return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}