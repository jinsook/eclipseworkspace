/*!
 * \brief Solving Prime Ring problem(from SK C&C) for the given inputs in a file.
 * \author Choi, Jinsook
 */

#include <iostream>
#include <fstream>

using namespace std;

void permute(int *values, int size, int k ){
	static int level = -1;

	level = level +1;
	values[k] = level;
	//cout<<" level="<<level;
	if (level==size){
		for ( int i=0; i<size; i++){ cout<<values[i]<<" ";}
		cout<<endl;
	}
	else {
		for (int i=0; i<size; i++){
		//	cout<<" i="<<i;
			if (values[i] == 0) {
	//			cout<<" permute(.,., "<<i<<")";
	//			cout<<" empty ";
				permute(values, size, i);
			}
		}
	//	cout<<endl;
	}
	//cout<<"elevel="<<level<<endl;
	level = level -1; values[k]=0;
	//cout<<"value["<<k<<"]=0"<<endl;

}


int main(int argc, char** argv)
{
	if ( argc < 2 ){
			return -1;
	}

	ifstream ifs(argv[1], ifstream::in);
	if (!ifs.is_open()) {
		cerr<<"file "<<argv[1]<<" doesn't exist!"<<endl;
	}
	int input;
	int num = 1;
	int values[256];
	while (ifs.good()) {
		ifs>>input;

		memset(values, 0, 256*sizeof(int));
		cout<<"Case "<<num++<<":"<<endl;
		permute(values, input, 0);
	}

	return 0;
}
