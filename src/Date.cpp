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
    void setDay(int day){
        this->day = day;
    }
    void setMonth(int month){
        this->month = month;
    }
    void setYear(int year){
        this->year = year;
    }

    // Convert date to string
    string DatetoString() const{
        stringstream ss;
        ss << day << "/" << month << "/" << year;
        return ss.str();
        
    }

    //Convert string to date
    void StringtoDate(const string& date) {
        int d, m, y;  
        char delimiter;
        stringstream ss(date);

        // Read the day, month, and year from the string
        ss >> d >> delimiter >> m >> delimiter >> y;

        // Basic validation
        if (ss.fail() || delimiter != '/' || d < 1 || d > 31 || m < 1 || m > 12) {
            throw invalid_argument("Invalid date format");
        }

        // Update the date
        this->day = d;
        this->month = m;
        this->year = y;

        
    }

    // Destructor
    ~Date();
};


    
#endif // DATE_H
   





}
