#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class Dates {
private:
    int day;
    int month;
    int year;

public:
    // Constructeur par d�faut
    Dates() : day(1), month(1), year(2000) {}

    // Constructeur avec param�tres
    Dates(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {}

    // Getters
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // M�thode pour obtenir une repr�sentation sous forme de cha�ne de la Dates
    string toString() const {
        stringstream ss;
        ss << setw(2) << setfill('0') << day << "/" << setw(2) << setfill('0') << month << "/" << year;
        return ss.str();
    }

};
