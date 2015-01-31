//============================================================================
// Name        : helloworld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

class AWOW {
public:
	virtual ~AWOW() = 0;
};

AWOW::~AWOW(){}

class FontHandle {

};

class Font {
public:
	explicit Font(FontHandle h)
	:f(h)
	{}
	~Font(){}

	FontHandle get() const { return f; }
private:
	FontHandle f;
};

int main() {
	FontHandle fh;
	Font f(fh);
	FontHandle sfh = f.get();

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << "jjjjj"<< endl;
	int in;
	cin>>in;
	return 0;
}
