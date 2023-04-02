// Tp réaliser par : LUCION Ilian 41000958

#ifndef tpimage_h
#define tpimage_h

#include <stdio.h>
#include <stdlib.h>

// -------------------------------------------
// Definition des types
// -------------------------------------------

/// Le type tPixel pour représenter les niveaux de (rouge, vert, bleu)
typedef struct pixel {
    int r;
    int v;
    int b;
} tPixel;

// Le type tImCouleurP3 pour représenter une image en couleur PPM dans un tableau de pixels
typedef struct imagecouleur {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal des niveaux de rouge, vert, bleu d'un pixel
    tPixel** tabpix;       // Le tableau des pixels (tableau de structures de type tPixel)
} tImCouleurP3;

// Le type tImGrisP2 pour représenter une image PGM en mémoire
typedef struct imageGris {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal du niveau de gris des pixels
    int** tabgris;      // Tableau des niveaux de gris des pixels
} tImGrisP2;

// Le type tableau ascii art
typedef struct asciiart {
    int nblig;      // nombre de lignes
    int nbcol;      // nombre de colonnes
    char** tabcar;  // le tableau des caractères
} tASCIIArt;

// -------------------------------------------
// initImgris : effectue l'allocation memoire necessaire pour une imgris de haut x larg pixels
// le type et la valeur maximale ne sont initialisea a 0 par defaut
// -------------------------------------------

extern tImGrisP2 initImgris(int haut, int larg, int maxval);

// -------------------------------------------
// initImCouleur : effectue l'allocation memoire necessaire pour une image de haut x larg pixels
// le type et la valeur maximale ne sont pas initialisea a 0 par defaut
// -------------------------------------------

extern tImCouleurP3 initImCouleur(int haut, int larg, int maxval);

// -------------------------------------------
// copieImCouleur : retourne une copie de l'image donnee en parametre
// -------------------------------------------

extern tImCouleurP3 copieImCouleur(tImCouleurP3 im);

// ************************************************
// chargePPM : charge dans une structure de type tImage
// -------------------------------------------
// l'image contenue dans le fichier donnee en parametre
// Chaque ligne d'un fichier pnm contient au maximum 70 caracteres

extern tImCouleurP3 chargePPM(char* fichier);

// ************************************************
// sauvePPM :  creer le fichier image pnm  a partir
// de la structure tImage donnee
// -------------------------------------------

extern void sauvePPM(char* nom, tImCouleurP3 im);

// ************************************************
// chargePPM : charge dans une structure tImGrisP2
// -------------------------------------------
// l'image contenue dans le fichier donnee en parametre
// Chaque ligne d'un fichier pnm contient au maximum 70 caracteres

extern tImGrisP2 chargePGM(char* fichier);

// ************************************************
// sauvePGM :  creer le fichier image pgm  a partir
// de la structure tImGris donnee
// -------------------------------------------

extern void sauvePGM(char* nom, tImGrisP2 im);

// -------------------------------------------
// Transformation en niveau de gris
// -------------------------------------------
// niveauGris : créer une image en niveau de gris à partir d'une image couleur

extern tImGrisP2 niveauGris(tImCouleurP3 im);

// -------------------------------------------
// copieImGris : retourne une copie de l'image donnee en parametre
// -------------------------------------------

extern tImGrisP2 copieImGris(tImGrisP2 im);

// -------------------------------------------
// Transformation en pavés gris
// -------------------------------------------
/*
 hp, lp : hauteur et largeur des pavés en nombre de pixels
 Un pavé de hp x lp pixels est trnsformé en un pavé de hp x lp pixels identiques dont la valeurs est la moyenne des hp x lp pixels de l'image de départ.
 On ignore les pixels "en trop"
 La largeur de l'image résultat est lp * E(im.largeur / lp) c'est à dire le plus grand multiple de lp.
 La hauteur de l'image resultat est hp * E(im.hauteur / hp) ...
 
 */

extern tImGrisP2 pixelise(tImGrisP2 im, int hp, int lp);

// -------------------------------------------
// Transformation en ascii art
// -------------------------------------------
/*
 hp, lp : hauteur et largeur des pavés en nombre de pixels
 Un pavé de hp x lp pixels est transformé en un carcatère correspondant à luminance moyenne des hp x lp pixels gris de l'image de départ.
 On ignore les pixels "en trop"
 L'ascii art résultat est un tableau de  E(im.hauteur / hp) lignes de  E(im.largeur / lp caractères
 
 */

extern tASCIIArt creerAsciiArt(tImGrisP2 im, int hp, int lp);

// ************************************************
// sauveAscii :  creer le fichier ascii art  a partir
// du tableau de caractères donné (avec ses dimensions)
// -------------------------------------------

extern void sauveAscii(char* nom, tASCIIArt im);

#endif /* tpimage_h */