#ifndef BST_H
#define BST_H


typedef struct node * link;
struct node {
  link l;
  link r;
  int item;
  int N;      // quantidade de nos na subarvore
  int id;     // id da nÃ³
  int altura; //altura da subárvore **********
};

typedef struct tree {
  link head; // raiz
  link z;    // nÃ³ externo
} * Tree;

Tree createTree();


link rotR (Tree t, link h);

link rotL (Tree t, link h);

link search (Tree h, int query);

link insert (Tree h, int item);

void imprimeEmOrdem (Tree t, link h);
void imprimePosOrdem (Tree t, link h);
void imprimePreOrdem (Tree t, link h, int k);

void setAltura(Tree t, link h); //Declaração de função criada para calcular a nova altura do nó h

link AVLinsert (Tree t, int item); //Parametros mudados para melhor funcionamento ********


void imprime(Tree a, char *s);
 
#endif 


