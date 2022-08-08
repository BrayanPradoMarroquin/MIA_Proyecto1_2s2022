#include <iostream>
#include <string.h>
#include <stdio.h>
#include "analizadores.h"
using namespace std;

int main(int argc, char *argv[]){
    string mensaje;
    string new_command;
    mensaje = argv[1];
   
    if(argc > 1){
        if (argc == 3)
        {
            string root = argv[2];
            exec(mensaje, root);
        }if (argc > 3)
        {
            cout<<"mayor a 3"<<endl;
        }else
        {
            cout<<"faltan parametros en el comando"<<endl;
        }
    }else{
        mensaje = "ejecute un comando para empezar ... \n";
    }

    Analizador(mensaje);
    return 0;
}