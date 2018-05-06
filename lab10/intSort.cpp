// Aidan Anders	and Jasper Fung
#include "./intSort.h"

// globals
const unsigned MAX_ELEMS = 50;

void sort(int intArray[], int num) {
	int smallest = intArray[0];
	int smallestIndex = 0;
	int startIndex = 0;
	// first for loop runs num times, once for each element
	for(int i=0; i < num; i++) {
		// this runes from startIndex to end of array,
		// incrementing up one as we move the smallest elelemts to startIndex
		for (int x = startIndex; x < num; x++) {
			int thisInt = intArray[x];
			if (thisInt < smallest) {
				smallest = thisInt;
				smallestIndex = x;
			}
		}
		// if smallestIndex is not equal to startIndex, swap them
		int temp = 0;
		if (smallestIndex != startIndex) {
			temp = intArray[startIndex];
			intArray[startIndex] = intArray[smallestIndex];
			intArray[smallestIndex] = temp;
		}
		// increment startIndex by one (regardless of swap y/n)
		startIndex += 1;
		// set smallestIndex equal to startIndex
		smallestIndex = startIndex;
		// set smallest to the value at startIndex
		smallest = intArray[startIndex];
	}
}

void read_file(string filename, int num, int intArray[]) {
	ifstream file;
	file.open(filename.c_str());

	if (!file) {
		cout << "File error" << endl;
		return;
	}

	int i = 0;
	int readNum = 0;
	while(file >> readNum) {
		if (i > num) {
			break;
		}
		intArray[i] = readNum;
		i++;
	}
	file.close();

}


void save_file(std::string filename, int num, int intArray[]) {

	ofstream file;
	file.open(filename.c_str());

	for (int i = 0; i < num; i++) {
		file << " " << intArray[i];
	}
	file << endl;

	file.close();
}


int main() {
	std::string ifilename;
	std::string ofilename;
	int num;

	cout << "Please specify an input file " << endl;
	cin >> ifilename;
	cout << "Please specify the number of numbers in the file " << endl;
	cin >> num;
	cout << "Please enter an output file name " << endl;
	cin >> ofilename;

	int intArray[MAX_ELEMS];

	read_file(ifilename, num, intArray);
	sort(intArray, num);
	save_file(ofilename, num, intArray);

	return 0;
}
