// Ajouter les directives d'inclusion nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    mkfifo ("tube1", 0600);
    mkfifo ("tube2", 0600);

    //Creation premier processus fils faisant rev
    if (fork() == 0) {
        //Ouverture du tube 
        int fd = open("tube1", O_WRONLY);
        //Connexion entre le premier tude et STDOUT
        dup2(fd, 1);
        close(fd);
        //Execution de la commande rev
        execlp("rev", "rev", "In.txt", NULL);
    }

    //Creation deuxieme processus fils faisant rev aussi
    else if (fork() == 0) {
        //Ouverture du tube
        int fd = open("tube1", O_RDONLY);
        //Connexion entre le premier tube et STDIN
        dup2(fd, 0);
        close(fd);
        //Ouverture du deuxieme tube
        int fd2 = open("tube2", O_WRONLY);
        //Connexion entre le deuxieme tube et STDOUT
        dup2(fd2, 1);
        close(fd2);

        //Execution de la commande rev    
        execlp("rev", "rev", NULL);
    }
    //Creation du troisieme processus fils faisant diff
    else if (fork() == 0) {
        //Ouverture du deuxieme tube
        int fd = open("tube2", O_RDONLY);
        //Connexion entre le deuxieme tube et STDIN
        dup2(fd, 0);
        close(fd);
        //Execution de la commande diff
        execlp("diff", "diff", "-", "In.txt", "-s", NULL);
    }
    
    else {
        //Attente de la fin des processus fils
        wait(NULL);
    }
    return 0;
}
