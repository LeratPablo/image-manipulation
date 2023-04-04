# Image Manipulation Program in C

This program allows you to manipulate images in the PPM and PGM format through the command line. The program is written in C and the image is displayed in the terminal.

---

# Getting Started
## Prerequisites
- GCC (GNU Compiler Collection) or any C compiler.

---

## Installation
1. Clone the repository:
```
git clone https://github.com/LeratPablo/image-manipulation.git
```

2. Compile the tpimage.c file:
```
gcc tpimage.c -o main.exe
```

---

## Usage
1. To launch the program, run the following command:
```
./main.exe
```

2. Choose an operation from the interface:
```
Quelle operation voulez-vous effectuer ?
1. Charger une image couleur en memoire
2. Sauver une image couleur
3. Transformer une image couleur en niveau de gris
4. Charger une image en niveau de gris en memoire
5. Sauver une image en niveau de gris
6. Pixeliser une image en niveau de gris
7. Creer un ASCII Art a partir d'une image en niveau de gris
8. Sauver un ASCII Art
0. Quitter
Choix ==>
```

3. Follow the prompt to complete the chosen operation.

**Note**: The result of the operations will be saved in the same folder as main.exe.

**Note**: No English translation has been done. Everything is in French.

**Note**: ASCII Art images are save into .txt file.

# Technical informations
To use this program properly, u can follow this instruction sequence on the interface (choice n° - description): 
- 1 - Load a ppm image
- 2 - save it
- 3 - Turn it to grayscale
- 5 - Save it to a pgm file
- 4 - Load the pgm file in memory
- 6 - pixelates the pgm image
- 5 - Save the pixelates image in pgm format
And now u have a GrayScale pixelate image.

If u want to manipulate any other ppm or pgm file, don't forget to load them by using command 1 or 4.

Also, don't forget to save them after u make a change.

---

### Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

---

### License
This project is licensed under the MIT License - see the LICENSE file for details.
