// Tp réaliser par : LUCION Ilian 41000958

#include "tpimage.h"

int main(void)
{
  int fin = 0;
  int choix;

  char ppmExt[] = ".ppm";
  char pgmExt[] = ".pgm";
  char txtExt[] = ".txt";

  tImCouleurP3 imagecouleurs;
  tImGrisP2 imageGris, imagePixelise;
  tASCIIArt imageAscii;

  while (fin == 0)
  {
    printf("Quelle operation voulez-vous effectuer ?\n");
    printf("1. Charger une image couleur en memoire\n");
    printf("2. Sauver une image couleur\n");
    printf("3. Transformer une image couleur en niveau de gris\n");
    printf("4. Charger une image en niveau de gris en memoire\n");
    printf("5. Sauver une image en niveau de gris\n");
    printf("6. Pixeliser une image en niveau de gris\n");
    printf("7. Creer un ASCII Art a partir d'une image en niveau de gris\n");
    printf("8. Sauver un ASCII Art\n");
    printf("0. Quitter\n");

    printf("Choix ==> ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix)
    {
      case 0:
        printf("Au revoir.");
        fin = 1;
        break;

      case 1: // Chargement d'une image en couleur depuis un fichier
        char nomPPMfile[100];

        printf("Entrer le chemin vers l'image a charger : ");
        scanf("%s", &nomPPMfile);

        imagecouleurs = chargePPM(nomPPMfile);
        printf("Fait !!");
        printf("\n\n");
        break;

      case 2: // Sauvegarde d'une image en couleur
        char nomPPMsave[100];

        printf("Choisissez un nom pour sauvegarder votre image.");
        printf("Exemple de nom de fichier : fichier.ppm\n");
        printf("=> ");
        scanf("%s", &nomPPMsave);

        sauvePPM(nomPPMsave, imagecouleurs);
        
        printf("Fait !!");
        printf("\n\n");
        break;

      case 3: // Transformation d'une image en couleur en image en nuances de gris
        imageGris = niveauGris(imagecouleurs);
        printf("Fait !!");
        printf("\n\n");
        break;

      case 4: // Chargement d'une image en nuance de gris depuis un fichier
        char nomPGMfile[100];

        printf("Entrer le chemin vers l'image a charger : ");
        scanf("%s", &nomPGMfile);

        imageGris = chargePGM(nomPGMfile);

        printf("Fait !!");
        printf("\n\n");
        break;

      case 5: // Sauvegarde d'une image en nuance de gris
        char nomPGMsave[100];

        printf("Choisissez un nom pour sauvegarder votre image.");
        printf("Exemple de nom de fichier : fichier.pgm\n");
        printf("=> ");
        scanf("%s", &nomPGMsave);

        sauvePGM(nomPGMsave, imageGris);

        printf("Fait !!");
        printf("\n\n");
        break;

      case 6: // Pixelisation d'une image en nuance de gris
        imageGris = copieImGris(imageGris);

        int hauteur;
        int largeur;

        printf("Entrez une valeur pour la hauteur du bloc de pixel que vous souhaite\n");
        printf("La hauteur doit etre comprise entre 1 et %d\n", imageGris.hauteur);
        printf("=> ");
        scanf("%d", &hauteur);

        printf("Entrez une valeur pour la largeur du bloc de pixel que vous souhaite\n");
        printf("La largeur doit etre comprise entre 1 et %d\n", imageGris.largeur);
        printf("=> ");
        scanf("%d", &largeur);

        imageGris = pixelise(imageGris, hauteur, largeur);
        
        printf("Votre image a ete pixelise. Vous devez recharger votre image ou une autre pour effectuer d'autres manipulations.\n");
        printf("Et n'oubliez pas de sauvegarder votre image pixelise.\n");
        printf("\n");
        break;

      case 7: // Transformation d'une image en nuance de gris en ASCII art
        imageGris = copieImGris(imageGris);

        int hauteurAscii;
        int largeurAscii;

        printf("Entrez une valeur pour la hauteur du bloc de pixel que vous souhaite\n");
        printf("La hauteur doit etre comprise entre 1 et %d\n", imageGris.hauteur);
        printf("=> ");
        scanf("%d", &hauteurAscii);

        printf("Entrez une valeur pour la largeur du bloc de pixel que vous souhaite");
        printf("La largeur doit etre comprise entre 1 et %d\n", imageGris.largeur);
        printf("=> ");
        scanf("%d", &largeurAscii);

        imageAscii = creerAsciiArt(imageGris, hauteurAscii, largeurAscii);

        printf("Fait !!\n");
        printf("Et n'oubliez pas de sauvegarder votre image pixelise.\n");
        printf("\n");
        break;

      case 8: // Sauvegarde d'un ASCII dans un fichier texte
        char nomASCIIsave[100];

        printf("Choisissez un nom pour sauvegarder votre image : ");
        printf("Exemple de nom de fichier : fichier.txt\n");
        printf("=> ");
        scanf("%s", &nomASCIIsave);

        sauveAscii(nomASCIIsave, imageAscii);

        printf("Fait !!");
        printf("\n\n");
        break;
    }
  }
  
  return 0;
}