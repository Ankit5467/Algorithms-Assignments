/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Ankit Patel
 * Version     : 1.0
 * Date        : 10/26/20
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	// TODO
	long count = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i; j < length; j++) {
			if (array[i] > array[j]) {
				count++;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time,
 * using mergesort.
 */
long count_inversions_fast(int array[], int length) {
	// TODO
	int *scratch = new int[length];
	long count = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;

	return count;
}

/**
 * Uses the mergesort algorithm to keep track of the number of inversions.
 * Recursive calls are for finding number of inversions in the subarrays.
 */
static long mergesort(int array[], int scratch[], int low, int high) {
	// TODO
	long count = 0;

	if (low < high) {
		int mid = low + (high - low) / 2;

		//Adds the inversion counts from the left & right partitions
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);

		int L = low;
		int H = mid + 1;

		for (int k = low; k <= high; k++) {
			if (L <= mid && (H > high || array[L] <= array[H])) {
				scratch[k] = array[L];
				L++;
			} else {
				scratch[k] = array[H];
				H++;

				//Adds the inversion count of the current execution of algorithm
				count += mid - L + 1;
			}
		}

		for (int k = low; k <= high; k++) {
			array[k] = scratch[k];
		}
	}

	return count;
}

int main(int argc, char *argv[]) {

	// TODO: parse command-line argument
	bool slow = false;

	if (argc > 2) {
		//invalid usage
		cerr << "Usage: " << argv[0] << " [slow]" << endl;
		return 1;
	} else if (argc == 2) {
		istringstream ss;
		ss.str(argv[1]);
		if (!ss.str().compare("slow")) {
			slow = true;
		} else {
			//invalid command line argument
			cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
			return 1;
		}
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;

	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}

	// TODO: produce output
	if(!values.size()){
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}

	long num_inversions;
	if (slow) {
//		cout << "slow" << endl;
		num_inversions = count_inversions_slow(&values[0], values.size());
	} else {
		num_inversions = count_inversions_fast(&values[0], values.size());
	}
	cout << "Number of inversions: " << num_inversions << endl;

	return 0;
}
