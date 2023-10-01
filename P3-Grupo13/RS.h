#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define RS_FACTOR

typedef struct celdaRS{
	envio envio;
	struct celdaRS *siguiente;
}celdaRS;

typedef struct RS{
	celdaRS *estructura[RS_FACTOR];
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

RS initRS(){
	RS rs;
	int i;

	for(i = 0; i < RS_FACTOR; i++){
		rs.estructura[i] = NULL;
	}

	rs.actual = NULL;
	rs.anterior = NULL;
	rs.cant = 0;

	return rs;
}

//HASH
int hashing(char *x, int M){
    int longitud,i;
    int contador = 0;

    longitud = strlen(x);
    for(i=0; i<longitud; i++)
        contador += ((int)x[i]) * (i+1);

    return (contador % M);
}


#endif // RS_H_INCLUDED


