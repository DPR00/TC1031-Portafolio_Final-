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
        // Almacenar un registro
        void setData(string t_month, int t_day, string t_hours, string t_ip, string t_reason);
        // Acceso a datos privados
        time_t getDate();
        string getInfo();
        string getIp();
        // Obtener la IP en formato unsigned int
        unsigned int getIntIp(string t_ip);
        // Sobrecarga de operadores
        bool operator > (const Registro&);
        bool operator < (const Registro&);
        bool operator == (const Registro&);
        bool operator != (const Registro&);
        bool operator >= (const Registro&);
        bool operator <= (const Registro&);
};

#endif