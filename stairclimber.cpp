/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Ankit Patel
 * Date        : 10/2/20
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

/*
 * Returns a vector of vectors of ints representing
 * the different combinations of ways to climb num_stairs
 * stairs, moving up either 1, 2, or 3 stairs at a time.
 * (Recursive implementation)
 */
vector<vector<int> > get_ways(int num_stairs) {
	//Base case
	if (num_stairs <= 0) {
		return { {}};
	}

	vector<vector<int>> ways = { };
	for (int i = 1; i < 4; i++) {
		if (num_stairs >= i) {

			// recursive call
			vector<vector<int>> result = get_ways(num_stairs - i);

			for (int j = 0; j < (int) result.size(); j++) {
				result.at(j).insert(result.at(j).begin(), i);
			}

			// concatenates known result w/ newly found result
			ways.insert(ways.end(), result.begin(), result.end());
		}
	}
	return ways;
}

/*
 * Displays the ways to climb stairs by iterating over
 * the vector of vectors and printing each combination.
 * (Prints in the format as described in the requirements
 *  document)
 */
void display_ways(const vector<vector<int> > &ways) {
	// finds # of spaces needed to right align output.
	int size_len = (int) ways.size();
	int num_spaces = 0;

	// finds number of digits contained in the length of ways
	while (size_len != 0) {
		size_len /= 10;
		num_spaces++;
	}

	//Formatting for first iteration of loop
	int count = 1;
	int nums_on_row = 0;
	cout << setw(num_spaces) << count << ". [";

	//Prints all of the data in ways
	for (vector<int> i : ways) {
		for (int j : i) {
			cout << j;
			nums_on_row++;

			//If all of the elements in a vector in ways have not
			//been printed, continue the formatting.
			if ((int) i.size() != nums_on_row) {
				cout << ", ";
			}
		}
		count++;
		cout << "]" << endl;

		//If there are more vectors in ways left to be
		//printed, set up the formatting to print the next vector.
		if ((int) ways.size() != count - 1) {
			cout << setw(num_spaces) << count << ". [";
		}
		nums_on_row = 0;
	}
}

int main(int argc, char *const argv[]) {

	//Case 1: No input arguments or Case 2: Too many input arguments
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1; // return 1 whenever the program doesn't complete successfully
	}

	int num_stairs;
	istringstream str(argv[1]);
	str >> num_stairs;

	//Case 5: Valid Input
		//If input is unable to be converted into a string,
		//it must be an integer
	if (!(str >> num_stairs)) {
		if (num_stairs > 0) {
			vector<vector<int>> all_ways = get_ways(num_stairs);

			if (all_ways.size() == 1) {
				cout << all_ways.size() << " way to climb " << num_stairs
						<< " stair." << endl;
			} else {
				cout << all_ways.size() << " ways to climb " << num_stairs
						<< " stairs." << endl;
			}
			display_ways(all_ways);
		}
		//Case 4: Bad input
		else {
			cerr << "Error: Number of stairs must be a positive integer."
					<< endl;
			return 1;
		}
	}
	//Case 3: Bad input
	else {
		//If input is successfully converted into a string,
		//It's an invalid input
		cerr << "Error: Number of Stairs must be a positive integer" << endl;
		return 1;
	}
	return 0;
}
