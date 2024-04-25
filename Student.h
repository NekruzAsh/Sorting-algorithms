#pragma once

#include <string>

class Student {
private:
    std::string firstName;
    std::string lastName;
    int idNumber;

public:

    Student(std::string firstName, std::string lastName, int idNumber);

    std::string getFirstName();
    std::string getLastName();
    int getIdNumber();
};