/*
 * CSC A48 - Intro to Computer Science II, Summer 2020
 *
 * This file provides an interactive test driver to help you check your
 * work as you work on A2.
 *
 * This is provided *only* with the intent of helping you test. It's up
 * to you to use this to thoroughly check that everything works in your
 * code.
 *
 * Remember: You are expected to test for *correctness*, that means
 * it's not enough for your functions to produce the right result,
 * they have to do so by manipulating all the relevant data correctly.
 * You should check for structure and correctness at every step.
 *
 * (c) 2020 Mustafa Quraish
 */

#include "Quad.c"
#include <string.h>

void getInt(char *prompt, int *var) {
  printf("%s = ", prompt);
  scanf("%d", var);
  getchar();
}

void getStr(char *prompt, char *var) {
  printf("%s = ", prompt);
  fgets(&var[0], 1024, stdin);
  int i = strlen(&var[0]);
  if (var[i - 1] == '\n')
    var[i - 1] = '\0';
}

int main() {
  int tx, ty, w, h, wsplit, choice, i;
  int sx = 512, threshold, mode;
  Quad *root = NULL;
  Quad *new_note = NULL;
  Quad *t = NULL;
  Image *im = NULL, *im2;
  char name[1024];

  choice = 0;

  while (choice != 9) {
    if (im == NULL) {
      printf("              No image loaded, default sx = %d\n", sx);
    } else {
      printf("                         Image loaded, sx = %d\n", sx);
    }

    printf("Please select from among the following options:\n");
    printf("0 - Insert new Quad\n");
    printf("1 - Search for Quad\n");
    printf("2 - Delete Quad\n");
    printf("3 - Print Quads in order\n");
    printf("4 - Print Quads in pre-order\n");
    printf("5 - Print Quads in post-order\n");
    printf("6 - Load Image\n");
    printf("7 - Split Tree\n");
    printf("8 - Save Image\n");
    printf("9 - Delete BST and exit\n");

    getInt("Enter choice", &choice);
    printf("------------------------------------------------\n");

    if (choice == 0) {
      getInt("tx", &tx);
      getInt("ty", &ty);
      getInt("w", &w);
      getInt("h", &h);
      getInt("wsplit (0/1)", &wsplit);
      new_note = new_Quad(tx, ty, w, h, wsplit, sx);
      root = BST_insert(root, new_note);
    }

    if (choice == 1) {
      getInt("tx", &tx);
      getInt("ty", &ty);
      t = BST_search(root, tx, ty);
      if (t != NULL) {
        printf("Found Quad at tx:ty (%d:%d), w=%d, h=%d, wsplit=%d\n", tx, ty,
               t->w, t->h, t->wsplit);
      } else {
        printf("No such Quad found in the tree\n");
      }
    }

    if (choice == 2) {
      getInt("tx", &tx);
      getInt("ty", &ty);
      root = BST_delete(root, tx, ty);
    }

    if (choice == 3) {
      BST_inorder(root, 0);
    }

    if (choice == 4) {
      BST_preorder(root, 0);
    }

    if (choice == 5) {
      BST_postorder(root, 0);
    }

    if (choice == 6) {
      printf("Note: BST will be reset\n");
      getStr("Name of the image (in .pgm format)", name);
      im = readPGMimage(name);
      if (im != NULL) {
        delete_BST(root);
        root = NULL;
        printf("Image loaded with size = %d x %d\n", im->sx, im->sy);
        sx = im->sx;
      }
    }

    if (choice == 7) {
      if (im == NULL) {
        printf("Please load an image first.\n");
      } else {
        getInt("threshold [0-255]", &threshold);
        getInt("Number of times to split", &h);
        for (i = 0; i < h; i++)
          root = split_tree(im, root, threshold);
      }
    }

    if (choice == 8) {
      if (im == NULL) {
        printf("Please load an image first.\n");
      } else {
        printf("Modes: 0 - outlines\n");
        printf("       1 - outlines with expected colour\n");
        printf("       2 - expected colour\n");
        getInt("mode (0/1/2)", &mode);
        im2 = copyImage(im);
        if (mode > 0) {
          save_Quad(im2, root);
        }
        if (mode < 2) {
          drawOutline(im2, root, 128);
        }
        imageOutput(im2, "output.pgm");
        deleteImage(im2);
      }
    }
    printf("------------------------------------------------\n");
  } // Enf while (choice!=9)

  delete_BST(root);
  deleteImage(im);
  return 0;
}