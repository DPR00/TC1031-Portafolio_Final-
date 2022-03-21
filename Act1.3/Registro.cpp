#include "Registro.h"
#include "dateTime.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;

Registro::Registro(){
    day = 1;
    ip = "a";
    reason = "b";
}

void Registro::setData(string t_month, int t_day, string t_hours, string t_ip, string t_reason){
    
    ip = t_ip;
    reason = t_reason;
    hours = t_hours;
    month = t_month;
    day = t_day;
}

time_t Registro::getDate(){
    
    dateTime date(month, day, stoi(hours.substr(0,2)), stoi(hours.substr(3,5)), stoi(hours.substr(6,8)));

    return date.getDate();
}

string Registro::getInfo(){

    string info;
    info = month + " " + std::to_string(day) + " " + hours + " " + ip + " " + reason;
    
    return info;
}
