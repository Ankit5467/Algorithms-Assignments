/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Ankit Patel
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System
 * Date          : 10/23/20
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;


/*
 * Performs a single lomuto partition on an array.
 * After the lomuto partition, all of the elements less than the pivot
 * will be to its left and all of the elements greater than or
 * equal to the pivot will be to its right. (These two partitions
 * may be relatively unsorted). Assumes the initial pivot value is the
 * first element of the array. Returns the new index of the pivot value.
 */
size_t lomuto_partition(int array[], size_t left, size_t right) {

	// TODO
	// DO NOT change the function header in any way.
	int p = array[left]; // p is the pivot value
	int s = left;

	for (unsigned int i = left + 1; i <= right; i++) {
		if (array[i] < p) {
			s++; // s+=1;
			swap(array[s], array[i]);
		}
	}
	swap(array[left], array[s]); // places pivot in appropriate location.

	return s; //s is the new pivot index after 1 iteration of lomuto partition
}

/*
 * quick_select performs repeated lomutu partitions to obtain and return
 * the value of the k-th smallest element in array[].
 * Implements with algorithm without array slicing.
 */
int quick_select(int array[], size_t left, size_t right, size_t k) {
	// TODO
	// DO NOT change the function header in any way.
	unsigned int s = lomuto_partition(array, left, right);

	if (s == k - 1) {
		return array[s];
	} else if (s > k - 1) {
		return quick_select(array, left, s - 1, k);
	} else {
		return quick_select(array, s + 1, right, k);
	}
}

int quick_select(int array[], const size_t length, size_t k) {
	return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <k>" << endl;
		return 1;
	}

	int k;
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> k) || k <= 0) {
		cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
		return 1;
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	iss.clear();
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

	int num_values = values.size();
	if (num_values == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}

	// TODO - error checking k against the size of the input
	if (k > num_values) {
		cerr << "Error: Cannot find smallest element " << k << " with only "
				<< num_values;
		if (num_values == 1) {
			cerr << " value." << endl;
		} else {
			cerr << " values." << endl;
		}
		return 1;
	}

	// TODO - call the quick_select function and display the result
	int res = quick_select(&values[0], num_values, k);
	cout << "Smallest element " << k << ": " << res << endl;

	return 0;
}
