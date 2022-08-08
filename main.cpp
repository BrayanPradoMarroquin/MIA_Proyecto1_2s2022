#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[]){
    char* mensaje;

    if(argc > 1){
        mensaje = argv[1];
    }else{
        mensaje = "ejecute un comando para empezar ... \n";
    }

    printf(mensaje);
    return 0;
}