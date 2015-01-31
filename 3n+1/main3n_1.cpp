/*!
 * \brief Solving 3n+1 problem for the given inputs in a file.
 * \author Jinsook
 */

#include <iostream>
#include <fstream>

using namespace std;

typedef struct __nclpair{
	int num; ///< integer value
	int clength; ///< the cycle length of num
	struct __nclpair *next;

} NumClengthPair;

/*!
 * Definition of Solver3nPlus1
 */
class Solver3nPlus1
{
	NumClengthPair *simpleHash[1000];
//	int newEntry, reused;

private: //private methods

	/*!
	 * put a new cycle length clength for the number num.
	 */
	void putCLength(int num, int clength){
		int entry = num%1000;
		NumClengthPair *newPair = new NumClengthPair;
		newPair->num = num; newPair->clength = clength;
		newPair->next= simpleHash[entry];
		simpleHash[entry] = newPair;
		//newEntry++;
	}

	/*!
	 * find the cycle length of num. If there is no value stored, return -1;
	 */
	int findCLength(int num){
		NumClengthPair *curPtr;
		if (!(curPtr=simpleHash[num%1000])) return -1;
		while (curPtr){
			if (curPtr->num == num) {
				//reused++;
				return curPtr->clength;
			}
			curPtr = curPtr->next;
		}
		return -1;
	}

	/*!
	 * deallocate the memory that was created during putCLength
	 */
	void clearSimpleHash(){
		NumClengthPair *curPtr, *nxtPtr;
		for (int i=0; i < 1000; i++){
			curPtr=simpleHash[i];
			while(curPtr){
				nxtPtr = curPtr->next;
				delete curPtr;
				curPtr = nxtPtr;
			}
		}
	}

	/*!
	 * returns the cycle length of n. First finds the cycle length if already calculated.
	 * Otherwise, calculates and saves the cycle length for later use.
	 */
	int getCycleLength(int n){
		int length;
		if ( (length=findCLength(n))!= -1)
			return length;

		if (n==1) return 1;

		if (n%2) putCLength(n, length=1+getCycleLength(3*n+1));
		else 	 putCLength(n, length=1+getCycleLength(n/2));

		return length;
	}

public:
	Solver3nPlus1(){
		memset(simpleHash, 0, sizeof(NumClengthPair*)*1000);
//		newEntry =0;reused = 0;
	};
	~Solver3nPlus1(){
//		cout<<"newEntry= "<<newEntry<<" reused="<<reused<<endl;
		clearSimpleHash();
	};

	/*!
	 * calculates the maximum cycle length among all cycle lengths for numbers between i and j.
	 */
	void solveProblem(int i, int j) {

		int tmp = -1;
		if ( j<i ){	tmp = i; i = j; j = tmp;}//if the order is reversed, swap
		int maxCycleLength = -1;
		int tmpCycleLength;
		for (int index=j; index>=i; index--){
			tmpCycleLength = getCycleLength(index);
			if (maxCycleLength < tmpCycleLength)
				maxCycleLength = tmpCycleLength;
			//cout<<"index="<<index<<" clength="<<tmpCycleLength<<endl;
		}

		if (tmp>0){tmp = i; i = j; j = tmp;}// if the order has been reversed, swap back
		cout<<i<<' '<<j<<' '<<maxCycleLength<<endl;
	}
};

void usage(){
	cerr<<"usage: 3nplus1 filename"<<endl;
	exit(-1);
}

int main(int argc, char** argv)
{
	if ( argc < 2 ){
		usage();
	}

	Solver3nPlus1 solver;
	ifstream ifs(argv[1], ifstream::in);
	if (!ifs.is_open()) {
		cerr<<"file "<<argv[1]<<" doesn't exist!"<<endl;
	}
	int i, j;
	while (ifs.good()) {
		ifs>>i>>j;
		if (i<=0 || i>= 10000000 || j<=0 || j>=1000000){
			cerr<<"Cannot process input "<<i<<" and "<<j;
			cerr<<" pair in the file. The input should be greater than 0 and less than 1000000"<<endl;
			continue;
		}
		solver.solveProblem(i,j);
	}

	return 0;
}


