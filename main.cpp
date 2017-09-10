#include <iostream>
#include <fstream>

using namespace std;

//main that takes in a file argument
int main(int argc, char* argv []) {
	
	if (argc < 2) {
		cout << "Missing file name...";
		return 1;
	}

	ifstream fin(argv[1]);

	if (!fin) {
		cout << "file not found...";
		return 1;
	}
	
	//parser(fin); //parser function (INCOMPLETE)
	fin.close();




}