Fall 2016 CS 31
Programming Assignment 5
I Can't Get No Satisfaction

Time due: 9:00 PM Wednesday, November 16

There's a world of web pages out there, and people like to have a way to find the ones that are interesting to them. One way to do this involves specifying a set of rules that can be applied to the text of each page; those pages that satisfy the rules to the highest degrees should be the ones that are most interesting.

Let's call the text of a web page a document. For this problem, a rule consists of two words, w1 and w2, and a positive integer distance. A document satisfies that rule if in it somewhere, w2 appears at least 1 word and no more than distance words before or after w1. For example, if w1 is "mad", w2 is "scientist", and distance is 2, then a document containing "The mad scientist took over the world." would satisfy the rule (since "scientist" appears 1 word after "mad"), as would one containing "A mad computer scientist invented C++." (2 words after "mad") and one containing "The scientist went mad." (2 words before "mad"). But if a document contained "The mad UCLA computer scientist unleashed a virus." ("scientist" is 3 words after "mad") and nowhere else contained the word "mad" preceded or followed by the word "scientist" any closer, then it would not satisfy the rule. The document "nomad scientists" does not satisfy the rule, since it does not even contain the word "mad" or the word "scientist".

We say that a collection of rules is in normal form if

Every word is at least one letter long and contains no characters other than lower case letters.
Every distance is positive.
No two rules in the collection have both the same w1 words and the same w2 words, in either order. (For example, if one rule has "mad" as its w1 word and "scientist" as its w2 word, then no other rule has "mad" as its w1 word and "scientist" as its w2 word, and no other rule has "scientist" as its w1 word and "mad" as its w2 word.)
Given a set of rules in normal form and a document, the satisfaction score of that document is the number of rules in that set that it satisfies. (Notice that if a document satisfies a rule, the number of ways it does so is irrelevant. For example, if there is a rule whose w1 is "deranged", w2 is "robot", and distance is 4, then the contribution of this rule to the satisfaction score for a document containing "deranged robot deranged deranged robot robot" is 1, not 8.)

For this project, you will write two functions: one to put a collection of purported rules into normal form, and one to calculate the satisfaction score of a document. A collection of rules will be represented using an integer and three arrays. The integer is the number of rules in the collection; the three components of each rule are stored in the same position across the three arrays. If there are n rules, they occupy positions 0 through n-1 of the arrays. The three arrays are

an array of C strings, holding the w1 words
an array of C strings, holding the w2 words
an array of ints, holding the distances
We guarantee that we will never test your functions with a word in a rule that is longer than 20 characters, so you are allowed to assume (and do not have to check) that the zero-bytes that denote the ends of the C strings are in fact present in the arrays that we give you. Prior to any of your function definitions, you must define the following constant (outside of any function definitions):

const int MAX_WORD_LENGTH = 20;
and use it where appropriate.

Here are the two functions you must implement:

int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
char word2[][MAX_WORD_LENGTH+1],
int distance[],
int nRules)
The parameters to this function represent a collection of zero or more purported rules, located in positions 0 through nRules-1 of the arrays. (Treat a negative nRules parameter as if it were 0.) When this function returns, the arrays must represent a set of rules in normal form, and the return value of the function is the number of rules in that normalized set (which might even be zero). The function must transform every upper case letter in the rule words into its lower case equivalent. The function must remove from the collection every purported rule for which at least one of these conditions hold:

A word in the rule contains no characters, or contains a character that is not a letter.
The distance is not positive.
Also, if two rules have the same w1 and the same w2 values, in either order, remove the rule whose distance value is the lesser of the two distance values. For example, if one rule indicates that we want to find documents where "robot" appears within 1 word before or after "deranged", and another indicates we want to find those where "robot" appears within 2 words before or after "deranged", remove the rule specifying within 1 word (since the other rule subsumes it). If two rules have the same w1 and w2 values (in either order) and the same distance values, remove one of them.

Suppose, say, r is the value returned by this function. Then the remaining rules in the normalized set that results from calling this function must be located in positions 0 through r−1 of the arrays, although they need not be in the same order they were in when the function was called, and a rule's w1 and w2 words may have been exchanged. The contents of positions r though nRules-1 of the arrays may be whatever you like; they don't even have to be valid C strings.

As an example, if elements 0 through 6 of the three arrays were

mad           scientist    2
deranged      robot        4
NEFARIOUS     PLOT         1
half-witted   assistant    3
robot         deranged     2
plot          Nefarious    1
have          mad         13
and the function were called with a last parameter of 7, then the function must return 4, and elements 0 through 3 of the arrays must contain some permutation of the following rules (where in each rule, the w1 and w2 words might be exchanged):

mad           scientist    2
deranged      robot        4
nefarious     plot         1
have          mad         13
(and it doesn't matter what's in elements 4 though 6 of each array).

You must not assume any particular limit on nRules, the number of purported rules.

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
const char word2[][MAX_WORD_LENGTH+1],
const int distance[],
int nRules,
const char document[])
The first four parameters represent a set of rules that this function is allowed to assume is in normal form. (In other words, it need not check this, and is allowed to not work correctly or even do something undefined if the set is not in normal form.) The last argument is a C string containing the entire text of a document. You are allowed to assume that no document is longer than 200 characters. (We guarantee we will not test your function with documents that exceed this limit.) The function must return the satisfaction score of the document (i.e., the number of rules that the document satisfies). Treat a negative nRules parameter as if it were 0.

In the document, words are separated by one or more space characters (i.e., ' '), upper case letters are to be treated as if they were lower case, and all non-alphabetic characters other than spaces are to be ignored — they do not act as word separators. Thus, the document "I'm upset that on Nov. 15th, 2016, my 2 brand-new BMW M760Lis were stolen!!" must be treated the same as if it were "im upset that on nov th my brandnew bmw mlis were stolen".

Notice that the function is not allowed to modify the characters in the document. It can, of course, make a copy of all or part of the document into local variables of its own if it wants. Because you are allowed to assume that no document is longer than 200 characters, you can determine upper bounds for any local arrays you might declare.

The document might contain words that are longer than 20 characters, even though we guarantee that no word in a rule will be longer than 20 characters. You must not assume any particular limit on nRules, the number of rules.

Your program must not use any std::string objects. If you need to use a string, you must use a C string.

Your functions must not use any global variables whose values may be changed during execution (so global constants like MAX_WORD_LENGTH are allowed). Any local arrays that your function declares must have a number of elements known at compile time.

The source file you turn in will contain the two required functions and a main routine. You can have the main routine do whatever you want, because we will rename it to something harmless, never call it, and append our own main routine to your file. Our main routine will thoroughly test your functions. You'll probably want your main routine to do the same. If you wish, you may write functions in addition to those required here. We will not directly call any such additional functions.

As an example, here is a main routine that contains some tests of the calculateSatisfaction function:

#include <iostream>
#include <cassert>
using namespace std;
...
int main()
{
const int TEST1_NRULES = 4;
char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
"mad",       "deranged", "nefarious", "have"
};
char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
"scientist", "robot",    "plot",      "mad"
};
int test1dist[TEST1_NRULES] = {
2,           4,          1,           13
};
assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
"The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
"The mad UCLA scientist unleashed    a deranged robot.") == 2);
assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
"**** 2016 ****") == 0);
assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
"  That plot: NEFARIOUS!") == 1);
assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
"deranged deranged robot deranged robot robot") == 1);
assert(calculateSatisfaction(test1w1, test1w2, test1dist, TEST1_NRULES,
"That scientist said two mad scientists suffer from deranged-robot fever.") == 0);
cout << "All tests succeeded" << endl;
}
The program you turn in must build successfully under both g++ with Linux and either Visual C++ or clang++, and during execution, neither of the two required functions, nor any function that they call, may read anything from cin or write anything to cout. If you want to print things out for debugging purposes, write to cerr instead of cout. When we test your program, we will cause everything written to cerr to be discarded instead — we will never see that output, so you may leave those debugging output statements in your program if you wish.

When your functions are called with arguments that meet the specifications, your program must not do anything that depends on undefined program behavior. Your program could not, for example, assume anything about t's value, or even whether or not the program crashes:

…
char t[10];
strcpy(t, "scientists");  // too long: 11 chars including '\0'
…
What you will turn in for this assignment is a zip file containing these two files and nothing more:

A text file named satisfy.cpp that contains the source code for your C++ program. Your source code should have helpful comments that tell the purpose of your data structures and program segments, and explain any tricky code.

A file named report.doc or report.docx (in Microsoft Word format) or report.txt (an ordinary text file) that contains:
A brief description of notable obstacles you overcame.
A description of the design of your program. You should use pseudocode in this description where it clarifies the presentation.
A list of the test data that you could use to thoroughly test your program, along with the reason for each test. You must note which test cases your program does not handle correctly. (This could happen if you didn't have time to write a complete solution, or if you ran out of time while still debugging a supposedly complete solution.) Notice that most of this portion of your report can be written just after reading the requirements in this specification, before you even start designing your program.
By November 15, there will be links on the class webpage that will enable you to turn in your zip file electronically. Turn in the file by the due time above. Give yourself enough time to be sure you can turn something in, because we will not accept excuses like "My network connection at home was down, and I didn't have a way to copy my files and bring them to a SEASnet machine." There's a lot to be said for turning in a preliminary version of your program and report early (You can always overwrite it with a later submission). That way you have something submitted in case there's a problem later.

Notes

Microsoft made a controversial decision to issue by default an error in some cases when using certain functions from the standard C and C++ libraries (e.g., strcpy). These warnings call that function unsafe and recommend using a different function in its place; that function, though, is not a Standard C++ function, so will cause a compilation failure when you try to build your program under g++ or clang++. Therefore, for this class, we want to use functions like strcpy without getting that error from Visual C++; to eliminate the error messages, put the following line in your program before any of your #includes:

#define _CRT_SECURE_NO_WARNINGS
It is OK and harmless to leave that line in when you build your program using g++ or clang++ and when you turn it in.

If your program dies under Visual C++ with a dialog box appearing saying "Debug Assertion Failed! ... File: ...\src\isctype.c ... expression: (unsigned)(c+1)<=256", then you called one of the functions defined by <cctype>, such as isalpha or tolower, with a character whose encoding is outside the range of 0 through 127. Since all the normal characters you would use (space, letters, punctuation, '\0', etc.) fall in that range, you're probably passing an uninitialized character to the function. Perhaps you're examining a character past the '\0' marking the end of a C string, or perhaps you built what you thought was a C string but forgot to end it with a '\0'.

Although the program you turn in must use C strings and is forbidden from using C++ strings, you can experiment with ideas for doing this project without that restriction. For example, you could create an experimental project (that you will not turn in) and pretend the required functions are

int fixRules(string word1[],
string word2[],
int distance[],
int nRules)

int figureSatisfaction(const string word1[],
const string word2[],
const int distance[],
int nRules,
const string document)
You can work out a lot of what you need to do for this project using C++ strings without the distraction of having to wrestle with C strings. Use what you learn from the experimental project when writing the real project that uses only C strings. Warning: It may not be wise to try to completely finish the experimental C++ string version before even starting the real C string version; it might take you more time than you thought to figure out how to work with C strings, so you might not have anything working in the C string version that you must turn in. Instead, when you have just a few things working in a C++ string version, try implementing them and getting them to work in the C string version, so you'll know how much time it takes you to translate from using C++ strings to C strings. Get more things working in the C++ string version, then in the C string version. Once you're comfortable with C strings, you might abandon the experimental version and continue on with just the real C string version. (Or not; maybe you prefer to continue working out each new bit with C++ strings first before implementing it with C strings.)

Project 5 Test Data

There were 61 test cases, each worth 1.23 points. Each test case is represented by an assertion that must be true for you to pass that test. To run the test cases:

Remove the main routine from your satisfy.cpp file.
Append the following text to the end of your satisfy.cpp file, and build the resulting program.
For any test case you wish to try, run the program, providing as input the test number.
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cassert>

using namespace std;

int d[3] =                      {    2,    1,    3 };
char w1[3][MAX_WORD_LENGTH+1] = { "aa", "bb", "cc" };
char w2[3][MAX_WORD_LENGTH+1] = { "dd", "ee", "ff" };

int e[2] =                      {    4,    4 };
char x1[2][MAX_WORD_LENGTH+1] = { "aa", "cc" };
char x2[2][MAX_WORD_LENGTH+1] = { "bb", "dd" };

const int THREE_LETTERS = 26*26*26;
int dd[THREE_LETTERS];
char ww1[THREE_LETTERS][MAX_WORD_LENGTH+1];
char ww2[THREE_LETTERS][MAX_WORD_LENGTH+1];

bool eq(int c, int dist, const char wd1[], const char wd2[])
{
	return d[c] == dist  &&  strcmp(w1[c], wd1) == 0  &&
						strcmp(w2[c], wd2) == 0;
}

void testone(int n)
{
	switch (n)
	{
			         case  1: {
		assert(normalizeRules(w1, w2, d, 0) == 0);
			} break; case  2: {
		assert(normalizeRules(w1, w2, d, 1) == 1  &&
					eq(0, 2, "aa", "dd"));
			} break; case  3: {
		d[0] = 0;
		assert(normalizeRules(w1, w2, d, 1) == 0);
			} break; case  4: {
		d[0] = 0;
		assert(normalizeRules(w1, w2, d, 2) == 1  &&
					eq(0, 1, "bb", "ee"));
			} break; case  5: {
		d[1] = 0;
		assert(normalizeRules(w1, w2, d, 2) == 1  &&
					eq(0, 2, "aa", "dd"));
			} break; case  6: {
		d[1] = 0;
		d[2] = 0;
		assert(normalizeRules(w1, w2, d, 3) == 1  &&
					eq(0, 2, "aa", "dd"));
			} break; case  7: {
		d[0] = 0;
		d[1] = 0;
		assert(normalizeRules(w1, w2, d, 3) == 1  &&
					eq(0, 3, "cc", "ff"));
			} break; case  8: {
		d[0] = 0;
		d[1] = 0;
		d[2] = 0;
		assert(normalizeRules(w1, w2, d, 3) == 0);
			} break; case  9: {
		strcpy(w1[1], "");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 10: {
		strcpy(w2[1], "");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 11: {
		strcpy(w1[1], "bb@");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 12: {
		strcpy(w1[1], "bb ");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 13: {
		strcpy(w1[1], "bBBb");
		assert(normalizeRules(w1, w2, d, 2) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 1, "bbbb", "ee"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 1, "bbbb", "ee"))
		       )
		      );
			} break; case 14: {
		strcpy(w1[1], "bBBb");
		strcpy(w2[1], "EeEeE");
		assert(normalizeRules(w1, w2, d, 2) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 1, "bbbb", "eeeee"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 1, "bbbb", "eeeee"))
		       )
		      );
			} break; case 15: {
		strcpy(w2[1], "bb");
		assert(normalizeRules(w1, w2, d, 2) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 1, "bb", "bb"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 1, "bb", "bb"))
		       )
		      );
			} break; case 16: {
		strcpy(w2[0], "aa");
		strcpy(w1[1], "aa");
		strcpy(w2[1], "aa");
		assert(normalizeRules(w1, w2, d, 2) == 1  &&
					eq(0, 2, "aa", "aa")
		      );
			} break; case 17: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 18: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 2;
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 19: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 5;
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 5, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 5, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 20: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		assert(normalizeRules(w1, w2, d, 3) == 1  &&
					eq(0, 3, "aa", "dd")
		      );
			} break; case 21: {
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		d[1] = 0;
		assert(normalizeRules(w1, w2, d, 3) == 1  &&
					eq(0, 3, "aa", "dd")
		      );
			} break; case 22: {
		strcpy(w1[1], "abcdefghijklmnopqrst");
		strcpy(w2[1], "abcdefghijklmnopqrsu");
		d[0] = 0;
		assert(normalizeRules(w1, w2, d, 2) == 1  &&
				eq(0, 1, "abcdefghijklmnopqrst",
						"abcdefghijklmnopqrsu")
		      );
			} break; case 23: {
		strcpy(w2[0], "DD");
		strcpy(w1[1], "AA");
		strcpy(w2[1], "dD");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 24: {
		strcpy(w1[1], "dd");
		strcpy(w2[1], "aa");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 25: {
		strcpy(w1[1], "dd");
		strcpy(w2[1], "aa");
		d[1] = 2;
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       (((eq(0, 2, "aa", "dd")  ||  eq(0, 2, "dd", "aa")
			 )  &&  eq(1, 3, "cc", "ff")
			)  ||
			((eq(1, 2, "aa", "dd")  ||  eq(1, 2, "dd", "aa")
			 )  &&  eq(0, 3, "cc", "ff")
			)
		       )
		      );
			} break; case 26: {
		strcpy(w1[1], "Dd");
		strcpy(w2[1], "aA");
		assert(normalizeRules(w1, w2, d, 3) == 2  &&
		       ((eq(0, 2, "aa", "dd")  &&  eq(1, 3, "cc", "ff"))  ||
			(eq(1, 2, "aa", "dd")  &&  eq(0, 3, "cc", "ff"))
		       )
		      );
			} break; case 27: {
		int dx[7] = { 2, 4, 1, 3, 2, 1, 13 };
		char w1x[7][MAX_WORD_LENGTH+1] = { "mad", "deranged",
			"NEFARIOUS", "half-witted", "robot", "plot", "have" };
		char w2x[7][MAX_WORD_LENGTH+1] = { "scientist", "robot",
			"PLOT", "assistant", "deranged", "Nefarious", "mad" };
		assert(normalizeRules(w1x, w2x, dx, 7) == 4);
			} break; case 28: {
		assert(calculateSatisfaction(x1, x2, e, 2, "") == 0);
			} break; case 29: {
		assert(calculateSatisfaction(x1, x2, e, 2, " ") == 0);
			} break; case 30: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa bb") == 1);
			} break; case 31: {
		e[0] = 1;
		assert(calculateSatisfaction(x1, x2, e, 2, "aa bb") == 1);
			} break; case 32: {
		e[0] = 1;
		assert(calculateSatisfaction(x1, x2, e, 2, "aa     bb") == 1);
			} break; case 33: {
		assert(calculateSatisfaction(x1, x2, e, 2, " aa bb") == 1);
			} break; case 34: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa bb ") == 1);
			} break; case 35: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa bb cc dd xx") == 2);
			} break; case 36: {
		assert(calculateSatisfaction(x1, x2, e, 1, "aa bb cc dd xx") == 1);
			} break; case 37: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa xx cc bb xx dd xx") == 2);
			} break; case 38: {
		assert(calculateSatisfaction(x1, x2, e, 2, "xx dd bb cc aa xx") == 2);
			} break; case 39: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa xx xx xx bb cc dd xx") == 2);
			} break; case 40: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa xx xx xx xx bb cc dd xx") == 1);
			} break; case 41: {
		e[0] = 1;
		e[1] = 1;
		assert(calculateSatisfaction(x1, x2, e, 2, "aa xx bb cc dd xx") == 1);
			} break; case 42: {
		e[0] = 2;
		e[1] = 2;
		assert(calculateSatisfaction(x1, x2, e, 2, "aa cc bb dd xx") == 2);
			} break; case 43: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa bb aa bb cc dd xx") == 2);
			} break; case 44: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa aa bb bb cc dd xx") == 2);
			} break; case 45: {
		strcpy(x2[0], "aa");
		assert(calculateSatisfaction(x1, x2, e, 2, "aa xx xx aa") == 1);
			} break; case 46: {
		strcpy(x2[0], "aa");
		assert(calculateSatisfaction(x1, x2, e, 2, "xx aa xx") == 0);
			} break; case 47: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aA bb cc dd xx") == 2);
			} break; case 48: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa @@ ## $$ %% ^^ bb cc dd xx") == 2);
			} break; case 49: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa b@@b cc dd xx") == 2);
			} break; case 50: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa b123456789012345678901234567890b cc dd xx") == 2);
			} break; case 51: {
		e[0] = 1;
		assert(calculateSatisfaction(x1, x2, e, 2, "aa abcdefghijklmnopqrstuvwxyz bb cc dd xx") == 1);
			} break; case 52: {
		e[0] = 2;
		assert(calculateSatisfaction(x1, x2, e, 2, "aa abcdefghijklmnopqrstuvwxyz bb cc dd xx") == 2);
			} break; case 53: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(calculateSatisfaction(x1, x2, e, 2, "abcdefghijklmnopqrst bb cc dd xx") == 2);
			} break; case 54: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(calculateSatisfaction(x1, x2, e, 2, "abcdefghijklmnopqrstu bb cc dd xx") == 1);
			} break; case 55: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aaa bb cc dd xx") == 1);
			} break; case 56: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa@bb cc dd xx") == 1);
			} break; case 57: {
		assert(calculateSatisfaction(x1, x2, e, 2, "aa bb@cc dd xx") == 0);
			} break; case 58: {
		e[0] = 1000;
		assert(calculateSatisfaction(x1, x2, e, 2, "xx aa xx") == 0);
			} break; case 59: {
		strcpy(x1[0], "a");
		strcpy(x2[0], "b");
		e[0] = 100;
		static char doc[200+1];
		strcpy(doc, "a ");
		for (int k = 0; k < 98; k++)
			strcpy(doc+2+2*k, "x ");
		strcpy(doc+198, "b ");
		assert(calculateSatisfaction(x1, x2, e, 2, doc) == 1);
			} break; case 60: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = k % 2;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(normalizeRules(ww1, ww2, dd, THREE_LETTERS) == THREE_LETTERS / 2);
		for (int k = 0; k < THREE_LETTERS / 2; k++)
			assert(dd[k] == 1 && strcmp(ww1[k], "a") == 0 &&
				islower(ww2[k][2]) &&
				(ww2[k][2] - 'a') % 2 == 1);
			} break; case 61: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = 1;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(calculateSatisfaction(ww1, ww2, dd, THREE_LETTERS,
				"a aaa a iaa a pzz a zzz") == 4);
		assert(calculateSatisfaction(ww1, ww2, dd, THREE_LETTERS,
				"a aaaa a iaaa a pzzz a zzzz") == 0);
			} break;
	}
}

int main()
{
    cout << "Enter a test number (1 to 61): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 61)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}