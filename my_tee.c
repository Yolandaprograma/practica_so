//S'inclou les llibreria necesàries. 
#include <stdio.h>  //Llibreria per utilizar funcions d'entrada/sortida com perror i printf. 
#include <stdlib.h>  //S'inclou per utilitzar funcions com exit (per sortir del programa) i altres controls
#include <fcntl.h> //S'inclou per treballar amb arxius a baix nivell (com open, O_CREAT, O_WRONLY, O_APPEND).
#include <unistd.h>  //S'inclou per funcions relacionades amb la manipulació d'arxius i entrada/sortida (com read, write, close).


int main (int argc, char *argv[]){
    if (argc < 2) { //Comprovem si el nombre d'arguments passats és menor que 2.
        perror("ERROR: cap argument introduït"); //Si és així, el programa no té el nom de l'arxiu i termina amb un missatge d'error.
        exit (-1); //Terminem el programa amb un codi d'error -1.
        
    }
    // Intentem obrir l'arxiu amb els següents paràmetres:
    // - O_WRONLY: Només volem escriure a l'arxiu.
    // - O_APPEND: Si l'arxiu existeix, afegirem dades al final.
    // - O_CREAT: Si l'arxiu no existeix, el crearem amb els permisos especificats.
    // El permís 0644 significa que el propietari té permisos de lectura i escriptura,
    // mentre que el grup i els altres usuaris només tenen permisos de lectura.
    int fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
     //Si l'obertura de l'arxiu falla (fd és -1), imprimim un missatge d'error i terminem el programa.    if(fd == -1){
        perror("ERROR en obrir el fitxer");
        exit (-1);
    }


     //Definim un buffer per emmagatzemar les dades llegides
    char buf[1024];
    ssize_t byte_read; //Variable que emmagatzemarà el nombre de bytes llegits.



    //Iniciem un bucle que llegirà dades del teclat (entrada estàndard) i les escriurà a l'arxiu.
    //read(0, buf, sizeof(buf)) llegeix fins a 1024 bytes des de l'entrada estàndard (0 representa l'entrada estàndard).
    //El bucle continuarà mentre hi hagi bytes llegits (majors que 0).
    while (bytes_read =  read(0, buf, sizeof(buf))>0){
        // Si l'escriptura a l'arxiu falla, imprimim un missatge d'error i tanquem l'arxiu.
        if (write(fd, buf, bytes_read) == -1){
            perror("ERROR: no s'ha pogut escriue en l'arxiu");
            close(fd); // Tanquem l'arxiu abans de sortir del programa.
            exit(-1); // Terminem el programa amb un error.
        }

    }
    // Si la funció read falla (retorna -1), s'imprimeix un missatge d'error.
    // També tanquem l'arxiu abans de sortir.
    if(bytes_read == -1){
        perror("ERROR: No s'ha pogut llegir del teclat");
        close(fd); // Tanquem l'arxiu.
        exit(-1); // Terminem el programa amb un error.
    }
    // Finalment, tanquem l'arxiu. Si el tancament falla, es mostra un error.
    if(close(fd) == -1){
        perror("ERROR al tancar l'arxiu"){
            exit(-1); // Terminem el programa amb un error si no es pot tancar l'arxiu correctament.
        }
        
    return 0;// Terminem el programa amb èxit (valor de retorn 0).
}