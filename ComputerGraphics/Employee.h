#pragma once
#include <string>

using namespace std;

class Employee {
private:
	int _id;
	string _firstName;
	string _lastName;
	int _salary;
public:
	Employee(int id, string firstName, string lastName, int salary);
	int GetID();
	string GetFirstName();
	string GetLastName();
	string GetName();
	int GetSalary();
	void SetSalary(int salary);
	int GetAnnualSalary();
	int RaiseSalary(int percent);
	string Print();
};