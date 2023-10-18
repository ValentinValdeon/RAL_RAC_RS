#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define RS_FACTOR 211

int maxRSEvocEx=0,costRSEvocEx=0,cantRSEvocEx=0,maxRSEvocFr=0,costRSEvocFr=0,cantRSEvocFr=0;

typedef struct celdaRS{
	envio envio;
	struct celdaRS *siguiente;
}celdaRS;

typedef struct RS{
	celdaRS *estructura[211];
	celdaRS *anterior;
	celdaRS *actual;
	int cant;
}RS;

celdaRS *initCelda(envio envAux){
    celdaRS* n = (celdaRS*)malloc(sizeof(celdaRS));
    if(n == NULL)
        return n;

    n->envio = envAux;
    n->siguiente = NULL;

    return n;
}

void initRS(RS *rs){
	int i;

	for(i = 0; i < RS_FACTOR; i++){
		(*rs).estructura[i] = NULL;
	}

	(*rs).actual = NULL;
	(*rs).anterior = NULL;
	(*rs).cant = 0;

	return rs;
}

//HASH
int hashingRS(char *x){
    int longitud,i;
    int contador = 0;

    longitud = strlen(x);
    for(i=0; i<longitud; i++)
        contador += ((int)x[i]) * (i+1);

    return (contador % RS_FACTOR);
}




#endif // RS_H_INCLUDED


