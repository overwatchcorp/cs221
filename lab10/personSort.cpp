// Aidan Anders	and Jasper Fung
#include "./personSort.h"

// globals
const unsigned MAX_ELEMS = 50;

// define Person class constructor
Person::Person() {
  myFirstName = "";
  myLastName = "";
  myAge = 0;
}
Person::Person(std::string firstName, std::string lastName, int age) {
  myFirstName = firstName;
  myLastName = lastName;
  myAge = age;
}
//getters
int Person::getAge() {
  return myAge;
}
std::string Person::getName() {
  return myFirstName + " " + myLastName;
}
std::string Person::getFirstName() {
  return myFirstName;
}
std::string Person::getLastName() {
  return myLastName;
}
// opeator overloading
bool Person::operator> (Person other) { return this->getAge() > other.getAge(); }

void sort(Person peopleArray[], int num) {
	Person smallest = peopleArray[0];
	int smallestIndex = 0;
	int startIndex = 0;
	// first for loop runs num times, once for each element
	for(int i=0; i < num; i++) {
		// this runes from startIndex to end of array,
		// incrementing up one as we move the smallest elelemts to startIndex
		for (int x = startIndex; x < num; x++) {
			Person thisPerson = peopleArray[x];
			if (smallest > thisPerson) {
				smallest = thisPerson;
				smallestIndex = x;
			}
		}
		// if smallestIndex is not equal to startIndex, swap them
		if (smallestIndex != startIndex) {
			Person temp = peopleArray[startIndex];
			peopleArray[startIndex] = peopleArray[smallestIndex];
			peopleArray[smallestIndex] = temp;
		}
		// increment startIndex by one (regardless of swap y/n)
		startIndex += 1;
		// set smallestIndex equal to startIndex
		smallestIndex = startIndex;
		// set smallest to the value at startIndex
		smallest = peopleArray[startIndex];
	}
}

void read_file(string filename, int num, Person peopleArray[]) {
	ifstream file;
	file.open(filename.c_str());

	if (!file) {
		cout << "File error" << endl;
		return;
	}

	int i = 0;
  std::string firstName;
  std::string lastName;
  int age;
	while(file >> firstName >> lastName >> age) {
		if (i > num) {
			break;
		}
		peopleArray[i] = Person(firstName, lastName, age);
		i++;
	}
	file.close();

}


void save_file(std::string filename, int num, Person peopleArray[]) {

	ofstream file;
	file.open(filename.c_str());

	for (int i = 0; i < num; i++) {
    file << peopleArray[i].getName() << " " << peopleArray[i].getAge() << std::endl;
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
  if (!cin) {
    std::cout << "Invalid input" << std::endl;
    return 1;
  }
	cout << "Please specify the number of numbers in the file " << endl;
	cin >> num;
  if (!cin) {
    std::cout << "Please enter integer" << std::endl;
    return 1;
  }
	cout << "Please enter an output file name " << endl;
	cin >> ofilename;
  if (!cin) {
    std::cout << "Invalid input" << std::endl;
    return 1;
  }

	Person peopleArray[MAX_ELEMS];

	read_file(ifilename, num, peopleArray);
	sort(peopleArray, num);
	save_file(ofilename, num, peopleArray);

	return 0;
}
