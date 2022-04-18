#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

using std::string;

class Registro{

    private:
        string ip, reason, month;
        string hours;
        int day;

    public:
        Registro();
        void setData(string t_month, int t_day, string t_hours, string t_ip, string t_reason);
        time_t getDate();
        string getInfo();
        //void ();
        //void printDates(string f_month1, int f_day1, string f_hours1, string f_month2, int f_day2, string f_hours2);
};

#endif