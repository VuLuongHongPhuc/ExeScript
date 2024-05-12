
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <random>
#include <iterator>

#define SIZE 128 // taille du tableau

using namespace std;

struct Resultat // déclaration de la structure
{
    int caractere; // champ pour le caractère
    int valeur; // champ pour la valeur
};

int main()
{
    int ascii[SIZE]; // déclaration du tableau
    Resultat resultat[SIZE]; // déclaration du tableau de structures
    srand(time(NULL)); // initialisation du générateur aléatoire
	
	/*
    for (int i = 0; i < SIZE; i++) // boucle pour remplir le tableau
    {
        ascii[i] = rand() % 256; // affectation d'une valeur aléatoire entre 0 et 255
        resultat[i].caractere = i; // affectation du caractère à la structure
        resultat[i].valeur = ascii[i]; // affectation de la valeur à la structure
    }*/
	
	// Generate an array with unique random values from 0 to 255
    unsigned char randomValues[256];
    for (int i = 0; i < 256; ++i) {
        randomValues[i] = static_cast<unsigned char>(i);
    }
    random_shuffle(randomValues, randomValues + 256);

    // Populate the second column with random values from 0 to 255
    for (int i = 0; i < SIZE; ++i) {
        //table[i][1] = randomValues[i];
		resultat[i].valeur = randomValues[i];
		resultat[i].caractere = i; // affectation du caractère à la structure
    }


    cout << "static unsigned char ascii_rand_table[SIZE][2] = {" << endl;

    for (int i = 0; i < SIZE; i++) // boucle pour afficher le tableau de structures
    {
        cout << "{" << setbase(16) << "0x" << resultat[i].caractere << " , " << "0x" << resultat[i].valeur << "},"<< endl; // affichage du caractère et de sa valeur
    }
    cout << "};" << endl;
    return 0;
}
