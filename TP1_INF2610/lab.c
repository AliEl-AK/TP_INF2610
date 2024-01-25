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
#include <string.h>

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
void createPlanes(Plane* planes, const char* id, int numberOfPlanes) {
    for (int i = 0; i < numberOfPlanes; i++) {
        // Use strncpy to safely copy the ID
        strncpy(planes[i].id, id, sizeof(planes[i].id) - 1);
        planes[i].id[sizeof(planes[i].id) - 1] = '\0'; // Ensure null-termination
        
        planes[i].isAvailable = true; // Set availability to true

        // Use atoi or an appropriate conversion function
        planes[i].wheel = createWheels(atoi(id) + i); // Assuming createWheels expects an integer ID
        planes[i].wing = createWings(atol(id) + i);   // Assuming createWings expects a long ID

        // Initialize planeType as an empty string
        memset(planes[i].planeType, 0, sizeof(planes[i].planeType));
    }
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
    long longId = 1;
    Wing* wings = createWings(longId);
    for (int i = 0; i < 2; i++)
    {
        printf("Wing id: ");
        for (int j = 0; j < 9; j++)
        {
            printf("%d", wings[i].id[j]);
        }
        printf("\n");
    }
    

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
