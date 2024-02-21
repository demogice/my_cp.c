#include <stdio.h>  //Trabajo de:Suhar Aristegui, Iker Vicente y Alain Souto
#include <stdlib.h>
#include <string.h>

void copiar(const char *archivo_a_abrir,const char *archivo_a_copiar){
    FILE *archivoCopy, *archivoPaste;
    if(archivo_a_abrir!=NULL){
       archivoCopy=fopen(archivo_a_abrir, "rb");
       archivoPaste=fopen(archivo_a_copiar, "wb");
         if(archivoCopy==NULL){
            perror("Hubo un error en la apertura del archivo");
               exit(EXIT_FAILURE);
         }
    }
    const int tamBuffer = 4096;
    char buffer[tamBuffer];
    while(fgets(buffer, tamBuffer, archivoCopy)!=NULL){
	      fputs(buffer, archivoPaste);
   }
   fclose(archivoCopy);
   fclose(archivoPaste);
}

