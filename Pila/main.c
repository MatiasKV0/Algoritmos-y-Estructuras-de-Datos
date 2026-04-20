#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define TODO_BIEN 0
#define SIN_MEMORIA 1
#define PILA_VACIA 2
#define MINIMO(x,y)(((x)>(y))?(y):(x))

typedef struct
{
    char pila[TAM];
    size_t tope;
} tPila;

void crearPila(tPila *p);
int ponerEnPila(tPila *p, const void *d, size_t tamDato);
int sacarDePila(tPila *p, void *d, size_t tamDato);
int verTopePila(const tPila *p, void *d, size_t tamDato);
int esPilaVacia(const tPila *p);
int esPilaLlena(const tPila *p, size_t tamDato);
void vaciarPila(tPila *p);

int main()
{
    tPila pila;
    int dato = 2;
    int tope;
    char tope1;

    crearPila(&pila);
    ponerEnPila(&pila, &dato, sizeof(dato));
    int respuesta = esPilaVacia(&pila);
    printf("respusta: %d\n",respuesta);
    verTopePila(&pila,&tope,sizeof(tope));
    printf("Tope: %d\n", tope);
    char dato1 = 'a';
    ponerEnPila(&pila, &dato1, sizeof(dato1));
    verTopePila(&pila,&tope1,sizeof(tope1));
    printf("Tope: %c\n", tope1);


    return 0;
}

void crearPila(tPila *p)
{
    p->tope = TAM;
}

int ponerEnPila(tPila *p, const void *d, size_t tamDato)
{
    if(p->tope < tamDato + sizeof(size_t))
    {
        return SIN_MEMORIA;
    }

    p->tope -= tamDato;
    memcpy(p->pila + p->tope, d, tamDato);
    p->tope -= sizeof(size_t);
    memcpy(p->pila + p->tope, &tamDato, sizeof(size_t));
    return TODO_BIEN;
}

int sacarDePila(tPila *p, void *d, size_t tamDato)
{
    size_t tamDatoPila;

    if(p->tope == TAM)
    {
        return PILA_VACIA;
    }

    memcpy(&tamDatoPila, p->pila + p->tope,sizeof(size_t));
    p->tope += sizeof(size_t);
    memcpy(d, p->pila + p->tope, MINIMO(tamDatoPila,tamDato));
    p->tope += tamDatoPila;
    return TODO_BIEN;
}

int verTopePila(const tPila *p, void *d, size_t tamDato)
{
    size_t tamDatoPila;

    if(p->tope==TAM)
    {
        return PILA_VACIA;
    }

    memcpy(&tamDatoPila, p->pila + p->tope,sizeof(size_t));
    memcpy(d, p->pila + p->tope + sizeof(size_t), MINIMO(tamDatoPila,tamDato));
    return TODO_BIEN;
}

int esPilaVacia(const tPila *p)
{
    return p->tope == TAM;
}

int esPilaLlena(const tPila *p, size_t tamDato)
{
    return p->tope < tamDato + sizeof(size_t);
}

void vaciarPila(tPila *p)
{
    p->tope = TAM;
}
