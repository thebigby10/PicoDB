#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <sstream>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;


public:
    // Default constructor
    Date();
    Date(int day, int month, int year);

    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Setters
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    // Convert date to string
    string DatetoString() const;

    //Convert string to date
    void StringtoDate(const string& date);

    // Destructor
    ~Date();
};


    

   





}
