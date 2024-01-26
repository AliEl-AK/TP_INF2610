#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int id;
    bool isRearWheel;
} Wheel;

typedef struct {
    int* id;
} Wing;

typedef struct {
    char* id;
    char planeType[10];
    bool isAvailable;
    Wheel* wheel;
    Wing* wing;
} Plane;

Wheel* createWheels(int id) {
    const int numWheels = 7;
    Wheel* wheels = malloc(sizeof(Wheel) * numWheels);
    for (int i = 0; i < numWheels; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = (i >= 3);
    }
    return wheels;
}

void populateWingAttributes(Wing* wing, int id) {
    const int modValue = 10;
    const int size = 9;
    wing->id = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        wing->id[i] = 0;
    }

    for (int i = (size - 1); i > 0; i--) {
        wing->id[i] = id % modValue;
        id = id / modValue;
    }
}

Wing* createWings(long id) {
    const int wingSize = 2;
    Wing* wings = malloc(sizeof(Wing) * wingSize);
    for (int i = 0; i < wingSize; i++) {
        populateWingAttributes(&wings[i], id + i);
    }
    return wings;
}

void createPlanes(Plane** planes, const char* id, int numberOfPlanes) {
    const long wingId = 1;
    const int wheelId = 1;
    *planes = malloc(sizeof(Plane) * numberOfPlanes);
    for (int i = 0; i < numberOfPlanes; i++) {
        Plane* currentPlane = &(*planes)[i];
        currentPlane->id = strdup(id);
        currentPlane->isAvailable = true;
        currentPlane->wheel = createWheels(wheelId);
        currentPlane->wing = createWings(wingId);
    }
}

void setAvailability(Plane* plane, bool isAvailable) {
    plane->isAvailable = isAvailable;
}

char** getAvailablePlanes(Plane* planes, int numberOfPlanes, int* countAvailable) {
    int availablePlanesIndex = 0;
    for (int i = 0; i < numberOfPlanes; i++) {
        if (planes[i].isAvailable) {
            availablePlanesIndex++;
        }
    }

    *countAvailable = availablePlanesIndex;
    char** availablePlanes = malloc(sizeof(char*) * availablePlanesIndex);
    availablePlanesIndex = 0;

    for (int i = 0; i < numberOfPlanes; i++) {
        if (planes[i].isAvailable) {
            availablePlanes[availablePlanesIndex++] = strdup(planes[i].id);
        }
    }
    return availablePlanes;
}

void setPlaneType(Plane* plane) {
    int wingId = plane->wing->id[0];
    int idWingMod = wingId % 9;
    if (wingId < 3) {
        strcpy(plane->planeType, "Small");
    } else if (wingId < 6) {
        strcpy(plane->planeType, "Medium");
    } else if (wingId < 8) {
        strcpy(plane->planeType, "Large");
    }
}

Plane* getPlanesByType(Plane* planes, const char* type, int numberOfPlanes) {
    Plane* typedPlanes = malloc(sizeof(Plane) * numberOfPlanes);
    int count = 0;
    for (int i = 0; i < numberOfPlanes; i++) {
        if (strcmp(planes[i].planeType, type) == 0) {
            typedPlanes[count] = planes[i];
            count++;
        }
    }
    return realloc(typedPlanes, sizeof(Plane) * count);
}

int main(int argc, char** argv) {
    const int wingSize = 2; // 2 wings per plane

    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    const int id = 1;
    Wheel* wheels = createWheels(id);

    /* Create wing - [4 points] */
    const long longId = 1;
    Wing* wings = createWings(longId);

    /* Create plane - [4 points] */
    const int numberOfPlanes = 2;
    Plane* planes;
    createPlanes(&planes, "momo", numberOfPlanes);
    printf("is plane 0 available: %d \n", planes[0].isAvailable);

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    Plane* plane = &(planes[0]);
    setAvailability(plane, true);
    printf("Availability of a plane after the modification: %d \n", plane->isAvailable);

    /* Get available planes - [1 point] */
    int countAvailable;
    char** availablePlanes = getAvailablePlanes(planes, numberOfPlanes, &countAvailable);
    if (countAvailable > 0) {
        if (availablePlanes[0] != NULL) {
            printf("Available planes: %s \n", availablePlanes[0]);
        } else {
            printf("No available planes\n");
        }
    } else {
        printf("No available planes\n");
    }
    /* Classify planes - [2 points] */
    setPlaneType(plane);
    printf("Plane type: %s \n", plane->planeType);

    /* Return type specific planes - [2 points] */
    const char* planeType = "Medium"; 
    Plane* typedPlanes = getPlanesByType(planes, planeType, numberOfPlanes);
    if (typedPlanes != NULL) {
        printf("Plane type: %s \n", typedPlanes[0].planeType);
        free(typedPlanes);
    } else {
        printf("No planes of type %s found.\n", planeType);
    }

    for (int i = 0; i < wingSize; i++) {
        free(wings[i].id);
    }

    for (int i = 0; i < numberOfPlanes; i++) {
        free(planes[i].id);
        free(planes[i].wheel);
        free(planes[i].wing);
    }

    free(availablePlanes);
    free(wheels);
    free(wings);
    free(planes);

    return 0;
}
