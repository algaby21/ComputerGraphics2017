#include "Employee.h"
#include <iostream>

Employee::Employee(int id, string firstName, string lastName, int salary){
	_id = id;
	_firstName = firstName;
	_lastName = lastName;
	_salary = salary;
}

int Employee::GetID(){
	return _id;
}

string Employee::GetFirstName(){
	return _firstName;
}

string Employee::GetLastName(){
	return _lastName;
}

string Employee::GetName(){
	return _firstName + " " + _lastName;
}

int Employee::GetSalary(){
	return _salary;
}

void Employee::SetSalary(int salary){
	_salary = salary;
}

int Employee::GetAnnualSalary(){
	return 12 * _salary;
}

int Employee::RaiseSalary(int percent){
	return _salary*(1+(float)percent / 100);
}

string Employee::Print() {
	return "Employee[" + to_string(_id)+", name: "+_firstName+" "+_lastName+", "+to_string(_salary)+"]";
}
