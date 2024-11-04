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
    Date(){
        this->day = 1;
        this->month = 1;
        this->year = 2000; //default date
    }
    Date(int day, int month, int year){
        this->day = day;
        this->month = month;
        this->year = year;
    }

    // Getters
    int getDay() const{
        return day;
    }
    int getMonth() const{
        return month;
    }
    int getYear() const{
        return year;
    }

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


    
#endif // DATE_H
   





}
