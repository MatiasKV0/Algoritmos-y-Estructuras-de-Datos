#include <stdio.h>
#include <string.h>

#define TAM_COLA 300
#define SIN_MEMORIA 1
#define TODO_BIEN 0
#define COLA_VACIA 2

#define minimo( X , Y ) ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )

typedef struct
{
    char     cola[TAM_COLA];
    unsigned pri,
             ult,
             tamDisp;
} tCola;

void crearCola(tCola *p);
int colaLlena(const tCola *p, unsigned cantBytes);
int ponerEnCola(tCola *p, const void *d, unsigned cantBytes);
int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes);
int colaVacia(const tCola *p);
int sacarDeCola(tCola *p, void *d, unsigned cantBytes);
void vaciarCola(tCola *p);


int main()
{
    tCola cola;
    int dato = 2;

    crearCola(&cola);
    ponerEnCola(&cola,&dato,sizeof(dato));
    dato = 0;
    verPrimeroCola(&cola,&dato,sizeof(dato));
    printf("frente de cola: %d\n",dato);
    int respuesta = colaVacia(&cola);
    printf("EsVacia: %d\n",respuesta);
    dato = 0;
    sacarDeCola(&cola,&dato,sizeof(dato));
    printf("frente de cola: %d\n",dato);
    respuesta = colaVacia(&cola);
    printf("EsVacia: %d\n",respuesta);

    return 0;
}


void crearCola(tCola *p)
{
    p->pri = TAM_COLA - 70;
    p->ult = TAM_COLA - 70;
    p->tamDisp = TAM_COLA;
}

int colaLlena(const tCola *p, unsigned cantBytes)
{
    return p->tamDisp < cantBytes + sizeof(unsigned);
}

int ponerEnCola(tCola *p, const void *d, unsigned cantBytes)
{
    unsigned ini, fin;

    if(p->tamDisp < sizeof(unsigned) + cantBytes)
        return 0;

    p->tamDisp -= sizeof(unsigned) + cantBytes;

    // Guardar el tamaño del dato
    if((ini = minimo(sizeof(cantBytes), TAM_COLA - p->ult)) != 0)
        memcpy(p->cola + p->ult, &cantBytes, ini);
    
    if((fin = sizeof(cantBytes) - ini) != 0)
        memcpy(p->cola, ((char *)&cantBytes) + ini, fin);
    
    p->ult = fin ? fin : p->ult + ini;

    // Guardar el dato en sí
    if((ini = minimo(cantBytes, TAM_COLA - p->ult)) != 0)
        memcpy(p->cola + p->ult, d, ini);
    
    if((fin = cantBytes - ini) != 0)
        memcpy(p->cola, ((char *)d) + ini, fin);
    
    p->ult = fin ? fin : p->ult + ini;

    return 1;
}

int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes)
{
    unsigned tamInfo, ini, fin, pos = p->pri;

    if(p->tamDisp == TAM_COLA)
        return 0;

    // Ver tamaño del dato
    if((ini = minimo(sizeof(unsigned), TAM_COLA - pos)) != 0)
        memcpy(&tamInfo, p->cola + pos, ini);
    
    if((fin = sizeof(unsigned) - ini) != 0)
        memcpy(((char *)&tamInfo) + ini, p->cola, fin);
    
    pos = fin ? fin : pos + ini;

    // Ver el dato (truncando si el destino es más chico)
    tamInfo = minimo(tamInfo, cantBytes);
    
    if((ini = minimo(tamInfo, TAM_COLA - pos)) != 0)
        memcpy(d, p->cola + pos, ini);
    
    if((fin = tamInfo - ini) != 0)
        memcpy(((char *)d) + ini, p->cola, fin);

    return 1;
}

int colaVacia(const tCola *p)
{
    return p->tamDisp == TAM_COLA;
}

int sacarDeCola(tCola *p, void *d, unsigned cantBytes)
{
    unsigned tamInfo, ini, fin;

    if(p->tamDisp == TAM_COLA)
        return 0;

    // Extraer tamaño
    if((ini = minimo(sizeof(unsigned), TAM_COLA - p->pri)) != 0)
        memcpy(&tamInfo, p->cola + p->pri, ini);
    
    if((fin = sizeof(unsigned) - ini) != 0)
        memcpy(((char *)&tamInfo) + ini, p->cola, fin);
    
    p->pri = fin ? fin : p->pri + ini;
    p->tamDisp += sizeof(unsigned) + tamInfo;

    // Extraer dato
    unsigned tamACopiar = minimo(tamInfo, cantBytes);
    
    if((ini = minimo(tamACopiar, TAM_COLA - p->pri)) != 0)
        memcpy(d, p->cola + p->pri, ini);
    
    if((fin = tamACopiar - ini) != 0)
        memcpy(((char *)d) + ini, p->cola, fin);

    // Mover el puntero 'pri' según el tamaño real almacenado, no solo lo copiado
    unsigned resto = tamInfo - tamACopiar;
    p->pri = (tamACopiar + p->pri + resto) % TAM_COLA; 

    return 1;
}

void vaciarCola(tCola *p)
{
    p->ult = p->pri;
    p->tamDisp = TAM_COLA;
}