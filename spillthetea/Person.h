#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
	string id;
	string name;
	int age;
public:
	Person();
	Person(string id, string name, int age); 
	Person(const Person& other); 

	void setName(string);
	void setAge(int);
	void setID(string);

	string getID();
	int getAge();
	string getName();


};
