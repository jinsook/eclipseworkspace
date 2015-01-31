/*!
 * \brief Solving Prime Ring problem(from SK C&C) for the given inputs in a file.
 * \author Choi, Jinsook
 */

#include <iostream>
#include <fstream>

using namespace std;

/*!
 * Finds prime rings for the given integer(0< i <= 16) value.
 */
class PrimeRing{

	enum PRIME{No, Yes, Unknown};

	/*!
	 * For calculated primes, we save the result and reuse later.
	 */
	PRIME mPrime[32];///< if i is mPrime, mPrime[i]= Yes.

public:

	PrimeRing(){
		for (int i =0; i<32;i++ ){
			mPrime[i] = Unknown;
		}
		mPrime[0] = No;
		mPrime[1] = No;
	}

	/*!
	 * finds and prints the prime ring for the given input
	 */
	void solveProblem(int input){
		int *values = new int[input];
		memset(values, 0, sizeof(int)*input);

		permute(values, input, 0);
		delete [] values;
	}

private:

	bool ismPrime(int i) {
		assert(i<=31);
		if (mPrime[i]==Unknown){
			for (int j=i-1 ; j > 1; j--)
				if((i%j)==0) return (mPrime[i]=No);
			return (mPrime[i]=Yes);
		}
		return (mPrime[i]==Yes);
	}

	bool isOdd(int i) const { return i%2!=0; }

	bool isEven(int i) const { return i%2 == 0; }

	/*!
	 * return true if i+j is prime return true;
	 * otherwise return false;
	 */
	bool ismPrimeNeighbor(int i, int j) {
		if (isOdd(i) && isOdd(j)) return false;
		if (isEven(i) && isEven(j)) return false;
		if (!ismPrime(i+j))return false;
		return true;
	}

	/*!
	 * Used Alexander Bogomolyn's unordered permutation algorithm.
	 * But if a permutation is not fitting for the prime ring
	 * stop to find a solution among that permutation.
	 */
	void permute(int *values, int size, int k ){
		static int level = 0;

		level = level +1;
		values[k] = level;

		if (k>=1){
			int il = (k-1)%size;
			int ir = (k+1)%size;
			//if this permutation is not fitting for the prime ring
			//stop go further.
			if ((values[il] != 0 && !ismPrimeNeighbor(level, values[il])) ||
				(values[ir] != 0 && !ismPrimeNeighbor(level, values[ir])) ){
				level = level -1; values[k]=0;
				return;
			}
		}

		if (level==size){
			for ( int i=0; i<size; i++){ cout<<values[i]<<" ";}
			cout<<endl;
		}
		else {
			for (int i=1; i<size; i++){
				if (values[i] == 0)
					permute(values, size, i);
			}
		}

		level = level -1; values[k]=0;
	}


};

void usage(){
	cerr<<"usage: primering filename"<<endl;
	exit(-1);
}

int main(int argc, char** argv)
{
	if ( argc < 2 ){
		usage();
	}

	PrimeRing primeRing;
	ifstream ifs(argv[1], ifstream::in);
	if (!ifs.is_open()) {
		cerr<<"file "<<argv[1]<<" doesn't exist!"<<endl;
	}
	int input;
	int num = 1;
	while (ifs.good()) {
		ifs>>input;

		//check input validity
		if (input<=0 || input >16) {
			cerr<<"Wrong input="<<input<<
			". input should be greater than 0 and less than 17"<<endl;
			continue;
		}

		cout<<"Case "<<num++<<":"<<endl;
		primeRing.solveProblem(input);
	}

	return 0;
}
