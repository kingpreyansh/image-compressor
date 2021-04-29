/*
 * CSC A48 - Intro to Computer Science II, Summer 2020
 *
 * This file provides a test driver you can use while developing your
 * solution to test different components.
 *
 * This is provided *only* with the intent of helping you test, and
 * of getting an idea of what *some* of the tests we will subject
 * your code to look like.
 *
 * Passing all the tests in this driver *does not mean your code is
 * bug free*, you have to do much more extensive and thorough testing
 * on your own (a separate interactive driver is provided, and should
 * be helpful with that).
 *
 * Remember: You are expected to test for *correctness*, that means
 * it's not enough for your functions to produce the right result,
 * they have to do so by manipulating all the relevant data correctly.
 * You should check for structure and correctness at every step.
 *
 * (c) 2020 Mustafa Quraish
 */

#include "Quad.c"

int check(Quad *q, int tx, int ty, int w, int h, int wsplit, int sx) {
  return (q->tx == tx && q->ty == ty && q->w == w && q->h == h &&
          q->wsplit == wsplit && q->sx == sx && q->key == tx + (ty * sx));
}

int main() {
  Quad *root = NULL;
  Quad *new = NULL;
  Quad *temp = NULL;
  int tx, ty, w, h, wsplit, sx;
  int pass, i, j;
  unsigned char col;

  // COMMENT AND UN-COMMENT THE TESTS BELOW AS NEEDED!

  // WHILE YOU'RE RUNNING THE TESTS BELOW - you should do ON PAPER the same
  // operations we're asking your BST to perform, so you know what SHOULD
  // be happening, and can find problems when they occur.

  sx = 1000; // Using just this size for the tests here.

  // Test #1 - Creating and initializing a new node for the BST
  tx = 100, ty = 150, h = 100, w = 100, wsplit = 1;
  new = new_Quad(tx, ty, w, h, wsplit, sx);
  pass = 1;
  if (new == NULL)
    pass = 0;
  else if (!check(new, tx, ty, w, h, wsplit, sx))
    pass = 0;
  if (pass == 1)
    printf("Passed test #1\n");
  else {
    printf("Failed test #1 - creating a new node for the BST did not work as "
           "expected\n");
    return 0;
  }

  // Test #2 - Test inserting a couple nodes into the BST
  root = BST_insert(root, new);
  pass = 1;
  if (root != new)
    pass = 0;

  // Where should this go in the tree?
  tx = 150, ty = 100, h = 50, w = 200, wsplit = 0;
  new = new_Quad(tx, ty, w, h, wsplit, sx);
  root = BST_insert(root, new);
  if (root->left != new || root->right != NULL)
    pass = 0;
  if (!check(root->left, tx, ty, w, h, wsplit, sx))
    pass = 0;

  // Where should this go in the tree?
  tx = 200, ty = 200, h = 150, w = 75, wsplit = 0;
  new = new_Quad(tx, ty, w, h, wsplit, sx);
  root = BST_insert(root, new);
  if (root->right != new)
    pass = 0;
  if (!check(root->right, tx, ty, w, h, wsplit, sx))
    pass = 0;

  if (pass == 0) {
    printf("Failed test #2 - BST insert didn't work properly\n");
    return 0;
  } else
    printf("Passed test #2\n");

  // Test #3 - Search for specific nodes
  new = new_Quad(300, 400, 50, 25, 1, sx);
  root = BST_insert(root, new);

  tx = 274, ty = 143, h = 45, w = 225, wsplit = 0;
  new = new_Quad(tx, ty, w, h, wsplit, sx);
  root = BST_insert(root, new);

  new = new_Quad(130, 440, 40, 65, 0, sx);
  root = BST_insert(root, new);

  temp = BST_search(root, tx, ty);
  pass = 1;
  if (temp == NULL)
    pass = 0;
  if (!check(temp, tx, ty, w, h, wsplit, sx))
    pass = 0;
  if (pass == 0) {
    printf("Failed test #3 - BST search did not find the node we just added to "
           "the tree\n");
    return 0;
  } else
    printf("Passed test #3\n");

  // Test #4 - Delete, case a) (node without children)
  root = BST_delete(root, 274, 143);
  temp = BST_search(root, 274, 143);
  pass = 1;
  if (temp != NULL)
    pass = 0;
  if (root == NULL || root->left == NULL || root->left->right != NULL)
    pass = 0;
  if (pass == 0) {
    printf("Failed test #4 - BST delete, case a) something went wrong\n");
    return 0;
  } else
    printf("Passed test #4\n");

  // Test #5 - Delete, case b) (node with one child)
  temp = BST_search(root, 200, 200);
  pass = 1;
  if (temp == NULL) {
    printf("Test #5 - Node with a tx=200,ty=200 is not in the BST, it "
           "should be there!\n");
    return 0;
  }
  root = BST_delete(root, 200, 200);
  pass = 1;
  temp = BST_search(root, 200, 200);
  if (temp != NULL || root == NULL || root->right == NULL)
    pass = 0;
  if (!check(root->right, 300, 400, 50, 25, 1, sx))
    pass = 0;
  if (pass == 0) {
    printf("Failed test #5 - BST delete case b) did not do the right thing\n");
    return 0;
  } else
    printf("Passed test #5\n");

  // Test #6 - Delete, case c) (node with 2 children)
  new = new_Quad(140, 300, 30, 2, 1, sx);
  root = BST_insert(root, new);
  new = new_Quad(100, 300, 5, 27, 0, sx);
  root = BST_insert(root, new);

  root = BST_delete(root, 100, 150); // Deletes the note at root!
  pass = 1;
  temp = BST_search(root, 100, 150);
  if (temp != NULL || root == NULL || root->right == NULL)
    pass = 0;
  if (!check(root, 100, 300, 5, 27, 0, sx))
    pass = 0;
  if (!check(root->right, 300, 400, 50, 25, 1, sx))
    pass = 0;
  if (pass == 0) {
    printf("Failed test #6 - BST delete case c) did not do the right thing\n");
    return 0;
  } else
    printf("Passed test #6\n");

  // Test #7 - In-Order Traversal
  // THIS TEST NEEDS TO BE CHECKED BY YOU, so make sure you have a diagram ON
  // PAPER of what the tree should contain up to this point, given all the
  // operations above. You then have to check that the functions print out the
  // right information that means: The nodes in the tree in the correct order
  // given how the traversal works.
  printf("\n*** Checking in-Order traversal\n");
  BST_inorder(root, 0);

  // Test #8 - pre-Order Traversal
  printf("\n*** Checking pre-Order traversal\n");
  BST_preorder(root, 0);

  // Test #9 - post-Order Traversal
  printf("\n*** Checking post-Order traversal\n");
  BST_postorder(root, 0);

  printf("\n\n");

  //////////////////////////////////////////////////////////////////////////////
  ////////// Uncomment the follwing for basic tests for crunchy ////////////////
  //////////////////////////////////////////////////////////////////////////////

  root = delete_BST(root);
  sx = 10; // This is for the image tests.

  /* NOTE: Each of these tests is only for one node. You need to check if your
    functions work for a whole tree yourself */

  // Test #10 - get_colour()
  Image *im = newImage(10, 10);
  new = new_Quad(0, 0, 10, 10, 0, 10);
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      im->data[i + j * 10] = 255 - i * i - j * j;
  if (get_colour(im, new) != 198) {
    printf(
        "Failed test #10 - get_colour() did not return the correct result.\n");
    return 0;
  } else
    printf("Passed test #10\n");

  // Test #11 - save_Quad()
  new->tx = 1, new->ty = 1, new->w = 5, new->h = 5;
  col = get_colour(im, new);
  save_Quad(im, new);
  pass = 1;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      if (i == 0 || i > 5 || j == 0 || j > 5) {
        if (im->data[i + j * 10] != 255 - i * i - j * j)
          pass = 0;
      } else if (im->data[i + j * 10] != col)
        pass = 0;
  if (pass == 0) {
    printf("Failed test #11 - save_Quad() did not do the right thing\n");
    return 0;
  } else
    printf("Passed test #11\n");

  // Test #12 - drawOutline()
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      im->data[i + j * 10] = 255;

  drawOutline(im, new, 100);
  pass = 1;

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      if (((i == 1 || i == 5) && (j > 0 && j < 6)) ||
          ((j == 1 || j == 5) && (i > 0 && i < 6))) {
        if (im->data[i + j * 10] != 100) {
          pass = 0;
        }
      } else if (im->data[i + j * 10] != 255) {
        pass = 0;
      }
    }
  }

  if (pass == 0) {
    printf("Failed test #12 - draw_outline() did not do the right thing\n");
    return 0;
  } else {
    printf("Passed test #12\n");
  }

  // The tests above check bac functionality of your A2. You should write
  // your own test cases here for the missing functions, and to more
  // comprehensively check all of them. The other crunchy function
  // (split_tree) is better tested from the interactive test loop.
  // Load in the examples given in the documentation, and make some
  // up yourselves to see if your code behaves the way it should.

  // Be sure to test out the functionality of your crunchy functions thoroughly
  // before submitting!

  return 0;
}