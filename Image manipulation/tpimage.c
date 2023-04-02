// Tp réaliser par : LUCION Ilian 41000958

#include "tpimage.h"

// -------------------------------------------
// initImCouleur : effectue l'allocation memoire necessaire pour une image de haut x larg pixels
// le type et la valeur maximale ne sont pas initialisea a 0 par defaut
// -------------------------------------------

tImCouleurP3 initImCouleur(int haut, int larg, int maxval){
    tImCouleurP3 im;
    im.hauteur = haut;
    im.largeur = larg;
    im.maxval = maxval;
    
    im.tabpix = malloc(haut * sizeof(tPixel *));
    for(int i=0; i<haut; i++){
        im.tabpix[i]= malloc(larg * sizeof(tPixel));
    }
    return im;
}

// -------------------------------------------
// copieImage : retourne une copie de l'image donnee en parametre
// -------------------------------------------

tImCouleurP3 copieImCouleur(tImCouleurP3 im){
    
    tImCouleurP3 copie = initImCouleur(im.hauteur, im.largeur, im.maxval);
    
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur;j++)
            copie.tabpix[i][j] = im.tabpix[i][j];
    }
    
    return copie;
    
}

// -------------------------------------------
// initImgris : effectue l'allocation memoire necessaire pour une imgris de haut x larg pixels
// le type et la valeur maximale ne sont initialisea a 0 par defaut
// -------------------------------------------

tImGrisP2 initImgris(int haut, int larg, int maxval){
    tImGrisP2 img;
    img.hauteur = haut;
    img.largeur = larg;
    img.maxval = maxval;
    
    img.tabgris = malloc(haut * sizeof(int *));
    for(int i=0; i<haut; i++){
        img.tabgris[i]= malloc(larg * sizeof(int));
    }
    return img;
}

// -------------------------------------------
// copieImGris : retourne une copie de l'image donnee en parametre
// -------------------------------------------

tImGrisP2 copieImGris(tImGrisP2 im){
    
    tImGrisP2 copie = initImgris(im.hauteur, im.largeur, im.maxval);
    
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur;j++)
            copie.tabgris[i][j] = im.tabgris[i][j];
    }
    return copie;
}

// ************************************************
// chargePPM : charge dans une structure de type tImage
// -------------------------------------------
// l'image contenue dans le fichier donnee en parametre
// Chaque ligne d'un fichier pnm contient au maximum 70 caracteres


tImCouleurP3 chargePPM(char* fichier){
    FILE* flot;
    tImCouleurP3 im;
    char c;
    int h, l, vmax;   // hauteur et largeur, vmax
    char t[3];        // Type de l'image
    
    // Ouverture du fichier texte en lecture
    if ((flot = fopen(fichier, "r")) == NULL){
        fprintf(stderr, "\nErreur dans chargePPM : %s innaccessible", fichier);
        
        return initImCouleur(0, 0, 0);
    };
    
    // Premiere ligne = type de l'image sur 2 caracteres de la forme Px
    fscanf(flot, "%s", t);
    
    // On passe la fin de la ligne
    while((c = fgetc(flot)) != '\n');
    // on passe aussi toutes les lignes commencant par #
    while ((c = fgetc(flot))=='#') {
        while((c = fgetc(flot)) != '\n');
    }
    // On replace dans le flot du fichier le caractère lu qui n'est pas un #
    ungetc(c, flot);
    
    // On recupere la taille de l'image et on fait l'allocation
    fscanf(flot, "%d", &l); // On lit la largeur de l'image
    fscanf(flot, "%d", &h); // On lit la hauteur de l'image
    // On recupere la valeur maxi des pixels
    fscanf(flot, "%d", &vmax);
    im = initImCouleur(h, l, vmax);

    
    // Puis on lit tous les pixels qu'on place dans le tableau
    for (int i=0; i<im.hauteur; i++) {
        for(int j=0; j< im.largeur; j++){
            fscanf(flot, "%i", &(im.tabpix[i][j].r));
            fscanf(flot, "%i", &(im.tabpix[i][j].v));
            fscanf(flot, "%i", &(im.tabpix[i][j].b));
        }
    }
    
    // On ferme le fichier
    fclose(flot);
    // Et on retourne l'image lue
    return im;
}

// ************************************************
// sauvePPM :  creer le fichier image pnm  a partir
// de la structure tImage donnee
// -------------------------------------------

void sauvePPM(char* nom, tImCouleurP3 im){
    FILE* flot;
    tPixel unPix;
    // Ouverture du fichier
    if( (flot = fopen(nom, "w")) == NULL){
        fprintf(stderr, "\nErreur dans sauvePPM : impossible de creer le fichier %s", nom);
        return;
    }
    // On ecrit d'abord le type de l'image
    fprintf(flot, "%s\n", "P3");
    
    // On ecrit une ligen de commentaire pour indiquer le createur
    fprintf(flot, "# CREATOR : devoir de langage C\n");
    
    // On ecrit les dimensions de l'image
    fprintf(flot, "%d %d\n", im.largeur, im.hauteur);
    
    // Puis la valeur maxi des pixels
    fprintf(flot, "%d\n", im.maxval);
    
    // On ecrit tous les pixels
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur; j++){
            unPix = im.tabpix[i][j];
            fprintf(flot, "%d\n", unPix.r);
            fprintf(flot, "%d\n", unPix.v);
            fprintf(flot, "%d\n", unPix.b);
        }
    }
    
    // et on ferme le fichier
    fclose(flot);
}

// Exercice 7 ///////////////////////////////////

float luminance(tPixel p){
    return(0.299*p.r + 0.587*p.v + 0.114*p.b);
}

tImGrisP2 niveauGris(tImCouleurP3 im){
    tImGrisP2 monImage;

    monImage = initImgris(im.hauteur, im.largeur, im.maxval);

    for (int j = 0; j < im.hauteur; j++)
    {
        for (int k = 0; k < im.largeur; k++)
        {
            monImage.tabgris[j][k] = (int)luminance(im.tabpix[j][k]);
        }
    }

    return monImage;
}

// Exercice 8 ///////////////////////////////////

void sauvePGM(char* nom, tImGrisP2 im){
    FILE* flot;

    // Ouverture du fichier
    if( (flot = fopen(nom, "w")) == NULL){
        fprintf(stderr, "\nErreur dans sauvePGM : impossible de creer le fichier %s", nom);
        return;
    }
    // On ecrit d'abord le type de l'image
    fprintf(flot, "%s\n", "P2");
    
    // On ecrit une ligen de commentaire pour indiquer le createur
    fprintf(flot, "# CREATOR : devoir de langage C\n");
    
    // On ecrit les dimensions de l'image
    fprintf(flot, "%d %d\n", im.largeur, im.hauteur);
    
    // Puis la valeur maxi des pixels
    fprintf(flot, "%d\n", im.maxval);
    
    // On ecrit tous les pixels
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur; j++){
            fprintf(flot, "%d\n", im.tabgris[i][j]);
        }
    }
    
    // et on ferme le fichier
    fclose(flot);
}

// Exercice 9 ///////////////////////////////////

tImGrisP2 chargePGM(char* fichier){
    FILE* flot;
    tImGrisP2 im;
    char c;
    int h, l, vmax;   // hauteur et largeur, vmax
    char t[3];        // Type de l'image
    
    // Ouverture du fichier texte en lecture
    if ((flot = fopen(fichier, "r")) == NULL){
        fprintf(stderr, "\nErreur dans chargePPM : %s innaccessible", fichier);
        
        return initImgris(0, 0, 0);
    };
    
    // Premiere ligne = type de l'image sur 2 caracteres de la forme Px
    fscanf(flot, "%s", t);
    
    // On passe la fin de la ligne
    while((c = fgetc(flot)) != '\n');
    // on passe aussi toutes les lignes commencant par #
    while ((c = fgetc(flot))=='#') {
        while((c = fgetc(flot)) != '\n');
    }
    // On replace dans le flot du fichier le caractère lu qui n'est pas un #
    ungetc(c, flot);
    
    // On recupere la taille de l'image et on fait l'allocation
    fscanf(flot, "%d", &l); // On lit la largeur de l'image
    fscanf(flot, "%d", &h); // On lit la hauteur de l'image
    // On recupere la valeur maxi des pixels
    fscanf(flot, "%d", &vmax);
    im = initImgris(h, l, vmax);

    
    // Puis on lit tous les pixels qu'on place dans le tableau
    for (int i=0; i<im.hauteur; i++) {
        for(int j=0; j< im.largeur; j++){
        fscanf(flot, "%i", &(im.tabgris[i][j]));
        }
    }
    
    // On ferme le fichier
    fclose(flot);
    // Et on retourne l'image lue
    return im;
}

// Exercice 10 //////////////////////////////////

tImGrisP2 pixelise(tImGrisP2 im, int hp, int lp){
    tImGrisP2 monImagePixelise;

    int sum = 0;
    int avg = 0;

    // Calcul des dimensions de la taille de ma nouvelle image
    int hauteur = im.hauteur;
    int largeur = im.largeur;

    // Calcule de la plus grande taille permettant de faire rentrer les carré de dimensions donné
    while (hauteur % hp != 0)
    {
        hauteur--;
    }
    while (largeur % lp != 0)
    {
        largeur --;
    }


    monImagePixelise = initImgris(hauteur, largeur, im.maxval);

    // Parcours de mon image de base

    // Parcour de chacun des blocs
    for (int haut = 0; haut < hauteur; haut+=hp)
    {
        for (int larg = 0; larg < largeur; larg+=lp)
        {
            // Parcours à l'intérieur d'un bloc
            for (int x = 0; x < hp; x++)
            {
                for (int y = 0; y < lp; y++)
                {
                    // Calcule de la somme total des valeur de gris dans un bloc
                    sum += im.tabgris[haut+x][larg+y];
                }
            }

            // Calcul de la moyenne de couleur d'un bloc
            avg = sum / (hp*lp);
            sum = 0;

            for (int x = 0; x < hp; x++)
            {
                for (int y = 0; y < lp; y++)
                {
                    monImagePixelise.tabgris[haut+x][larg+y] = avg;
                }
            }
        }
    }

    return monImagePixelise;
}

// Exercice 11 //////////////////////////////////

// Fonction servant au calcul déterminant le caractère a utiliser
int asciiChar(int moyenne){
    int charactere = (255 - moyenne) * 10/256;

    return charactere;
}

tASCIIArt creerAsciiArt(tImGrisP2 im, int hp, int lp){
    tASCIIArt monImageAscii;

    int sum = 0;
    int avg = 0;

    int valSymbole;
    char symbole;

    // Calcul des dimensions de la taille de ma nouvelle image
    int hauteur = im.hauteur;
    int largeur = im.largeur;

    int indX = 0;
    int indY = 0;

    // Calcule de la plus grande taille permettant de faire rentrer les carré de dimensions donné
    while (hauteur % hp != 0)
    {
        hauteur--;
    }
    while (largeur % lp != 0)
    {
        largeur --;
    }

    // Allocation de la mémoire pour le tableau de caractère
    monImageAscii.tabcar = malloc(hauteur * sizeof(char *));
    for(int i=0; i<hauteur; i++){
        monImageAscii.tabcar[i]= malloc(largeur * sizeof(char));
    }

    // Nombre de colones et ligne qui seront présente dans notre fichier texte
    monImageAscii.nbcol = (hauteur/hp);
    monImageAscii.nblig = (largeur/lp);

    // Parcours de mon image de base

    // Parcour de chacun des blocs
    for (int haut = 0; haut < hauteur; haut+=hp)
    {
        for (int larg = 0; larg < largeur; larg+=lp)
        {
            // Parcours à l'intérieur d'un bloc
            for (int x = 0; x < hp; x++)
            {
                for (int y = 0; y < lp; y++)
                {
                    // Calcule de la somme total des valeur de gris dans un bloc
                    sum += im.tabgris[haut+x][larg+y];
                }
            }

            // Calcul de la moyenne de couleur d'un bloc
            avg = sum / (hp*lp);
            sum = 0;

            // Calcul pour déterminé le caractère a utiliser
            valSymbole = asciiChar(avg);

            if (valSymbole == 0)
            {
                symbole = ' ';
            }
            else if (valSymbole == 1)
            {
                symbole = '.';
            }
            else if (valSymbole == 2)
            {
                symbole = ',';
            }
            else if (valSymbole == 3)
            {
                symbole = ':';
            }
            else if (valSymbole == 4)
            {
                symbole = ';';
            }
            else if (valSymbole == 5)
            {
                symbole = 'O';
            }
            else if (valSymbole == 6)
            {
                symbole = 'X';
            }
            else if (valSymbole == 7)
            {
                symbole = '%';
            }
            else if (valSymbole == 8)
            {
                symbole = '#';
            }
            else if (valSymbole == 9)
            {
                symbole = '@';
            }

            // On place dans le tableau de caratère le symbole correspondant
            monImageAscii.tabcar[indX][indY] = symbole;
            indY++;
        }
        indX++;
        indY = 0;
    }

    // On retourne l'image
    return monImageAscii;
}

// Exercice 12 //////////////////////////////////

void sauveAscii(char* nom, tASCIIArt im){
    FILE* flot;

    // Ouverture du fichier
    if( (flot = fopen(nom, "w")) == NULL){
        fprintf(stderr, "\nErreur dans sauveAscii : impossible de creer le fichier %s", nom);
        return;
    }
    
    // On ecrit tous les pixels
    for(int i=0; i<im.nbcol; i++){
        for (int j=0; j<im.nblig; j++)
        {
            fprintf(flot, "%c", im.tabcar[i][j]);
        }
        // On met un saut de ligne a la fin de la ligne
        fprintf(flot, "\n");
    }
    
    // et on ferme le fichier
    fclose(flot);
}