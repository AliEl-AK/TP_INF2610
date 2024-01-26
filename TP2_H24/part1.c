/*
 * Ecole polytechnique de Montreal - GIGL
 * Hiver  2024
 * Initlab - part1.c
 * Ali El-Akhras - 2143326
 * Sobhi Sandakli - 2136216
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
// -------------------------------------------------


int main() {
    char textInFile;
    char docPath[] = "output2.txt";
    int numberCharacter = 1;

    int file = open(docPath, O_WRONLY | O_TRUNC);
    if (file == -1) {
        perror("Appel système open a échoué");
        return 0;
    }

    printf("Saissez votre texte suivi de Ctrl+D:\n");
    while (read(STDIN_FILENO, &textInFile, numberCharacter)) {
        write(file, &textInFile, numberCharacter);
    }

    close(file);
    return 0;
}