
//S'inclou les llibreria necesàries.
#include <stdio.h> //Llibreria per utilizar funcions d'entrada/sortida com perror i printf. 
#include <stdlib.h> //S'inclou per utilitzar funcions com exit (per sortir del programa) i altres controls
#include <fcntl.h> //S'inclou per treballar amb arxius a baix nivell (com open, O_CREAT, O_WRONLY, O_APPEND).
#include <unistd.h>  //S'inclou per funcions relacionades amb la manipulació d'arxius i entrada/sortida (com read, write, close).

int main(int argc, char *argv[]) {
    if (argc < 3) { //Comprovem si el nombre d'arguments passats és menor que 3.
        perror("ERROR: cal especificar dos fitxers per comparar"); 
        exit(-1); // Si no es proporcionen dos fitxers, es mostra un missatge d'error i s'acaba el programa.
    }
    // Intentem obrir l'arxiu amb els següents paràmetres:
    // O_RDONLY, especifica que els arxius s'obriran en mode nomès lectura 
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("ERROR en obrir el primer fitxer");
        exit(-1); // Si no es pot obrir el primer fitxer, mostra un error i surt.
    }

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        perror("ERROR en obrir el segon fitxer");
        close(fd1); // Si no es pot obrir el segon fitxer, es tanca el primer fitxer abans de sortir.
        exit(-1);
    }
    //Variables per llegir els bytes dels arxius
    char buf1[1], buf2[1]; // Tots dos búfers han de ser de 1 byte
    ssize_t bytes_read1, bytes_read2; 
    int pos = 1; //Posició en els arxius
    int line = 1; //Comptador de línies
    //Bucle while per llegir els arxius byte a byte
    
    while((bytes_read1 = read(fd1, buf1, 1))>0 && (bytes_read2 = read(fd2, buf2, 1))>0){
        // Comprovem si hi ha una diferència en els bytes llegits
        if(buf1[0] != buf2[0]){
            printf("Diferència trobada al byte %d, línia %d\n", pos, line); // Si hi ha diferència, imprimeix missatge amb la diferència especificant la posició i la línia.
            close(fd1); // Tanquem el primer arxiu.
            close(fd2); // Tanquem el segon arxiu.
            exit(-1); // Finalitza el programa amb un codi d'error (-1).
        }
        if(buf1[0] == '\n'){
            line ++; // Si trobem un salt de línia, incrementem el comptador de línies
        }
        pos ++; // Incrementem la posició per indicar el següent byte.
    }

    if (bytes_read1 == -1 || bytes_read2 == -1) {
        perror("ERROR en llegir els fitxers"); // Si hi ha un error en llegir qualsevol dels fitxers, es mostra un missatge d'error.
        close(fd1); // Tanquem el primer fitxer.
        close(fd2); // Tanquem el segon fitxer.
        exit(-1);  // Finalitzem el programa amb un codi d'error (-1) indicant que ha fallat la lectura.
    }

    close(fd1); // Tanquem el primer fitxer després de la lectura.
    close(fd2);  // Tanquem el segon fitxer després de la lectura.
    return 0; // El programa acaba correctament, indicant que no hi ha hagut errors.
}

