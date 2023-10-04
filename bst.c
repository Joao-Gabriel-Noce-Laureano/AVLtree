#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int id = 0;
link novoNo (int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->altura = 0; //inicializando altura como 0 *****
  t->id = id++;
  return t;
}
Tree createTree(){
  Tree t = malloc (sizeof (struct tree));
  t->z = malloc (sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->altura = -1; //colocando a altura do nó exterior como -1 para testes em que um dos galhos da árvore está vazio.************
  t->z->r = t->z;
  return t;
}

link rotR (Tree t, link h) { //funções de rotação agora atualizam a altura e o número de nós das sub-árvores ***********
  link x = h->l;
  h->l = x->r;
  x->r = h;
  
  setAltura(t,x->r);
  setAltura(t,x);
  
  x->r->N = x->r->l->N + x->r->r->N + 1;
  x->N = x->l->N + x->r->N + 1;
  return x;
}

link rotL (Tree t, link h) { //funções de rotação agora atualizam a altura e o número de nós das sub-árvores ***********
  link x = h->r; 
  h->r = x->l; 
  x->l = h; 
  
  setAltura(t,x->l);
  setAltura(t,x);
  
  x->l->N = x->l->l->N + x->l->r->N + 1;
  x->N = x->l->N + x->r->N + 1;
  return x;
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if(h->item == query) 
    return h;
  if (h->item >= query) 
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
} 


link search (Tree t, int query){
   return searchR(t, t->head, query);
}

link insertR (Tree t, link h, link n) {
  if (h == t->z) {
    return  n;
  }

  if(h->item >= n->item)
    h->l = insertR(t, h->l, n);
  else 
    h->r = insertR(t, h->r, n);
  (h->N)++;
  return h;
}

link insert (Tree t, int item){
  if(t->head == t->z) {
    return (t->head =novoNo(item, t->z, t->z));
  }
  return insertR(t, t->head, novoNo(item, t->z, t->z));
}

void imprimeEmOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimeEmOrdem (t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N); 
  imprimeEmOrdem (t, h->r);
}

void imprimePosOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimePosOrdem (t, h->l);
  imprimePosOrdem (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}
void imprimePreOrdem (Tree t, link h, int k) {
  if(h == t->z) return;
  for(int i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  imprimePreOrdem (t, h->l, k + 1); 
  imprimePreOrdem (t, h->r, k + 1);
}


void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}
int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N); 
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}

void setAltura(Tree t, link h) //Criada função para calcular a nova altura do nó h ********
{
	if(h == t->z) return;
	if(h->l->altura > h->r->altura) h->altura = h->l->altura+1;
	else h->altura = h->r->altura+1;
}

link AVLinsertR (Tree t, link h, link n){ //Função criada baseada na insertR
  if (h == t->z) {
    return  n; 
  }

  if(h->item >= n->item)
    h->l = AVLinsertR(t, h->l, n);
  else 
    h->r = AVLinsertR(t, h->r, n);
    
  if(h->l->altura > h->r->altura+1) //desbalanceado para a esquerda
  {
  	if(h->l->r->altura > h->l->l->altura) h->l = rotL (t, h->l);
	h = rotR (t, h);
  }
  else if(h->r->altura > h->l->altura+1) //desbalanceado para a direita
  {
  	if(h->r->l->altura > h->r->r->altura) h->r = rotR (t, h->r);
	h = rotL (t, h);
  }
  else
  {
  	(h->N)++;
  }
  
  setAltura(t,h); //Chamada da função setAltura para alterar as alturas de cada sub-árvore 
  
  
  return h;
}

link AVLinsert (Tree t, int item){ //Função criada baseada na insert
  if(t->head == t->z) {
    return (t->head =novoNo(item, t->z, t->z));
  }
  t->head = AVLinsertR(t, t->head, novoNo(item, t->z, t->z));
  return t->head;
}




