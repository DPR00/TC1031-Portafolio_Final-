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
        
};

#endif