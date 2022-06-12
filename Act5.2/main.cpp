/**
 * Fecha: 11 Jun 2022
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

#include "Graph.h"
#include "Ip.h"
#include "HashTable.h"
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
ofstream outputFile3;


// Function to determine if a number is prime.
// Source: https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;
   
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;
   
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
   
    return true;
}

// Function to determine the next prime number
// Source: https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
int nextPrime(int N)
{
 
    // Base case
    if (N <= 1)
        return 2;
 
    int prime = N;
    bool found = false;
 
    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;
 
        if (isPrime(prime))
            found = true;
    }
 
    return prime;
}

//
bool compareStr(string str1, string str2){

}


int main(){

    // Leer el archivo
    ifstream inFile;
    inFile.open("bitacoraGrafos.txt");
    if(!inFile){
        cerr << "Error while opening the file" << endl;
        return 1;
    }

    // Variables
    int nodes, edges;
    inFile >> nodes >> edges;
    Graph Grafo(nodes, edges);

    //----------------------------
    // Almacenar datos en el Grafo
    //----------------------------
    while(!inFile.eof()){
        // Recibimos los nodos
        for(int i=0; i<nodes; i++){
            string tempIp;
            inFile >> tempIp;
            Grafo.addNode(tempIp);
        }
        // Recibimos los edges
        for(int i=0; i<edges; i++){
            string junk, origenIp, destinoIp; 
            int costo;
            // Ignoramos las entradas que no requerimos en este problema
            for(int i=0; i<3; i++){
                inFile >> junk;
            }
            // Recibimos ambas IP y el costo
            inFile >> origenIp >> destinoIp >> costo;
            // Solo obtener la IP (ignorar el puerto)
            size_t pos1 = origenIp.find(":");
            origenIp = origenIp.substr(0, pos1);
            size_t pos2 = destinoIp.find(":");
            destinoIp = destinoIp.substr(0, pos2);;
            // Creamos par de IP de destino y costo
            pair<string, int> tempPair(destinoIp, costo);
            // agregamos el edge
            Grafo.addEdge(origenIp, tempPair);
            // Ignoramos las entradas que no seran utilizadas
            while ( (inFile.peek() != '\n' && inFile.peek() != EOF)){
                inFile >> junk;
            }
        }
    }

    //-------------------------------------
    // Crear Hash Table
    //-------------------------------------

    int prime = nextPrime(nodes);
    HashTable<string, Ip> myHashTable(prime);
    map<string, vector<pair<string,int>>> data = Grafo.getData();
    auto iter = data.begin();
    int i=1;
    while (iter != data.end()) {
        string tempNode = iter->first;
        Ip tempIp(tempNode, Grafo.getIn(tempNode), Grafo.getOut(tempNode));
        myHashTable.add(tempNode, tempIp);
        ++iter;
    }

    //-------------------------------------
    // Get the number of collisions
    //-------------------------------------

    cout << "The number of collision in the Hash Table: ";
    cout << myHashTable.getNumCollisions() << endl;

    //-------------------------------------
    // Use of getIPSummary() function
    //-------------------------------------

    cout << "Enter an IP: ";
    string ip;
    cin >> ip;
    Ip userIp = myHashTable.getIPSummary(ip), nulo;
    if (userIp != nulo){
        cout << "IP: " << userIp.getIp() << endl;
        cout << "Total de direcciones accesadas desde la IP: " << userIp.getDirOut()<< endl;
        cout << "Total de direcciones que intentaron acceder a la IP: " << userIp.getDirIn()<< endl;
        cout << "Lista de direcciones accesadas: "<< endl;
        vector<pair<string,int>> tempList = data[userIp.getIp()];
        Grafo.sortIp(tempList);
        for (auto& it : tempList) {
            cout <<it.first << endl;
        }
    }
    else{
        cout << "IP not found D:. Try another IP."<< endl;
    }
    return 0;
}
