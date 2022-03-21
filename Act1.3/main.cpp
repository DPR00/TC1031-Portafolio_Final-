/**
 * Fecha: 20 Mar 2022
 * 
 * Integrantes: 
 *   - Diego Palma (A01759772)
 *   - Pablo Ramirez (A01702872)
 *   - Leonardo Gonzalez (A01721434)
 *
 * Para compilar: 
 * g++ -std=c++17 main.cpp Registro.cpp dateTime.cpp -o main
 *
 * Para ejecutar:
 * ./main 
 */

#include "Registro.h"
#include "dateTime.h"
#include <iostream>
#include <string>
#include <vector>
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

/* ============== MERGE ===================
* Descrition: Function that merges two vectors as part of
* the mergeSort algorithm.
*/
void merge(vector<Registro> &vecRegistros, int begin, int end){
    int mid = (begin+end)/2;
    int j = begin, k = mid+1, size = end-begin+1;
    vector<Registro> vecRegistrosTemp(size);

    for(int i=0; i<size; i++){
        if(j<= mid && k<=end){
            if(vecRegistros[j].getDate() < vecRegistros[k].getDate()) vecRegistrosTemp[i] = vecRegistros[j++];
            else vecRegistrosTemp[i] = vecRegistros[k++];
        }
        else if(j <= mid) vecRegistrosTemp[i] = vecRegistros[j++];
        else vecRegistrosTemp[i] = vecRegistros[k++];
    }
    for(int i=0; i<size; i++){
        vecRegistros[begin+i] = vecRegistrosTemp[i];
    }   
}

/* =========== SORT REGISTROS ===============
* Descrition: Function that sorts registers
* using the merge sort algorithm. Recursive
* implementation.
* - Complex: O(nlog(n))
*/
void sortRegistros(vector<Registro> &vecRegistros, int begin, int end){

    if(begin<end){
        int mid = (begin+end)/2;
        sortRegistros(vecRegistros, begin, mid);
        sortRegistros(vecRegistros, mid+1, end);
        merge(vecRegistros, begin, end);
    }
}

/* =========== FIND REGISTRO ===============
* Descrition: Function that FIND registers
* in a vector of registers using the binary
* search.
* - Complex: O(log2(n))
*/
int findRegistro(vector<Registro> &vecRegistros, time_t date){

  int low = 0;
  int high = vecRegistros.size() - 1;

  while (low <= high) {
    int m = low + (high - low) / 2;
    if (date == vecRegistros[m].getDate()) return m;
    else if (date < vecRegistros[m].getDate()) 
      high = m - 1;
    else 
      low = m + 1;
  }
  return -1;

}

// =============
// Main function
// =============
int main(){

    // Datos 
    vector<Registro> vecRegistros;

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
        vecRegistros.push_back(temp_btc);
    }

    // Ordena los registros
    cout << "Sorting registers ..." << endl;
    cout << endl;
    sortRegistros(vecRegistros, 0, vecRegistros.size()-1);

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
    int m1 = findRegistro(vecRegistros, date1.getDate());
    while (m1==-1){
        cerr << "¡Fecha 1 not found!" << endl;
        cerr << "Intenta nuevamente ... " << endl;
        cout << "Ingrese la primera fecha: ";
        cin >> t_month >> t_day >> t_hours;
        dateTime date1(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));
        m1 = findRegistro(vecRegistros, date1.getDate());
    }

    // Enter second date
    cout << "Ingrese la segunda fecha: ";
    cin >> t_month >> t_day >> t_hours;
    dateTime date2(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));
    // Binary search
    int m2 = findRegistro(vecRegistros, date2.getDate());
    while (m2==-1){
        cerr << "¡Fecha 2 not found!" << endl;
        cerr << "Intenta nuevamente ... " << endl;
        cout << "Ingrese la segunda fecha: ";
        cin >> t_month >> t_day >> t_hours;
        dateTime date2(t_month, t_day, stoi(t_hours.substr(0,2)), stoi(t_hours.substr(3,5)), stoi(t_hours.substr(6,8)));
        m2 = findRegistro(vecRegistros, date2.getDate());
    }

    // Save in bitacora_ordenada.txt
    outputFile.open("bitacora_ordenada.txt");
    for(int i=0; i<vecRegistros.size(); i++){
        string temp = vecRegistros[i].getInfo();
        outputFile << temp << endl;
    }

    // Show registers on screen
    cout << endl;
    cout << "Resultado: " << m2-m1+1 << " Registros" << endl;
    for(int i=m1; i<m2+1; i++){
        string temp = vecRegistros[i].getInfo();
        cout << temp << endl;
    }

    return 1;
}