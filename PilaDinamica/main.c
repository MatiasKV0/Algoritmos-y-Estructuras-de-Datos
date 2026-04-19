#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_MEMORIA 1
#define TODO_BIEN 0
#define PILA_VACIA 2

#define MINIMO(x,y)(((x)>(y))?(y):(x))

typedef struct sNodo {
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tPila;

void crearPila(tPila *p);
int ponerEnPila(tPila *p, const void *d, size_t tam);
int sacarDePila(tPila *p, void *d, size_t tam);
int esPilaVacia(const tPila *p);
int esPilaLlena(const tPila *p, size_t tamDato);
int verTope(const tPila *p, void *d, size_t tam);
void vaciarPila(tPila *p);


int main(){
    tPila pila; //tNodo *pila
    int dato = 2;
    int tope;
    char tope1;

    crearPila(&pila);
    ponerEnPila(&pila, &dato, sizeof(dato));
    int respuesta = esPilaVacia(&pila);
    printf("respusta: %d\n",respuesta);
    verTope(&pila,&tope,sizeof(tope));
    printf("Tope: %d\n", tope);
    char dato1 = 'a';
    ponerEnPila(&pila, &dato1, sizeof(dato1));
    verTope(&pila,&tope1,sizeof(tope1));
    printf("Tope: %c\n", tope1);

    return 0;
}


void crearPila(tPila *p) //tNode **p
{
    *p = NULL;
}

int ponerEnPila(tPila *p, const void *d, size_t tam){
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if(!nuevo){
        return SIN_MEMORIA;
    }

    nuevo->info = malloc(tam);

    if(!nuevo->info){
        free(nuevo);
        return SIN_MEMORIA;
    }

    nuevo->tamInfo = tam;
    memcpy(nuevo->info,d,tam);

    nuevo->sig = *p;
    *p = nuevo;

    return TODO_BIEN;
}

int sacarDePila(tPila *p, void *d, size_t tam){
    tNodo *eliminar = *p;

    if(!*p){
        return PILA_VACIA;
    }

    memcpy(d, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    *p = eliminar->sig;

    free(eliminar->info);
    free(eliminar);

    return TODO_BIEN;
}

int esPilaVacia(const tPila *p){
    return *p == NULL;
}

int esPilaLlena(const tPila *p, size_t tamDato){
    void *nodo = malloc(sizeof(tNodo));
    void *info = malloc(tamDato);

    free(nodo);
    free(info);

    return !nodo || !info;
}

int verTope(const tPila *p, void *d, size_t tam){
    if(!*p){
        return PILA_VACIA;
    }

    memcpy(d, (*p)->info,MINIMO((*p)->tamInfo,tam));
    return TODO_BIEN;
}

void vaciarPila(tPila *p){
    while(*p){
        tNodo *elim = *p;
        *p = elim->sig;
        free(elim->info);
        free(elim);
    }
}

