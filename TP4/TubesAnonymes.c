
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fdRevToRev[2];
    int fdRevToDiff[2];
    
    pipe(fdRevToRev);
    pipe(fdRevToDiff);

    
    //Creation premier processus fils faisant rev
    if(fork() == 0){
        //Fermer ce qui n'est pas necessaire
        close(fdRevToDiff[0]); close(fdRevToDiff[1]);
        close(fdRevToRev[0]);
        //Connexion entre le premier tube et STDOUT
        dup2(fdRevToRev[1], 1);
        close(fdRevToRev[1]);

        //Execution de la commande demandee
        execlp("rev", "rev", "In.txt", NULL);
    }

    //Creation deuxieme processus fils faisant rev aussi
    else if(fork() == 0){
        //Fermer ce qui n'est pas necessaire
        close(fdRevToRev[1]);
        //Connexion entre le premier tube et STDIN
        dup2(fdRevToRev[0], 0);
        close(fdRevToRev[0]);

        close(fdRevToDiff[0]);
        //Connexion entre le deuxieme tube et STDOUT
        dup2(fdRevToDiff[1], 1);
        close(fdRevToDiff[1]);

        //Execution de la commande demandee
        execlp("rev", "rev", NULL);
    }

    //Creation troisieme processus fils faisant diff
    else if(fork() == 0){
        //Fermer ce qui n'est pas necessaire
        close(fdRevToRev[0]); close(fdRevToRev[1]);
        close(fdRevToDiff[1]);
        //Connexion entre le deuxieme tube et STDIN
        dup2(fdRevToDiff[0], 0);
        close(fdRevToDiff[0]);

        //Execution de la commande demandee
        execlp("diff", "diff", "-", "In.txt", "-s", NULL);
    }

    //Processus parent
    else{
        //Fermer ce qui n'est pas necessaire
        close(fdRevToDiff[0]);
        close(fdRevToDiff[1]);
        close(fdRevToRev[0]);
        close(fdRevToRev[0]);

        //Attente de la fin de ses fils avant de se terminer
        wait(NULL);
    }

    return 0;

}