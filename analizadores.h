#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void Analizador(string &i);
void exec(string &i, string &root);

void Analizador(string &i){
    printf("Hola como estas, soy el analizador ... \n");
}

void exec(string &i, string &root){
    if (i=="exec")
    {
        printf("analizador del exec ... \n");
    }
}