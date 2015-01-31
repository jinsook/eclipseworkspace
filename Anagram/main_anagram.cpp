/*!
 * Solving Anagram for the given inputs in a file.
 * \author Choi, Jinsook
 */

#include <iostream>
#include <fstream>
#include <cstring>



using namespace std;

/*!the inputs seem short strings. So, why don't  we
 * use the insertion sort to sort the given string in ascending order.
 */
void sortSimple(char *input, int strlen){
	assert(input);
	char tmp;
	for (int i=1; i<strlen; i++){
		for (int j=i-1; j>=0; j--) {
			if (input[j]>input[j+1]) {
				tmp = input[j+1];
				input[j+1] = input[j];
				input[j] = tmp;
			}
			else break;
		}
	}
}

/*!
 * called from anagram
 */
void rotateLeft(char* input, const int start, const int strlen)
{
	char tmp = input[start];
	for(int i = start; i<strlen-1; i++){
		input[i] = input[i+1];
	}
	input[strlen-1] = tmp;
	cout<<"rotate:"<<input<<endl;
}

/*!
 * Generates all possible anagram from input string.
 * Since the algorithm is recursive, initial call should be
 * anagram(input, 0, strlen(input)) for all possible words.
 * Uses An Ordered Lexicographic Permutation Algorithm based
 * on one published in Practical Algorithms in C++
 */
void anagram(char *input, int start, int strlen) {

	cout<<input<<endl;
	char tmp;
	if(start<strlen){
		int i, j;
		for (i=strlen-2; i >= start; i--){
			for(j=i+1; j<strlen; j++){
				//remove the permutation for repeated character
				if ( input[i] == input[j]) continue;

				//swap
				tmp = input[i];
				input[i] = input[j];
				input[j] = tmp;

				anagram(input, i+1, strlen);
			}
			rotateLeft(input, i, strlen);
		}
	}
}

void usage(){
	cerr<<"usage: anagram filename"<<endl;
	exit(-1);
}

int main(int argc, char** argv)
{
	if ( argc < 2 ){
		usage();
	}

	ifstream ifs(argv[1], ifstream::in);
	if (!ifs.is_open()) {
		cerr<<"file "<<argv[1]<<" doesn't exist!"<<endl;
	}

	int numInput, slen;
	ifs>>numInput;

	//Allow the maximum length 1023, for now.
	int MaxInput = 1024;
	char input[MaxInput];
	for (int i =0; i < numInput; i++ ){
		memset(input, 0 , MaxInput);
		if(	!ifs.good())  {
			cerr<<"cannot get any more input"<<endl;
			cerr<<"please check if the input file is in the right format"<<endl;
			break;
		}
		ifs>>input;
		//cout<<"input:"<<input<<endl;
		if (input[MaxInput-1] != 0 ){
			cerr<<i<<"th input is too long: we can process up to size "
			<<MaxInput-1<<endl;
			continue;
		}
		slen = strlen(input);
		sortSimple(input, slen);
		anagram(input, 0, slen);
	}

	return 0;
}
