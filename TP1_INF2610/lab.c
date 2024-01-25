/* INF2610 - TP1
/ Matricule 1 :
/ Matricule 2 :
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    bool isRearWheel;
} Wheel;

typedef struct  {
    int* id; //Allocation dynamique puisque on a pas la taille de tableau
} Wing ;

typedef struct  {
    char* id ;
    char planeType[10];
    bool isAvailable;
    Wheel* wheel;
    Wing* wing;
} Plane ;

Wheel* createWheels (int id) {
    int numWheels = 7;
    Wheel* wheels = malloc(sizeof(Wheel) * numWheels);
    for (int i = 0; i < numWheels ; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = (i >= 3);
    }
    return wheels;
}

void populateWingAttributes(Wing* wing, int id){
    const int size = 9; 
    wing -> id  = malloc(sizeof(int) * size);
    
    // Everything to zero at first 
    for (int i = 0; i < size; i++) {
        wing -> id[i] = 0;
    }
    // size - 1 car on commence par 0 et non 1  
    for (int i = (size - 1) ; i > 0 ; i--){
        wing -> id[i] = id % 10;
        id = id/10; 
    }
}

Wing* createWings (long id){
    int size =  2; 
    Wing *wings = malloc(sizeof(Wing) * 2);
    for (int i = 0; i< size ; i++){
        populateWingAttributes(&wings[i], id + i );
    }
    return wings;
}

int main(int argc, char **argv)
{
    /* PARTIE 2 - [10 points] */
    /* Create wheel - [2 points] */

    int id = 1;
    Wheel* wheels;
    wheels = createWheels(id);
    for (int i =0 ; i < 7 ; i++) {
        printf("Wheel id : %d\n", wheels[i].id);
    }
    /* Create wing - [4 points] */
    /*
    long longId = 1;
    Wing[] wings;
    wings = createWings(longId);
    */

    /* Create plane - [4 points] */
    /*
    int numberOfPlanes = 3;
    Plane* planes = malloc(sizeof(Plane) * numberOfPlanes);
    createPlanes(planes, *id, 3);
    */

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    /*
    Plane plane = planes[0];
    setAvailability(plane, true);
    */

    /* Get available planes - [1 point] */
    /*
    getAvailablePlanes(planes, numberOfPlanes);
    */

    /* Classify planes - [2 points] */
    /*
    Plane plane = planes[1];
    setPlaneType(plane);
    */

    /* Return type specific planes - [2 points] */
    /*
    char planeType[] = "Small";
    getPlanesByType(planes, planeType,numberOfPlanes);
    */
    return 0;
}
