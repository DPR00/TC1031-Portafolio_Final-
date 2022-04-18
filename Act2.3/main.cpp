/**
 * Fecha: 08 Abr 2022
 * 
 * Integrantes: 
 *   - Diego Palma (A01759772)
 *
 * Para compilar: 
 * g++ -std=c++17 *.cpp -o main
 *
 * Para ejecutar:
 * ./main 
 */

#include "Registro.h"
#include "dateTime.h"
#include "DLinkedList.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

ofstream outputFile;
ofstream outputFile2;

// =============
// Main function
// =============
int main(){

    // Datos 
    DLinkedList<Registro> dLLRegistros;

    Registro temp_btc, bitacora1, bitacora2;
    string t_month, t_ip, t_hours;
    int t_day;

    // Datos de la primera fecha
    
    // Leer el archivo "bitacora.txt" y almacenarlo en un vector de datos
    ifstream inFile;
    inFile.open("bitacora.txt");
    if(!inFile){
        cerr << "Error while opening the file" << endl;
        return 1;
    }

    // Read and storage bitacora.txt
    while(!inFile.eof()){
        inFile >> t_month >> t_day >> t_hours >> t_ip;
        string t_reason;
        while ( inFile.peek() != '\n' && inFile.peek() != EOF){
            string temp;
            inFile >> temp;
            t_reason += temp+ " ";
        }
        temp_btc.setData(t_month, t_day, t_hours, t_ip, t_reason);
        dLLRegistros.addLast(temp_btc);
    }

    // Ordena los registros
    cout << "Sorting registers ..." << endl;
    cout << endl;
    dLLRegistros.sort();

    // As for the two date
    cout << "============================" << endl;
    cout << "Formato para ingresar fechas" << endl;
    cout << "============================" << endl;
    cout << endl;
    cout << "PRIMER DATO: 3 primeras letras del mes (en ingles). Por ejm: Agosto -> Aug" << endl;
    cout << "SEGUNDO DATO: Dia del mes en 2 digitos. Por ejm: Tercer dia -> 03" << endl;
    cout << "TERCER DATO: Hora exacata - hh:mm:ss. Por ejm: Las 2 horas, 34 min con 40 seg -> 02:34:40 " << endl;
    cout << endl;
    cout << "Ejemplo de Input: Aug 03 02:34:40";
    cout << endl;
    cout << endl;
    cout << "Con el formato indicado ..." << endl;

    // Enter first date
    cout << "Ingrese la primera fecha: ";
    cin >> t_month >> t_day >> t_hours;
    dateTime date1(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));

    // Binary search
    int m1 = dLLRegistros.findRegistro(date1.getDate()); 
    while (m1==-1){
        cerr << "¡Fecha 1 not found!" << endl;
        cerr << "Intenta nuevamente ... " << endl;
        cout << "Ingrese la primera fecha: ";
        cin >> t_month >> t_day >> t_hours;
        dateTime date1(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));
        m1 = dLLRegistros.findRegistro(date1.getDate()); 
    }

    // Enter second date
    cout << "Ingrese la segunda fecha: ";
    cin >> t_month >> t_day >> t_hours;
    dateTime date2(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));
    // Binary search
    int m2 = dLLRegistros.findRegistro(date2.getDate());
    while (m2==-1){
        cerr << "¡Fecha 2 not found!" << endl;
        cerr << "Intenta nuevamente ... " << endl;
        cout << "Ingrese la segunda fecha: ";
        cin >> t_month >> t_day >> t_hours;
        dateTime date2(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));
        m2 = dLLRegistros.findRegistro(date2.getDate());
    }

    // Save in bitacora_ordenada.txt
    outputFile.open("bitacora_ordenada.txt");
    for(int i=0; i<dLLRegistros.getNumElements(); i++){
        string temp = dLLRegistros[i].getInfo();
        outputFile << temp << endl;
    }

    // Show registers on screen
    cout << endl;
    outputFile2.open("resultado_busqueda.txt");
    cout << "Resultado: " << m2-m1+1 << " Registros" << endl;
    for(int i=m1; i<m2+1; i++){
        string temp = dLLRegistros[i].getInfo();
        cout << temp << endl;
        outputFile2 << temp << endl;
    }

    return 1;
}