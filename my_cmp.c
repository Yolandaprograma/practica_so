#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("ERROR: cal especificar dos fitxers per comparar");
        exit(-1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("ERROR en obrir el primer fitxer");
        exit(-1);
    }

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        perror("ERROR en obrir el segon fitxer");
        close(fd1);
        exit(-1);
    }

    char buf1[1], buf2[1];
    ssize_t bytes_read1, bytes_read2;
    int pos = 1;
    int line = 1;

    while((bytes_read1 = read(fd1, buf1, 1))>0 && (bytes_read2 = read(fd2, buf2, 1))>0){
        if(buf1[0] != buf2[0]){
            printf("Diferència trobada al byte %d, línia %d\n", pos, line);
            close(fd1);
            close(fd2);
            exit(-1);
        }
        if(buf1[0] == '\n'){
            line ++;
        }
        pos ++;
    }

    if (bytes_read1 == -1 || bytes_read2 == -1) {
        perror("ERROR en llegir els fitxers");
        close(fd1);
        close(fd2);
        exit(-1);
    }

    close(fd1);
    close(fd2);
    return 0;
}
