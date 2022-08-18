#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

void escribirfd();

struct Partition {
  char name[25];
  char status;
  char type;
  int start;
  char fit; 
  int size;
};

struct EBR
{
    char name[16];
    char status;
    int start; 
    char fit;
    int size; 
    int next;
};

struct PMBR
{
  int mbr_tamano;
  char mbr_fecha_creacion[17];
  int mbr_dsk_signature;
  Partition partitions[4];
};

int max_logical_partitions = 23;
int mounted_prefix = 17;
int size=0;
int unit=0;
string path;
string name;
string tipo;
string fit;
string Delete;
string add;

void AnalizadorFdisk(string dato){
    stringstream nueva(dato);
    string linea;
    int Estado = 0;
    while (getline(nueva, linea, '='))
    {
        if (linea=="-s")
        {
            Estado=1;
        }else if (linea=="-u")
        {
            Estado = 2;
        }else if (linea=="-path")
        {
            Estado = 3;
        }else if (linea=="-name"){
            Estado = 4;
        }else if (linea=="-t")
        {
            Estado = 5;
        }else if (linea=="-f")
        {
            Estado = 6;
        }else if (linea=="-delete")
        {
            Estado=7;
        }else if (linea=="-add")
        {
            Estado=8;
        }else if (Estado==1)
        {
            size = stoi(linea);
            cout<<size<<endl;
        }else if (Estado==2)
        {
            if (linea=="K")
            {
                unit = 1024;
                cout<<linea<<endl;
            }else if (linea=="M")
            {
                unit = 1024*1024;
                cout<<linea<<endl;
            }
        }else if (Estado==3)
        {
            path = linea;
        }else if (Estado==4)
        {
            name = linea;
        }else if (Estado=5)
        {
            tipo = linea;
        }else if (Estado=6)
        {
            fit = linea;
        }else if (Estado=7)
        {
            Delete = linea;
        }else if (Estado==8)
        {
            add = linea;
        }   
    }
}

void escribirfd(){
    PMBR mbr;

    FILE *disk_file = fopen(path.c_str(), "r+");
    if(disk_file!=NULL){
        fseek(disk_file, 0, SEEK_SET);
        fread(&mbr, sizeof(PMBR), 1, disk_file);

        int buscar_indice_particion = -1;
        int indice_particion_extendida = -1;
        int partitionIndex = 0;
        bool has_same_name = 0;

        for(int i = 0; i < 4; i++) {
            if(mbr.partitions[i].status == '1'){
                partitionIndex++;
            
                if(mbr.partitions[i].type == 'E')
                    indice_particion_extendida = i;

                if (mbr.partitions[i].name==name)
                {
                    has_same_name = 1;
                    buscar_indice_particion = i;
                }
                
            }
        }

        int buscar_indice_particion_logica = -1;
        EBR particion_logica[max_logical_partitions];
        for (size_t i = 0; i < max_logical_partitions; i++)
        {
            EBR ebr_vacio;
            ebr_vacio.status = '0';
            ebr_vacio.start = -1;
            ebr_vacio.next = -1;
            ebr_vacio.size = 0;
            particion_logica[i] = ebr_vacio;
        }
        
        if (indice_particion_extendida!=-1)
        {
            EBR ebr_cabecera;
            fseek(disk_file, mbr.partitions[indice_particion_extendida].start, SEEK_SET);
            fread(&ebr_cabecera, sizeof(EBR), 1, disk_file);
            particion_logica[0] = ebr_cabecera;

            //linea 102 en adelante para seguir trabajando
        }
        
    }
    // BUSCAR PARTICION LIBRE
  
  

    Partition nuevaPart;
  nuevaPart.size = unit*size;
  strcpy(nuevaPart.name, name.c_str());

  mbr.partitions[partitionIndex] = nuevaPart;

  // GUARDAR
  fseek(disk_file, 0, SEEK_SET);
  fwrite(&mbr, sizeof(PMBR), 1, disk_file);

  fclose(disk_file);
}

void EjecutarFdisk(){
    escribirfd();
    cout<<"Particion creada"<<endl;
}