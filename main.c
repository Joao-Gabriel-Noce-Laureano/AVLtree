#include <stdio.h>
#include "bst.h"

int main () {
  Tree t = createTree();
  link x;
  AVLinsert(t,99);
  AVLinsert(t,89);
  AVLinsert(t,88);
  AVLinsert(t,109);
  AVLinsert(t,110);
  AVLinsert(t,112);
  AVLinsert(t,111);
  imprime(t, "oi");

  return 0;
}
