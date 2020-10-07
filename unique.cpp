/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Ankit Patel
 * Date        : 9/23/20
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

/*
 * returns true if all characters in sting s are lowercase
 * letters in the English alphabet; false otherwise.
 */
bool is_all_lowercase(const string &s) {

	for(char c: s){
		//if the [ASCII] values of character isn't within this range,
		// then that character isn't in the lowercase English alphabet.
		if(!(c > 96 && c < 123)){
			return false;
		}
	}
	return true;
}

/*
 * TODO: returns true if all letters in string are unique, that is
 * no duplicates are found; false otherwise.
 * You may use only a single int for storage and work with bitwise
 * and bitshifting operators.
 * No credit will be given for other solutions.
 */
bool all_unique_letters(const string &s) {

	unsigned int vector = 0;

	for(unsigned int i = 0; i < s.length(); i++){

		// the setter is: 1 << (s[i] - 'a').
		// If the bitwise and of the vector and setter isn't 0,
		// That means the current character is a duplicate.
		if((vector & (1 << (s[i] - 'a'))) != 0){
			return false;
		}

		// If the current character isn't a duplicate,
		// update the vector to reflect that.
		vector = vector | (1 << (s[i] - 'a'));
	}
	return true;
}

// reads and parses command line arguments.
// Calls other functions to produce correct output.
int main(int argc, char * const argv[]) {

	//Case 1 & 2: Incorrect number of arguments
	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;	//return 1 whenever the program doesn't complete successfully
	}

	string input(argv[1]); //converts input into string

	//Case 3 & 4: Bad input (non lowercase characters)
	if(!is_all_lowercase(input)){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	//Case 5: Unique
	if(all_unique_letters(input)){
		cout << "All letters are unique." << endl;
	}
	else { //Case 6: Duplicates
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}
