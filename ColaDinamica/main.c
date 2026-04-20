#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_MEMORIA 1
#define TODO_BIEN 0
#define COLA_VACIA 2

#define MINIMO(x,y)(((x)>(y))?(y):(x))

typedef struct sNodo{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef struct{
    tNodo *pri;
    tNodo *ult;
}tCola;


void crearCola(tCola * p);
int ponerEnCola(tCola *p, const void *d, size_t tam);
int sacarDeCola(tCola *p, void *d, size_t tam);
int esColaVacia(const tCola *p);
int esColaLlena(const tCola *p, size_t tam);
int verFrenteDeCola(const tCola *p, void * d, size_t tam);
void vaciarCola(tCola *p);



int main()
{
    tCola cola;
    int dato = 2;

    crearCola(&cola);
    ponerEnCola(&cola,&dato,sizeof(dato));
    dato = 0;
    verFrenteDeCola(&cola,&dato,sizeof(dato));
    printf("frente de cola: %d\n",dato);
    int respuesta = esColaVacia(&cola);
    printf("EsVacia: %d\n",respuesta);
    dato = 0;
    sacarDeCola(&cola,&dato,sizeof(dato));
    printf("frente de cola: %d\n",dato);
    respuesta = esColaVacia(&cola);
    printf("EsVacia: %d\n",respuesta);

    return 0;
}

void crearCola(tCola * p){
    p->pri = p->ult = NULL;
}

int ponerEnCola(tCola *p, const void *d, size_t tam){
    tNodo *nuevo = (tNodo *) malloc(sizeof(tNodo));

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

    nuevo->sig = NULL;

    if(p->ult){
        p->ult->sig = nuevo;
    }
    else{
        p->pri = nuevo;
    }
    p->ult = nuevo;
    return TODO_BIEN;
}

int sacarDeCola(tCola *p, void *d, size_t tam){
    tNodo *eliminar = p->pri;

    if(!eliminar){
        return COLA_VACIA;
    }

    memcpy(d, eliminar->info, MINIMO(eliminar->tamInfo,tam));
    p->pri = eliminar->sig;

    if(!p->pri){
        p->ult = NULL;
    }

    free(eliminar->info);
    free(eliminar);

    return TODO_BIEN;
}

int esColaVacia(const tCola *p){
    return !p->pri;
}

int esColaLlena(const tCola *p, size_t tam){
    void *nodo = malloc(sizeof(tNodo));
    void *info = malloc(tam);

    free(nodo);
    free(info);

    return !nodo || !info;
}

int verFrenteDeCola(const tCola *p, void * d, size_t tam){
    if(!p->pri){
        return COLA_VACIA;
    }

    memcpy(d, p->pri->info, MINIMO(p->pri->tamInfo,tam));
    return TODO_BIEN;
}

void vaciarCola(tCola *p){
    while(p->pri){
        tNodo *eliminar = p->pri;
        p->pri = eliminar->sig;
        free(eliminar->info);
        free(eliminar);
    }

    p->ult = NULL;
}
