#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>

static bool flagDeFin = false;

static int *tampon;
static int sizeTampon;
static int sommeProduit = 0; 
static int sommeConsommee = 0 ;

static int ip = 0;
static int ic = 0;

static sem_t libre;
static sem_t occupe;
static sem_t mutex;


void* producteur(void* pid) {
    int *nbGenre = malloc(sizeof(int));
    srand(time(NULL));
    while(1){
        sem_wait(&libre);
        int chiffreRandom = (rand() % 9) + 1 ;

        sem_wait(&mutex);
        tampon[ip] = chiffreRandom;
        sommeProduit += tampon[ip];
        ip = (ip + 1) % sizeTampon;

        sem_post(&mutex);

        sem_post(&occupe);
        (*nbGenre)++;
        if(flagDeFin){
        break;
        }
    }
        printf("Fin de production du thread %d\n", (int)(long)pid);
        pthread_exit(nbGenre);
}

void* consommateur(void* cid) {
    int *nbConsomme = malloc(sizeof(int));
    int objRecuperer  = 0;

    while(1){
        printf("Consommation du thread %d\n" , (int)(long)cid);
        sem_wait(&occupe);

        sem_wait(&mutex);
        objRecuperer = tampon[ic];
        sommeConsommee += objRecuperer; 
        ic += 1;
        ic = ic % sizeTampon;
        sem_post(&mutex);

        sem_post(&libre);
        if(objRecuperer == 0){
            break;
            (*nbConsomme++);

        }
    }

    printf("Fin de consommation du thread %d\n", (int)(long)(cid));
    pthread_exit(nbConsomme);
    
}
void actionAlarme(){
    flagDeFin = true;
}

int main(int argc, char* argv[]) {

   int numProd = atoi(argv[1]);
   int numCons = atoi(argv[2]);
   sizeTampon = atoi(argv[3]);

   pthread_t *prodThreads = malloc(numProd * sizeof(pthread_t));
   pthread_t *consThreads = malloc(numCons * sizeof(pthread_t));
   tampon = malloc(sizeTampon * sizeof(int));

   sem_init(&mutex, 0, 1);
   sem_init(&libre, 0, sizeTampon);
   sem_init(&occupe, 0, 0);

   // Creation des threads producteur:
   for (size_t i = 0; i < numProd; i++)
      pthread_create(&prodThreads[i], NULL, producteur, (void *)i);

   // Creation des threads consommateur:
   for (size_t i = 0; i < numCons; i++)
      pthread_create(&consThreads[i], NULL, consommateur, (void *)i);

   // Lancement de l'alarme systeme:
   signal(SIGALRM, actionAlarme);
   alarm(1);

   // Attente de la fin des treads producteur:
   int nbTotalProduction = 0;
   for (size_t i = 0; i < numProd; i++)
   {
      int *exit_status;
      pthread_join(prodThreads[i], (void **)&exit_status);

      nbTotalProduction += *exit_status;
      free(exit_status);
   }

   // Mettre des zeros pour chaque consommmateur:
   sem_wait(&mutex);
   int nbOverwrite = 0;
   bool isOverwriting = false;
   for (size_t i = 0; i < sizeTampon; i++)
   {
      int value = tampon[ip];
      tampon[ip] = 0;

      isOverwriting = ip == ic ? true : isOverwriting;
      isOverwriting = value == 0 ? false : isOverwriting;

      if (isOverwriting)
      {
         sommeConsommee += value;
         nbOverwrite++;
      }

      ip = (ip + 1) % sizeTampon;
   }
   sem_post(&mutex);

   // Attente de la fin des treads consommateurs:
   int nbTotalConsommation = nbOverwrite;
   for (size_t i = 0; i < numCons; i++)
   {
      int *exit_status;
      pthread_join(consThreads[i], (void **)&exit_status);

      nbTotalConsommation += *exit_status;
      free(exit_status);
   }
   printf("\033[0;31m\n");
   printf("Le nombre production: %d \n", nbTotalProduction);
   printf("Le nombre consommation: %d \n", nbTotalConsommation);

   printf("Le sommeProduit: %d \n", sommeProduit);
   printf("Le sommeConsommer: %d \n", sommeConsommee);
   printf("\033[0m");

   free(prodThreads);
   free(consThreads);
   free(tampon);

   return 0;
}

