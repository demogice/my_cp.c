#include <stdio.h>  //Trabajo de:Suhar Aristegui, Iker Vicente y Alain Souto
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 

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


int main(int argc, char *argv[]){

	if(argc!=3){
		perror("Se deben introducir dos archivos/un archivo y un directorio");
		exit(EXIT_FAILURE);
	}
   char *dir_o_arch_pegar;
   struct stat st;  //Para comprobar si nos han pasado un archivo o un directorio usaremos stat st
   if(stat(argv[2],&st)==-1){ //En la funcion stat()(definide en biblioteca <sys/stat.h> de C, junto con otras), se toman dos parametros, el primero argv[2] es sobre el cual queremos conocer si es un archivo o directorio
      perror("No se ha podido obtener la informacion del archivo/directorio"); //la segunda en cambio es la direccion donde guerdaremos informacion del segundo parametro(una estructura stat)
       exit(EXIT_FAILURE); //Si la funcion nos devolviera -1 es que habria habido un problema en la obtencion de la informacion, en ese caso salta el error, y nos salimos
   }
   if(S_ISDIR(st.st_mode)){//st.mode contiene la informacion del tipo de archivo o directorio y los permisos, y mediante el uso de S_ISDIR comprobamos si es un directorio
      int longitud=strlen(argv[2]);//obtenemos la longitud del directorio
      if (argv[2][longitud-1]=='/'){//En caso de que el directorio acabe en "/"
         dir_o_arch_pegar=argv[2]; //El destino simplemente sera el directorio
      }
      else{//Si necesitamos agregar el "/" al final del codigo usaremos snprintf que es parecido a sprintf pero nos asegura que no se desbordara el buffer
      char *espacio_en_memoria=malloc(longitud+2); //espacio_en_memoria es un puntero que apunta a la memoria dinamica del segundo parametro
                                                   //Le aniadimos 2 ya que un espacio es para el "/" y el segundo es necesario para el terminador nulo de strings
                                                   //Si no aniadieramos el terminador nulo("\0"), el compilador podria tener problemas a la hora de interpretar y podria fallar el programa 
         if (espacio_en_memoria=NULL){//En caso de que no se hubiera podido modificar el espacio en memoria
               perror("Ha habido un problema con la asignacion de memoria");//Hacemos saltar el error por falta de memoria
               exit(EXIT_FAILURE);        //Y nos salimos del programa
         }
         snprintf(espacio_en_memoria,longitud+2, "%s/", argv[2]); //La funcion sprintf es similar a snprintf, solo que esta ultima evita el desbordamiento de buffer por medio del formateo de cadenas de caracteres(string)
                                                 //Funciona de la siguiente manera, el primer parametro es el lugar donde escribiremos la cadena(a diferencia de printf, que imprime en pantalla, esta funcion guarda en un puntero buffer lo que se quiere escribir)
                                                 //El segundo parametro es la longitud del buffer con el caracter nulo incluido, el tercero es el formato en el que sera impreso ("%s" en nuestro caso ya que es un string)
                                                 //Como queremos aniadirle algo al final, "(lo que se quiera cambiar si va antes)%s(lo que queramos cambiar si va despues)", en este caso "%s/" ya que hay que aniadir un "/" al final
                                                 //Los parametros que se aniaden a partir de los tres iniciales seran modificados o tomados como referencia por la funcion para ser modificados en este caso el segundo argumento argv[2]
         dir_o_arch_pegar=espacio_en_memoria;    //espacio_en_memoria contiene la cadena modificada
         free(espacio_en_memoria);//Vaciamos el espacio en memoria reservado para la cadena modificada, ya que esto no se hace automaticamente al acabar el programa, y dejarlo sin liberar podria llava a problemas de fuga de memoria, es decir,
                                  //El espacio se asigna dinamicamente, y si no se llega a liberar, con el tiempo el programa ocuparia cada vez mas, llevando a problemas mas serios, como la degradacion de rendimiento, o desgaste de la memoria
      }
   }
      else{//en caso de que el segundo argumento no sea un directorio, y sea un archivo
      dir_o_arch_pegar=argv[2];//ya que argv[2]sera un archivo
      }
   
copiar(argv[1],(const char *)dir_o_arch_pegar);//Hacemos la llamada a funcion para la hacer copia
   
	return 0;
}
