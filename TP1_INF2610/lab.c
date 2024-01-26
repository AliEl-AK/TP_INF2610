/* INF2610 - TP1
/ Matricule 1 : 2143326 - Nom : Ali El-Akhras
/ Matricule 2 : 2136216 - Nom : Sobhi Sandakli
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
    int* id;
} Wing ;

typedef struct  {
    char* id ;
    char planeType[10];
    bool isAvailable;
    Wheel* wheel;
    Wing* wing;
} Plane ;

Wheel* createWheels (int id) {
    const int numWheels = 7;
    Wheel* wheels = malloc(sizeof(Wheel) * numWheels);
    for (int i = 0; i < numWheels ; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = (i >= 3);
    }
    return wheels;
}

void populateWingAttributes(Wing* wing, int id){
    const int modValue = 10;
    const int size = 9; 
    wing -> id  = malloc(sizeof(int) * size);
    
    for (int i = 0; i < size; i++) {
        wing -> id[i] = 0;
    }

    for (int i = (size - 1) ; i > 0 ; i--){
        wing -> id[i] = id % modValue;
        id = id / modValue; 
    }
}

Wing* createWings (long id){
    const int wingSize =  2; 
    Wing *wings = malloc(sizeof(Wing) * 2);
    for (int i = 0; i< wingSize ; i++){
        populateWingAttributes(&wings[i], id + i );
    }
    return wings;
}

void createPlanes(Plane* planes, const char* id, int numberOfPlanes){
    const long wingId = 1;
    const int wheelId = 1;
    for (int i = 0; i < numberOfPlanes; i++){
        Plane* currentPlane = planes + i;
        currentPlane->id = id;
        currentPlane->isAvailable = true;
        currentPlane->wheel = createWheels(wheelId);
        currentPlane->wing = createWings(wingId);
    }
}
void setAvailability(Plane* plane, bool isAvailable){
    plane -> isAvailable = isAvailable;
}

char** getAvailablePlanes(Plane* planes, int numberOfPlanes){
    char** availablePlanes = malloc(sizeof(char*) * numberOfPlanes);
    int availablePlanesIndex = 0;
    for (int i = 0; i < numberOfPlanes; i++){
        Plane* currentPlane = planes + i;
        if (currentPlane->isAvailable){
            availablePlanes[availablePlanesIndex] = currentPlane->id;
            availablePlanesIndex++;
        }
    }
    return availablePlanes;
}

void setPlaneType(Plane* plane){
    int wingId = plane->wing->id[0];
    int idWingMod = wingId % 9;
    if (wingId < 3){
        strcpy(plane->planeType, "Small");
    } 
    else if (wingId < 6){
        strcpy(plane->planeType, "Medium");
    } 
    else if (wingId < 8){
        strcpy(plane->planeType, "Large");
    }
}

getPlanesByType(Plane* planes, char type[], const int numberOfPlanes){
    Plane* validPlanes = malloc(sizeof(Plane) * numberOfPlanes);
    int validPlanesIndex = 0;
    for (int i = 0; i < numberOfPlanes; i++){
        Plane* currentPlane = planes + i;
        bool str = strcmp(currentPlane->planeType, type);
        if (!str){
            validPlanes[validPlanesIndex] = *currentPlane;
            validPlanesIndex++;
        }
    }
    return validPlanes;
}




int main(int argc, char **argv)
{
    const int wingSize = 2; // 2 wings per plane

    /* PARTIE 2 - [10 points] */
    
    /* Create wheel - [2 points] */
    const int id = 1;  
    Wheel* wheels = createWheels(id);

    /* Create wing - [4 points] */
    const long longId = 1;
    Wing* wings = createWings(longId);

    /* Create plane - [4 points] */
    int numberOfPlanes = 2;
    char* id = "momo";
    Plane* planes = malloc(sizeof(Plane) * numberOfPlanes);
    createPlanes(planes, id, 3);
    printf("id plane 0: %s \n", planes[0].id);
    printf("is plane 0 available: %d \n", planes[0].isAvailable);
    

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    Plane* plane = &(planes[0]);
    setAvailability(plane, true);
    printf("Availability of a plane after the  modification: %d \n", plane->isAvailable);


    /* Get available planes - [1 point] */
    char** availablePlanes = getAvailablePlanes(planes, numberOfPlanes);
    printf("Available planes: %s \n",  availablePlanes[0]);
    
    /* Classify planes - [2 points] */
    
    Plane* plane = &(planes[0]);
    setPlaneType(plane);
    printf("Plane type: %s \n", plane->planeType);
    

    /* Return type specific planes - [2 points] */
    
    char* planeType = "Small";
    Plane* typedPlanes = getPlanesByType(planes, planeType,numberOfPlanes);
    printf("Plane type: %s \n", typedPlanes[0].planeType);
    
    for(int i =0 ; i< wingSize; i++){
        free(wings[i].id);
    }

    free(availablePlanes);
    free(wheels);
    free(wings);
    free(planes);
    free(typedPlanes);
    
    return 0;
}
