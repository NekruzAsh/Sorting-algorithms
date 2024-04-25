#include "Student.h"

Student::Student(std::string firstName, std::string lastName, int idNumber) : firstName(firstName), lastName(lastName), idNumber(idNumber) {}


std::string Student::getFirstName() {
    return firstName;
}

std::string Student::getLastName() {
    return lastName;
}

int Student::getIdNumber() {
    return idNumber;
}