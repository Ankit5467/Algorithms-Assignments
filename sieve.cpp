/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Ankit Patel
 * Date        : 9/15/20
 * Description : Sieve of Eratosthenes algorithm- prime number finder
 * Pledge  	   : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
    void find_max_prime();
};

//constructor
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {

    // As per the algorithm, the array of booleans must initially contain all "true" values.
    for(int i = 0; i <= limit_; i++){
    		is_prime_[i] = true;
    	}

    //Fuction calls to find the prime numbers and largest prime.
    sieve();
    find_max_prime();

    //initializes the instance variable "num_primes_" to the value of the number of primes.
    num_primes_ = count_num_primes();
}

/*
 * Displays the primes in the format specified in the requirements document.
 *
 */
void PrimesSieve::display_primes() const {

	const int max_prime_width = num_digits(max_prime_),
	 primes_per_row = 80 / (max_prime_width + 1);

	cout << endl << "Number of primes found: " << num_primes_ << endl;
	cout << "Primes up to " << limit_ << ":";

	//for testing purposes
	//cout << "The max prime width: " << max_prime_width << endl;
	//cout << "Primes per row: " << primes_per_row << endl;

	//If all of the primes can be printed on one line, the algorithm for displaying them is different
	//then the algorithm required if all of the primes required more than one line.
	if(num_primes_ <= primes_per_row){
		cout << endl;
		for(int i = 0; i <= limit_; i++){
			if(is_prime_[i]){
				// ie: the last (aka largest) prime to be printed does NOT have a trailing whitespace
				if(i == max_prime_){
					cout << i;
				}
				else{
					cout << i << " ";
				}
			}
		}
	}
	else{
		int curr = 0; // Used to keep track of the number of primes printed in a row
		for(int i = 0; i <= limit_; i++){
			if(is_prime_[i]){
				// ie: remove the leading space if the prime being printed goes on a new line
				if(curr >= primes_per_row || curr == 0){ //need || curr == 0 for the 1st line's formatting.
					cout << endl;
					curr = 0;
					cout << setw(max_prime_width);
				}
				else{
					cout << setw(max_prime_width+1);
				}
				cout << i;
				curr++;
			}
		}
	}
}

/*
 * Counts the number from prime numbers between 2 and limits_
 */
int PrimesSieve::count_num_primes() const {
	int num_primes_ = 0;
	for(int i = 0; i <= limit_; i++){
		if(is_prime_[i]){
			num_primes_++;
		}
	}
    return num_primes_;
}

/*
 * The sieve algorithm for finding prime numbers.
 */
void PrimesSieve::sieve() {
    // 0 and 1 are not considered prime, so set them equal to false.
	is_prime_[0] = false;
	is_prime_[1] = false;

	for(int i = 2; i <= (int)sqrt(limit_) ; i++){
		if(is_prime_[i]){
			for(int j = (int)pow(i,2.0); j<=limit_; j+=i){
				is_prime_[j] = false;
			}
		}
	}
}

/*
 *  Traverses the is_prime_ array backwards to find the largest prime
 *  Since the largest prime in the array is towards the end of the sorted
 *  array, its more efficient to traverse the array backwards.
 */
void PrimesSieve::find_max_prime(){
	for(int i = limit_ ; i >= 1; i--){
		if(is_prime_[i])
		{
			max_prime_ = i;
			break; // break out of the loop once the largest prime has been found
		}
	}
}

/*
 * Determines how many digits are in an integer via the
 * use of repeated division by 10. This function is used
 * for finding the number of digits of the largest prime number,
 * something which is needed to format the output properly.
 */
int PrimesSieve::num_digits(int num) {
	int num_digits=0;
	while(num/10 != 0){
		num= num/10;
		num_digits++;
	}
	num_digits++;
    return num_digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // The code that uses the PrimesSieve class to produce the desired output.
    PrimesSieve *nums = new PrimesSieve(limit);
    nums-> display_primes();

    delete nums; //deletes the object to prevent memory leaks
    return 0;
}
