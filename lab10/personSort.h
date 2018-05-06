// Aidan Anders	and Jasper Fung
#ifndef INT_SORT_H_
#define INT_SORT_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sort(int intArray[], int num);
void read_file(string filename, int num, int intArray[]);
void save_file(std::string filename, int num, int intArray[]);
// Each Person should contain a string storing the person’s first name, a string storing the person’s last name, and an int storing the person’s age.
class Person {
  public:
    Person();
    Person(std::string firstName, std::string lastName, int age);
    int getAge();
    bool operator>(Person other);
    std::string getName();
    std::string getFirstName();
    std::string getLastName();
  private:
    std::string myFirstName;
    std::string myLastName;
    int myAge;
};

#endif
#ifndef INT_SORT_H_
#define INT_SORT_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sort(int intArray[], int num);
void read_file(string filename, int num, int intArray[]);
void save_file(std::string filename, int num, int intArray[]);
// Each Person should contain a string storing the person’s first name, a string storing the person’s last name, and an int storing the person’s age.
class Person {
  public:
    Person();
    Person(std::string firstName, std::string lastName, int age);
    int getAge();
  private:
    std::string myFirstName;
    std::string myLastName;
    int myAge;
};

#endif
